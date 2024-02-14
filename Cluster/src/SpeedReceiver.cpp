#include "SpeedReceiver.h"

SpeedReceiver::SpeedReceiver(QObject *parent) : QObject(parent)
{
}

void SpeedReceiver::receiveSpeed(int speed)
{
    qt_speedValue = speed;
    emit speedValueChanged();
}

