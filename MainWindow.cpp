#include <QtWidgets>
#include <QDateTime>
#include <QtConcurrent>	

#include "MainWindow.h"
#include "CSVWriter.h"

MainWindow::MainWindow()
{
	setupUi();
	initEEGSession();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));
	timer->start(1000);
}

MainWindow::~MainWindow()
{
	//_handler.stop();
}

void MainWindow::setupUi()
{
	lblStatus = new QLabel;

	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	btnStartSession = new QPushButton("Start session");
	connect(btnStartSession, SIGNAL(clicked()), this, SLOT(startSession()));

	btnStopSession = new QPushButton("Stop session");
	connect(btnStopSession, SIGNAL(clicked()), this, SLOT(stopSession()));

	QVBoxLayout *btnLayout = new QVBoxLayout;
	btnLayout->addWidget(btnStartSession);
	btnLayout->addWidget(btnStopSession);
	btnLayout->addWidget(quitButton);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(lblStatus);
	mainLayout->addLayout(btnLayout);
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
		updateStatus();
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

void MainWindow::updateStatus()
{
	lblStatus->setText(
		QString("Session: %1\nNext track pressed: %2\nTouching forehead: %3\nContact quality L: %4\nContact quality R: %5\nBeta power L-R: %6\n")
		.arg(_session.running() ? "running" : "stopped")
		.arg(_model.eventTriggered() ? "true" : "false")
		.arg(_handler.data()->touchingForehead ? "ok" : "bad")
		.arg((int) _handler.data()->quality[eeg::Data::EEG2])
		.arg((int) _handler.data()->quality[eeg::Data::EEG3])
		.arg(_model.data(2))
	);
}
