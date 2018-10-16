#pragma once

#include <QWidget>

#include "EEGSession.h"
#include "SimpleCSVDataModel.h"

class QPushButton;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void startSession();
	void stopSession();

protected:
	void setupUi();
	void initEEGSession();

	void keyPressEvent(QKeyEvent* ev) override;

private:
	QPushButton* btnStartSession;
	QPushButton* btnStopSession;
	QPushButton* quitButton;

	eeg::DataHandler _handler;
	eeg::EEGSession _session;
	eeg::TestDataModel _model;
};