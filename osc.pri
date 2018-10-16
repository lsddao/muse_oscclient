HEADERS += \
	osc/MessageMappingOscPacketListener.h \
	osc/OscException.h \
	osc/OscHostEndianness.h \
	osc/OscOutboundPacketStream.h \
	osc/OscPacketListener.h \
	osc/OscPrintReceivedElements.h \
	osc/OscReceivedElements.h \
	osc/OscTypes.h \
	ip/IpEndpointName.h  \
	ip/NetworkingUtils.h  \
	ip/PacketListener.h  \
	ip/TimerListener.h  \
	ip/UdpSocket.h
  
SOURCES += \
	osc/OscOutboundPacketStream.cpp \
	osc/OscPrintReceivedElements.cpp \
	osc/OscReceivedElements.cpp \
	osc/OscTypes.cpp \
	ip/IpEndpointName.cpp \
	ip/win32/NetworkingUtils.cpp \
	ip/win32/UdpSocket.cpp