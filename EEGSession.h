#pragma once

#include <QList>
#include <QTimer>

#include "EEGDataConsumer.h"
#include "EEGDataHandler.h"

namespace eeg
{
	class EEGSession
	{
	public:
		EEGSession();
		virtual ~EEGSession();

		void setData(const Data* data) { _data = data; }
		void addDataConsumer(IDataConsumer* consumer);

		bool running() { return _timer.isActive(); }
		void start(int syncIntervalMs = 1000);
		void stop();

	protected:
		QList<IDataConsumer*> _consumers;
		QTimer _timer;
		const Data* _data;
	};
};
