#pragma once

#include "EEGPacketListener.h"

#include "ip/UdpSocket.h"

namespace eeg
{
	class DataHandler
	{
	public:
		DataHandler(int port = 7000)
			: _port(port)
		{
		}

		void run()
		{
			UdpListeningReceiveSocket s(
				IpEndpointName(IpEndpointName::ANY_ADDRESS, _port),
				&_listener);
			s.RunUntilSigInt();
		}

		const Data* data() { return &_listener._data; }

	protected:
		EEGPacketListener _listener;
		int _port;
	};
};

