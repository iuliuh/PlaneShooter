#ifndef APLICATIE_H
#define APLICATIE_H

#include <QWidget>

class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;

class Application : public QWidget
{
    QGridLayout *layout;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;

public:
    Application(QWidget *parent = NULL);

};

#endif
