#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

#include <math.h>
#include <cstdlib>

#include "field.h"

Field::Field(QWidget *parent) : QWidget(parent)
{
    // Timers to control elements rendering
    counter = new QTimer(this);
    planeCounter = new QTimer(this);

    currentTime = 0;
    planeTime = 0;

    // Initial cannon angle
    currentAngle = 45;
    // Initial cannon force
    currentForce = 25;

    // Hit counter
    hitTarget = 0;
    // Missed counter
    missedTarget = 0;

    // Plane y axis position
    randomPosition = (rand() % -200) - 300;

    // Visual elements
    background = QImage(":/images/background");
    projectile = QImage(":/images/bomb");
    cannon = QImage(":/images/canon");
    wheel = QImage(":/images/wheel");
    ammunition = QImage(":/images/ammunition");
    plane = QImage(":/images/plane");

    planeCounter->start(10);

    // Everytime counter timeouts new projectile position is calculated
    connect(counter, SIGNAL(timeout()),
            this, SLOT(moveProjectile()));

    // Everytime counter timeouts new plane position is calculated
    connect(planeCounter, SIGNAL(timeout()),
            this, SLOT(movePlane()));

    this->setFixedSize(800, 300);
}

void Field::setAngle(int newAngle)
{
    // Updates view each time angle changes
    currentAngle = newAngle;
    emit angleChanged(currentAngle);
    update();
}

void Field::setForce(int newForce)
{
    currentForce = newForce;
    emit forceChanged(newForce);
}

void Field::paintEvent(QPaintEvent *)
{
    // Takes care of the rendering part
    QPainter painter(this);

    drawCannon(painter);
    painter.rotate(currentAngle);
    drawTarget(painter);

    painter.rotate(-currentAngle);

    if (counter->isActive())
             drawProjectile(painter);
}

void Field::drawCannon(QPainter &painter)
{
    // Cannon is drawn
    QRectF target_fundal(0.0, 0.0, 800.0, 300.0);
    QRectF source_fundal(0.0, 0.0, 800.0, 300.0);

    painter.drawImage(target_fundal, background, source_fundal);

    painter.translate(20, this->height()-20);

    QRectF target_tun(-10.0, -35.0, 70.0, 70.0);
    QRectF source_tun(0.0, 0.0, 50.0, 50.0);

    QRectF target_roata(-15.0, -15.0, 70.0, 70.0);
    QRectF source_roata(0.0, 0.0, 100.0, 100.0);

    QRectF target_munitie(60.0, 0.0, 70.0, 70.0);
    QRectF source_munitie(0.0, 0.0, 100.0, 100.0);

    painter.rotate(-currentAngle);
    painter.drawImage(target_tun, cannon, source_tun);

    painter.rotate(currentAngle);
    painter.drawImage(target_roata, wheel, source_roata);
    painter.drawImage(target_munitie, ammunition, source_munitie);
    painter.rotate(-currentAngle);
}

void Field::drawProjectile(QPainter &painter)
{
    // Projectile is drawn
    painter.rotate(currentAngle);
    painter.drawImage(projectilePosition(), projectile);
}

void Field::drawTarget(QPainter &painter)
{
    // Plane is drawn
    painter.drawImage(targetPosition(), plane);
}

QRect Field::projectilePosition() const
{
    // Projectile position is calculated
    #define PI 3.14159265
    double gravitatie = 4;

    double rad = shootingAngle * PI/180;
    double timp = currentTime / 10.;

    double x_i = 50 * cos(rad) + currentTime;
    double y_i = 70 * sin(rad) + currentTime;

    double x = x_i + (shootingForce * cos(rad)) * timp;
    double y = y_i + (shootingForce * sin(rad)) * timp -
               0.5 * gravitatie * pow(timp, 2);

    QRect proiectil(x, -y, 20, 20);

    return proiectil;
}

QRect Field::targetPosition() const
{
    // A random y axis position is calculated for the plane
    QRect tinta(1000 - planeTime, randomPosition, 100, 68);

    return tinta;
}

void Field::shootProjectile()
{
    // If no projectile is already shot, one projectile is shot
    if(counter->isActive())
        return;

    shootingAngle = currentAngle;
    shootingForce = currentForce;

    counter->start(10);
}

void Field::moveProjectile()
{
    // Calculates projectile position
    ++currentTime;

    QRect proiectilAux = projectilePosition();

    if (proiectilAux.x() > width() ||
        proiectilAux.y() > height())
    {
        counter->stop();
        currentTime = 0;
    }

    if (proiectilAux.intersects(targetPosition()))
    {
        counter->stop();
        currentTime = 0;
        planeTime = 0;

        ++hitTarget;
        randomPosition = (rand() % -200) - 300;

        emit hit(hitTarget);
    }

    update();
}

void Field::movePlane()
{
    // Plane moves on the x axis
    ++planeTime;

    if(planeTime == 1200)
    {
        planeTime = 0;
        randomPosition = (rand() % -200) - 300;
        ++missedTarget;

        emit missed(missedTarget);
    }

    // Determine weather player lost the game
    if (missedTarget == 3)
    {
        QMessageBox msgBox;
        msgBox.setText("You lost!");
        msgBox.exec();
        reset();
    }

    // Determine weather player won the game
    if(hitTarget == 4)
    {
        QMessageBox msgBox;
        msgBox.setText("You won!");
        msgBox.exec();
        reset();
    }

    update();
}

void Field::reset()
{
    // Everything is reset
    currentTime = 0;
    planeTime = 0;
    currentAngle = 45;
    currentForce = 25;

    hitTarget = 0;
    missedTarget = 0;

    emit missed(missedTarget);
    emit hit(hitTarget);

    randomPosition = (rand() % -200) - 300;

    planeCounter->start(5);
}
