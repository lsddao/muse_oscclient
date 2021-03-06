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
		EEGSession(const Data* data);
		virtual ~EEGSession();

		void addDataConsumer(IDataConsumer* consumer);

		void start(int syncIntervalMs = 1000);
		void stop();

	protected:
		QList<IDataConsumer*> _consumers;
		QTimer _timer;
		const Data* _data;
	};
};
