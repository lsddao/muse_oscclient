#pragma once

#include <QWidget>

#include "EEGSession.h"
#include "SimpleCSVDataModel.h"

class QPushButton;
class QLabel;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void startSession();
	void stopSession();
	void updateStatus();
	void nextTrack();

protected:
	void setupUi();
	void initEEGSession();

	void keyPressEvent(QKeyEvent* ev) override;

private:
	QPushButton* btnStartSession;
	QPushButton* btnStopSession;
	QPushButton* quitButton;
	QPushButton* btnNext;

	QLabel* lblStatus;

	eeg::DataHandler _handler;
	eeg::EEGSession _session;
	eeg::TestDataModel _model;
};