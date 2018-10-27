#pragma once

#include "EEGPacketListener.h"

#include "ip/UdpSocket.h"

namespace eeg
{
	class DataHandler
	{
	public:
		DataHandler(int port = 7000)
			: _s(IpEndpointName(IpEndpointName::ANY_ADDRESS, port), &_listener)
		{
		}

		void run()
		{
			_s.Run();
		}

		void stop()
		{
			_s.AsynchronousBreak();
		}

		const Data* data() { return &_listener._data; }

	protected:
		UdpListeningReceiveSocket _s;
		EEGPacketListener _listener;
	};
};

