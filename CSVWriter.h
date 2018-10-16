#pragma once

#include "EEGDataConsumer.h"
#include "CSVDataModel.h"

#include <QFile>
#include <QTextStream>

namespace eeg
{
	class CSVWriter : public IDataConsumer
	{
	public:
		CSVWriter(const QString& fileName, ICSVDataModel* model);
		~CSVWriter();

		void consume() override;

	protected:
		void writeHeader();
		void writeRow();

	private:
		ICSVDataModel* _model{nullptr};
		QFile _file;
		QTextStream _stream;
		bool _headerWritten{ false };
	};
};
