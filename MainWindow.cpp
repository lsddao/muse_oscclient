#include <QtWidgets>
#include <QDateTime>
#include <QtConcurrent>	

#include "MainWindow.h"
#include "CSVWriter.h"

MainWindow::MainWindow()
{
	setupUi();
	initEEGSession();
}

MainWindow::~MainWindow()
{
	//_handler.stop();
}

void MainWindow::setupUi()
{
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	btnStartSession = new QPushButton("Start session");
	connect(btnStartSession, SIGNAL(clicked()), this, SLOT(startSession()));

	btnStopSession = new QPushButton("Stop session");
	connect(btnStopSession, SIGNAL(clicked()), this, SLOT(stopSession()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(btnStartSession);
	mainLayout->addWidget(btnStopSession);
	mainLayout->addWidget(quitButton);
	setLayout(mainLayout);
}

void MainWindow::initEEGSession()
{
	using namespace eeg;

	// start listening
	QtConcurrent::run([&]() { this->_handler.run(); });

	_session.setData(_handler.data());
	_model.setEEGData(_handler.data());

	_session.addDataConsumer(new CSVWriter(QString("session_%1.csv").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")), &_model));
}

void MainWindow::keyPressEvent(QKeyEvent* ev)
{
	if (ev->key() == Qt::Key_MediaNext)
	{
		_model.setEventTriggered();
	}
}

void MainWindow::startSession()
{
	_session.start(250);
}

void MainWindow::stopSession()
{
	_session.stop();
}
