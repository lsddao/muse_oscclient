#pragma once

namespace eeg
{
	struct Data
	{
		enum Channel { EEG1 = 0, EEG2, EEG3, EEG4, EEG_Last };
		enum FrequencyBand { Delta = 0, Theta, Alpha, Beta, Gamma, FrequencyBand_Last };
		enum ContactQuality { Good = 1, Mediocre = 2, Bad = 4 };

		Data()
		{
			reset();
		}

		void reset()
		{
			touchingForehead = false;
			for (short channel = EEG1; channel < EEG_Last; ++channel)
			{
				quality[channel] = Bad;
				isEegGood[channel] = false;
				for (short band = Delta; band < FrequencyBand_Last; ++band)
					absoluteFreq[channel][band] = 0;
			}
		}

		bool touchingForehead{ false };
		bool isEegGood[EEG_Last];
		ContactQuality quality[EEG_Last];
		double absoluteFreq[EEG_Last][FrequencyBand_Last];
	};
};
