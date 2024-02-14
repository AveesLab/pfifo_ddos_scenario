#ifndef BUTTONSRECEIVER_H
#define BUTTONSRECEIVER_H

#include <QObject>
#include <QString>

class ButtonsReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buttonsValue READ buttonsValue NOTIFY buttonsValueChanged)

public:
    explicit ButtonsReceiver(QObject *parent = nullptr);
    QString buttonsValue() const { return qt_buttons; }

signals:
    void buttonsValueChanged();

public slots:
    void receiveButtons(std::string signal);

private:
    QString qt_buttons;
};

#endif // BUTTONSRECEIVER_H
