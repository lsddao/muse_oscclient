#include <QtWidgets>
#include <QDateTime>
#include <QtConcurrent>	

#include "MainWindow.h"
#include "CSVWriter.h"

#include <windows.h>

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

	btnNext = new QPushButton("Next track");
	connect(btnNext, SIGNAL(clicked()), this, SLOT(nextTrack()));

	QVBoxLayout *btnLayout = new QVBoxLayout;
	btnLayout->addWidget(btnStartSession);
	btnLayout->addWidget(btnStopSession);
	btnLayout->addWidget(btnNext);
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

void MainWindow::nextTrack()
{
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = VK_MEDIA_NEXT_TRACK; 
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	_model.setEventTriggered();
	updateStatus();
}

void MainWindow::keyPressEvent(QKeyEvent* ev)
{
	/*if (ev->key() == Qt::Key_MediaNext)
	{
		_model.setEventTriggered();
		updateStatus();
	}*/
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
		QString("Session: \t\t%1\nNext track pressed: \t%2\nTouching forehead: \t%3\nContact quality(L): \t%4\nContact quality(R): \t%5\nEEG_good(L): \t\t%6\nEEG_good(R): \t\t%7")
		.arg(_session.running() ? "running" : "stopped")
		.arg(_model.eventTriggered() ? "true" : "false")
		.arg(_handler.data()->touchingForehead ? "true" : "false")
		.arg((int) _handler.data()->quality[eeg::Data::EEG2])
		.arg((int) _handler.data()->quality[eeg::Data::EEG3])
		.arg(_handler.data()->isEegGood[eeg::Data::EEG2] ? "true" : "false")
		.arg(_handler.data()->isEegGood[eeg::Data::EEG3] ? "true" : "false")
	);
}
