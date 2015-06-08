//Cannon control widget
#include <QWidget>
#include <QObject>
#include <QLCDNumber>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>

#include "control.h"

Control::Control(QWidget *parent) : QWidget(parent)
{
    lcd = new QLCDNumber(2);
    lcd->setSegmentStyle(QLCDNumber::Filled);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 99);
    slider->setValue(0);

    connect(slider, SIGNAL(valueChanged(int)),
            lcd, SLOT(display(int)));

    connect(slider, SIGNAL(valueChanged(int)),
            this, SIGNAL(valueChanged(int)));

    layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(slider);

    setLayout(layout);
}

Control::Control(const QString &text, QWidget *parent) : QWidget(parent)
{
    lcd = new QLCDNumber(2);
    lcd->setSegmentStyle(QLCDNumber::Filled);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 99);
    slider->setValue(0);

    connect(slider, SIGNAL(valueChanged(int)),
            lcd, SLOT(display(int)));

    connect(slider, SIGNAL(valueChanged(int)),
            this, SIGNAL(valueChanged(int)));

    label = new QLabel;
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);

    layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(slider);
    layout->addWidget(label);

    setLayout(layout);
}

void Control::setRange(int minValue, int maxValue)
{
    if(minValue < 0 || maxValue > 99 || minValue > maxValue)
    {
        minValue = 0;
        maxValue = 99;
        return;
    }
    slider->setRange(minValue, maxValue);
}

void Control::setValue(int newValue)
{
    slider->setValue(newValue);
}
