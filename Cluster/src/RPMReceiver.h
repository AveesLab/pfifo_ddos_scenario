#ifndef RPMRECEIVER_H
#define RPMRECEIVER_H

#include <QObject>
#include <iostream>

class RPMReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rpmValue READ rpmValue NOTIFY rpmValueChanged)

public:
    explicit RPMReceiver(QObject *parent = nullptr);
    int rpmValue() const { return qt_rpmValue; }

signals:
    void rpmValueChanged();

public slots:
    void receiveRPM(int signal);

private:
    int qt_rpmValue = 0;
};

#endif // RPMOUTPUT_H
