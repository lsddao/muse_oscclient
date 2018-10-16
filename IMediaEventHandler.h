#pragma once

namespace eeg
{
	class IMediaEventHandler
	{
	public:
		virtual void nextTrack() = 0;
	};
};

