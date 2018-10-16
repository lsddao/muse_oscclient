#include "EEGSession.h"

eeg::EEGSession::EEGSession(const Data* data)
	: _data(data)
{
}

eeg::EEGSession::~EEGSession()
{
	stop();
	qDeleteAll(_consumers);
}

void eeg::EEGSession::addDataConsumer(IDataConsumer* consumer)
{
	consumer->setData(_data);
	_consumers.append(consumer);
	QObject::connect(&_timer, &QTimer::timeout, [consumer]() { consumer->consume(); });
}

void eeg::EEGSession::start(int syncIntervalMs)
{
	_timer.start(syncIntervalMs);
}

void eeg::EEGSession::stop()
{
	_timer.stop();
}
