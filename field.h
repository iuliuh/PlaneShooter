#ifndef CAMP_H
#define CAMP_H

#include <QWidget>
#include <QObject>

class QTimer;

class Field : public QWidget
{
    Q_OBJECT

    int currentAngle;
    int shootingAngle;
    int shootingForce;
    int currentForce;
    int currentTime;
    int planeTime;

    int hitTarget;
    int missedTarget;

    int randomPosition;

    QTimer *counter;
    QTimer *planeCounter;

    QRect projectilePosition() const;
    QRect targetPosition() const;

    QImage background;
    QImage projectile;
    QImage wheel;
    QImage cannon;
    QImage ammunition;
    QImage plane;

    void drawProjectile(QPainter &painter);
    void drawCannon(QPainter &painter);
    void drawTarget(QPainter &painter);

public:
    Field(QWidget *parent = NULL);
    void paintEvent(QPaintEvent *);

public slots:
    void setAngle(int newAngle);
    void setForce(int newForce);

    void shootProjectile();
    void moveProjectile();
    void movePlane();

    void reset();

signals:
    void angleChanged(int newAngle);
    void forceChanged(int newForce);
    void hit(int value);
    void missed(int value);
};

#endif
