#include "CSVWriter.h"

#include <QDebug>

eeg::CSVWriter::CSVWriter(const QString& fileName, ICSVDataModel* model)
	: _file(fileName)
	, _model(model)
{
	_file.open(QIODevice::Append);
	_stream.setDevice(&_file);
}

eeg::CSVWriter::~CSVWriter()
{
	_stream.flush();
	_file.close();
}

void eeg::CSVWriter::consume()
{
	if (!_headerWritten)
	{
		writeHeader();
		_headerWritten = true;
	}
	writeRow();
}

void eeg::CSVWriter::writeHeader()
{
	for (auto columnId = 0; columnId < _model->columnCount(); ++columnId)
	{
		_stream << _model->columnName(columnId);
		if (columnId < _model->columnCount() - 1)
			_stream << ";";
	}
	_stream << "\n";
	_stream.flush();
}

void eeg::CSVWriter::writeRow()
{
	for (auto columnId = 0; columnId < _model->columnCount(); ++columnId)
	{
		_stream << _model->data(columnId);
		if (columnId < _model->columnCount() - 1)
			_stream << ";";
	}
	_stream << "\n";
	_stream.flush();
}
