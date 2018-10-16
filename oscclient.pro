TEMPLATE = app
CONFIG += console
TARGET = oscclient
DEPENDPATH += .
QT += core concurrent

TARGET_EXT = .exe

DEFINES += UNICODE _UNICODE WIN32 _CONSOLE NOMINMAX

LIBS += Ws2_32.lib Winmm.lib

include(osc.pri)

SOURCES +=	main.cpp \
			EEGDataConsumer.cpp \
			CSVWriter.cpp \
			EEGSession.cpp

HEADERS +=	EEGData.h \
			EEGDataHandler.h \
			EEGPacketListener.h \
			EEGDataConsumer.h \
			CSVWriter.h \
			EEGSession.h \
			CSVDataModel.h \
			SimpleCSVDataModel.h