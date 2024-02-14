#include "DetectsReceiver.h"

DetectsReceiver::DetectsReceiver(QObject *parent) : QObject(parent)
{
}

void DetectsReceiver::receiveDetects(std::string detection)
{
    qt_detects = QString::fromStdString(detection);
    emit detectsValueChanged();
}
