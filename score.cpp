//Score sidget
#include <QWidget>
#include <QObject>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QLabel>

#include "score.h"

Score::Score(QWidget *parent) : QWidget(parent)
{
    score = new QLCDNumber(4);
    score->setSegmentStyle(QLCDNumber::Filled);
    score->display(0);

    layout = new QHBoxLayout;
    layout->addWidget(score);
    setLayout(layout);
}

Score::Score(const QString &text, QWidget *parent) : QWidget(parent)
{
    score = new QLCDNumber(4);
    score->setSegmentStyle(QLCDNumber::Filled);
    score->display(0);

    label = new QLabel;
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);

    layout = new QHBoxLayout;
    layout->addWidget(score);
    layout->addWidget(label);
    setLayout(layout);
}

void Score::show(int newValue)
{
    score->display(newValue);
}
