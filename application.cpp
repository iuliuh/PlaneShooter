#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "application.h"
#include "control.h"
#include "field.h"
#include "score.h"

Application::Application(QWidget *parent) : QWidget(parent)
{
    Control *angle = new Control(tr("ANGLE"));
    angle->setRange(5, 70);
    angle->setValue(45);

    Control *force = new Control(tr("FORCE"));
    force->setRange(10, 50);
    force->setValue(25);

    Score *hitScore = new Score(tr("HIT"));
    Score *missedScore = new Score(tr("MISSED"));

    Field *field = new Field;
    connect(angle, SIGNAL(valueChanged(int)),
            field, SLOT(setAngle(int)));
    connect(field, SIGNAL(angleChanged(int)),
            angle, SLOT(setValue(int)));

    connect(force, SIGNAL(valueChanged(int)),
            field, SLOT(setForce(int)));
    connect(field, SIGNAL(forceChanged(int)),
            force, SLOT(setValue(int)));

    connect(field, SIGNAL(hit(int)),
            hitScore, SLOT(show(int)));
    connect(field, SIGNAL(missed(int)),
            missedScore, SLOT(show(int)));

    QPushButton *shoot = new QPushButton(tr("&Shoot"));
    shoot->setFont(QFont("Times", 20, QFont::Bold));
    shoot->setFixedSize(150, 50);

    connect(shoot, SIGNAL(clicked()),
            field, SLOT(shootProjectile()));

    QPushButton *quit = new QPushButton(tr("&Quit"));
    quit->setFont(QFont("Times", 20, QFont::Bold));
    quit->setFixedSize(150, 50);

    connect(quit, SIGNAL(clicked()),
            this, SLOT(close()));

    QPushButton *newGame = new QPushButton(tr("&New Game"));
    connect(newGame, SIGNAL(clicked()),
            field, SLOT(reset()));
    newGame->setFont(QFont("Times", 18, QFont::Bold));
    newGame->setFixedSize(150, 50);

    layout = new QGridLayout;
    hlayout = new QHBoxLayout;
    vlayout = new QVBoxLayout;

    hlayout->addWidget(newGame);
    hlayout->addWidget(shoot);
    hlayout->addWidget(hitScore);
    hlayout->addWidget(missedScore);

    vlayout->addWidget(angle);
    vlayout->addWidget(force);

    layout->addWidget(quit, 0, 0);
    layout->addLayout(hlayout, 0, 1);
    layout->addLayout(vlayout, 1, 0);
    layout->addWidget(field, 1, 1, 2, 1);
    layout->setColumnStretch(1, 10);

    setLayout(layout);
}
