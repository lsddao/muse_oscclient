TEMPLATE = app
CONFIG += windows
TARGET = oscclient
DEPENDPATH += .
QT += core concurrent widgets gui

LIBS += Ws2_32.lib Winmm.lib

include(osc.pri)

SOURCES +=	main.cpp \
			EEGDataConsumer.cpp \
			CSVWriter.cpp \
			EEGSession.cpp \
			MainWindow.cpp

HEADERS +=	EEGData.h \
			EEGDataHandler.h \
			EEGPacketListener.h \
			EEGDataConsumer.h \
			CSVWriter.h \
			EEGSession.h \
			CSVDataModel.h \
			SimpleCSVDataModel.h \
			MainWindow.h