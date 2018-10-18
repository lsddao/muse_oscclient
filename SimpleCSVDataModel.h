#pragma once

#include "CSVDataModel.h"

namespace eeg
{

class TestDataModel : public ICSVDataModel
{
public:
	bool eventTriggered() { return _eventTriggered; }

	void setEventTriggered() { _eventTriggered = true; }
	void resetAllEvents() override { _eventTriggered = false; }

	short columnCount() override { return 11; }

	QString columnName(short columnId)
	{
		switch (columnId)
		{
		case 0: return "ContactQuality_L";
		case 1: return "ContactQuality_R";
		case 2: return "EEG_good_L";
		case 3: return "EEG_good_R";
		case 4: return "NextTrackPressed";
		case 5: return "BetaPower_L";
		case 6: return "BetaPower_R";
		case 7: return "BetaPower_Diff";
		case 8: return "GammaPower_L";
		case 9: return "GammaPower_R";
		case 10: return "GammaPower_Diff";
		default: return QString();
		}
	}

	inline QString toString(bool val)
	{
		return val ? "1" : "0";
	}

	inline QString toString(double val)
	{
		return QString::number(val);
	}

	QString data(short columnId) override
	{
		switch (columnId)
		{
		case 0: 
		{
			return QString::number(_data->quality[Data::EEG2]);
		}
		case 1:
		{
			return QString::number(_data->quality[Data::EEG3]);
		}
		case 2:
		{
			return toString(_data->isEegGood[Data::EEG2]);
		}
		case 3:
		{
			return toString(_data->isEegGood[Data::EEG3]);
		}
		case 4:
		{
			return toString(_eventTriggered);
		}
		case 5:
		{
			return toString(_data->absoluteFreq[Data::EEG2][Data::Beta]);
		}
		case 6:
		{
			return toString(_data->absoluteFreq[Data::EEG3][Data::Beta]);
		}
		case 7:
		{
			double left = _data->absoluteFreq[Data::EEG2][Data::Beta];
			double right = _data->absoluteFreq[Data::EEG3][Data::Beta];
			return toString(left - right);
		}
		case 8:
		{
			return toString(_data->absoluteFreq[Data::EEG2][Data::Gamma]);
		}
		case 9:
		{
			return toString(_data->absoluteFreq[Data::EEG3][Data::Gamma]);
		}
		case 10:
		{
			double left = _data->absoluteFreq[Data::EEG2][Data::Gamma];
			double right = _data->absoluteFreq[Data::EEG3][Data::Gamma];
			return toString(left - right);
		}
		default:
			return QString();
		}
	}

protected:
	bool _eventTriggered{ false };
};

};
