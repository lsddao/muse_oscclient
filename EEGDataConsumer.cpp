#include "EEGDataConsumer.h"

#include <QMap>
#include <QString>
#include <QDebug>

void eeg::SimpleDataConsumer::consume()
{
	static QMap<short, QString> decision;
	if (decision.isEmpty())
	{
		decision[-1] = "don't like :(";
		decision[0] = "ok";
		decision[1] = "cool! :)";
	}

	double left = _data->absoluteFreq[Data::EEG2][Data::Beta];
	double right = _data->absoluteFreq[Data::EEG3][Data::Beta];

	double diff = left - right;
	short diff_quanted = 0;
	if (diff < -0.25)
		diff_quanted = -1;
	else if (diff > 0.25)
		diff_quanted = 1;

	qDebug() << decision[diff_quanted];
}