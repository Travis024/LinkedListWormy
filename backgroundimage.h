#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class BackgroundImage : public QGraphicsPixmapItem
{
public:
    BackgroundImage(QString image_path); //Creates an instance of the class with an image depending on the image path passed through

};
#endif // BACKGROUNDIMAGE_H
