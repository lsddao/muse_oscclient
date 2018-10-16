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

	short columnCount() override { return 4; }

	QString columnName(short columnId)
	{
		switch (columnId)
		{
		case 0: return "ContactQuality_LeftForehead";
		case 1: return "ContactQuality_RightForehead";
		case 2: return "Frontal_Asymmetry";
		case 3: return "Event_NextTrackPressed";
		default: return QString();
		}
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
			double left = _data->absoluteFreq[Data::EEG2][Data::Beta];
			double right = _data->absoluteFreq[Data::EEG3][Data::Beta];
			double diff = left - right;

			return QString::number(diff);
		}
		case 3:
		{
			return QString::number(_eventTriggered ? 1 : 0);
		}
		default:
			return QString();
		}
	}

protected:
	bool _eventTriggered{ false };
};

};
