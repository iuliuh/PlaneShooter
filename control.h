#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QObject>
//Cannon control widget
class QLCDNumber;
class QSlider;
class QLabel;
class QVBoxLayout;

class Control : public QWidget
{
    Q_OBJECT

    QSlider *slider;
    QLCDNumber *lcd;
    QLabel *label;
    QVBoxLayout *layout;

public:
    Control(QWidget *parent = NULL);
    Control(const QString &text, QWidget *parent = NULL);

public slots:
    void setRange(int minValue, int maxValue);
    void setValue(int newValue);

signals:
    void valueChanged(int);
};

#endif
