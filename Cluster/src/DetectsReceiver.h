#ifndef DETECTSRECEIVER_H
#define DETECTSRECEIVER_H

#include <QObject>
#include <QString>

class DetectsReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString detectsValue READ detectsValue NOTIFY detectsValueChanged)

public:
    explicit DetectsReceiver(QObject *parent = nullptr);
    QString detectsValue() const { return qt_detects; }

signals:
    void detectsValueChanged();

public slots:
    void receiveDetects(std::string signal);

private:
    QString qt_detects;
};

#endif // DETECTSRECEIVER_H
