#include <QCoreApplication>
#include <QtConcurrent>

#include "EEGSession.h"
#include "CSVWriter.h"

#include "SimpleCSVDataModel.h"

using namespace eeg;

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	DataHandler handler;
	QtConcurrent::run([&handler]() 
	{
		handler.run();
	});

	EEGSession session(handler.data());
	//session.addDataConsumer(new SimpleDataConsumer);

	TestDataModel model;
	model.setEEGData(handler.data());

	session.addDataConsumer(new CSVWriter("text.csv", &model));
	session.start(250);

    return app.exec();
}
