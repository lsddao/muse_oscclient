#pragma once

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

#include "EEGData.h"

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

		try 
		{
			if (std::strcmp(m.AddressPattern(), "Person0/elements/horseshoe") == 0)
			{
				auto arg = m.ArgumentsBegin();

				for (auto channel = 0; channel < Data::EEG_Last; ++channel)
					_data.quality[channel] = static_cast<Data::ContactQuality>((int)(arg++)->AsDouble());

				if (arg != m.ArgumentsEnd())
					throw osc::ExcessArgumentException();
			}
			else if (std::strcmp(m.AddressPattern(), "Person0/elements/is_good") == 0)
			{
				auto arg = m.ArgumentsBegin();

				for (auto channel = 0; channel < Data::EEG_Last; ++channel)
					_data.isEegGood[channel] = static_cast<bool>((int)(arg++)->AsDouble());

				if (arg != m.ArgumentsEnd())
					throw osc::ExcessArgumentException();
			}
			else if (std::strcmp(m.AddressPattern(), "Person0/elements/touching_forehead") == 0)
			{
				auto arg = m.ArgumentsBegin();

				_data.touchingForehead = static_cast<bool>((int)(arg++)->AsInt32());

				if (arg != m.ArgumentsEnd())
					throw osc::ExcessArgumentException();
			}
			else if (std::strcmp(m.AddressPattern(), "Person0/elements/beta_absolute") == 0)
			{
				auto arg = m.ArgumentsBegin();

				for (auto channel = 0; channel < Data::EEG_Last; ++channel)
					_data.absoluteFreq[channel][Data::Beta] = (arg++)->AsDouble();

				if (arg != m.ArgumentsEnd())
					throw osc::ExcessArgumentException();
			}
			/* TODO other freqs*/
		}
		catch (osc::Exception& e)
		{
			// any parsing errors such as unexpected argument types, or 
			// missing arguments get thrown as exceptions.
			std::cerr << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
		}
	}
};

};
