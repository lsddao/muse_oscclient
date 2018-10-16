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

protected:
	void setupUi();
	void initEEGSession();

	void keyPressEvent(QKeyEvent* ev) override;

private:
	QPushButton* btnStartSession;
	QPushButton* btnStopSession;
	QPushButton* quitButton;

	QLabel* lblStatus;

	eeg::DataHandler _handler;
	eeg::EEGSession _session;
	eeg::TestDataModel _model;
};