#ifndef IMAGERECEIVER_H
#define IMAGERECEIVER_H


#include <QObject>
#include <iostream>

class ImageReceiver : public QObject
{

public:
    explicit ImageReceiver(QObject *parent = nullptr);

public slots:
    void receiveRPM(int signal);
};

#endif // IMAGERECEIVER_H
