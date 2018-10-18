#include "CSVWriter.h"

#include <QDebug>

eeg::CSVWriter::CSVWriter(const QString& fileName, ICSVDataModel* model)
	: _file(fileName)
	, _model(model)
{
	
}

eeg::CSVWriter::~CSVWriter()
{
	_stream.flush();
	_file.close();
}

void eeg::CSVWriter::consume()
{
	if (!_file.isOpen())
	{
		_file.open(QIODevice::WriteOnly);
		_stream.setDevice(&_file);
	}
	if (!_headerWritten)
	{
		writeHeader();
		_headerWritten = true;
	}
	writeRow();
	_model->resetAllEvents();
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
