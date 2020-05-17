#ifndef PELLET_H
#define PELLET_H

#include <QObject>
#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Pellet : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT


public:
    Pellet();

    void PlaySound();

private:

    QMediaPlayer * pellet_media_player_; //Plays the sound when a pellet is eaten
};

#endif // PELLET_H
