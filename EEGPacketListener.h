#pragma once

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"

#include <QString>
#include <QMap>

#include "EEGData.h"

#include <iostream>

namespace eeg
{
	
class EEGPacketListener : public osc::OscPacketListener 
{
public:
	Data _data;

protected:
	virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
	{
		(void)remoteEndpoint;

		static QMap<QString, Data::FrequencyBand> bandNames;
		if (bandNames.isEmpty())
		{
			bandNames["delta"] = Data::Delta;
			bandNames["theta"] = Data::Theta;
			bandNames["alpha"] = Data::Alpha;
			bandNames["beta"] = Data::Beta;
			bandNames["gamma"] = Data::Gamma;
		}

		try 
		{
			const QStringList addressPattern = QString(m.AddressPattern()).split("/");
			if (addressPattern.size() == 3 && addressPattern[0] == "Person0" && addressPattern[1] == "elements")
			{
				const QString element = addressPattern[2];
				if (element == "horseshoe")
				{
					auto arg = m.ArgumentsBegin();

					for (auto channel = 0; channel < Data::EEG_Last; ++channel)
						_data.quality[channel] = static_cast<Data::ContactQuality>((int)(arg++)->AsDouble());

					if (arg != m.ArgumentsEnd())
						throw osc::ExcessArgumentException();
				}
				else if (element == "is_good")
				{
					auto arg = m.ArgumentsBegin();

					for (auto channel = 0; channel < Data::EEG_Last; ++channel)
						_data.isEegGood[channel] = static_cast<bool>((int)(arg++)->AsDouble());

					if (arg != m.ArgumentsEnd())
						throw osc::ExcessArgumentException();
				}
				else if (element == "touching_forehead")
				{
					auto arg = m.ArgumentsBegin();

					_data.touchingForehead = static_cast<bool>((int)(arg++)->AsInt32());

					if (arg != m.ArgumentsEnd())
						throw osc::ExcessArgumentException();
				}
				else if (element.endsWith("_absolute"))
				{
					const QString strBand = QString(element).remove("_absolute");
					Data::FrequencyBand band = bandNames.value(strBand, Data::FrequencyBand_Last);
					if (band == Data::FrequencyBand_Last)
						throw std::exception("unknown frequency band");

					auto arg = m.ArgumentsBegin();

					for (auto channel = 0; channel < Data::EEG_Last; ++channel)
						_data.absoluteFreq[channel][band] = (arg++)->AsDouble();

					if (arg != m.ArgumentsEnd())
						throw osc::ExcessArgumentException();
				}
			}
		}
		catch (osc::Exception& e)
		{
			// any parsing errors such as unexpected argument types, or 
			// missing arguments get thrown as exceptions.
			std::cerr << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
		}
		catch (std::exception& e)
		{
			std::cerr << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
		}
	}
};

};
