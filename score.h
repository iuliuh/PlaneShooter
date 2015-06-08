//Score widget
#ifndef SCOR_H
#define SCOR_H

#include <QWidget>
#include <QObject>

class QLCDNumber;
class QLabel;
class QHBoxLayout;

class Score : public QWidget
{
    Q_OBJECT

    QLCDNumber *score;
    QLabel *label;
    QHBoxLayout *layout;

public:
    Score(QWidget *parent = NULL);
    Score(const QString &text, QWidget *parent = NULL);

public slots:
    void show(int newValue);
};

#endif
