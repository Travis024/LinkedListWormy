#include "backgroundimage.h"

/*
The constructor for the BackgroundImage sets the object's image using an image path

@param: The image path
@return: A BackgroundImage, which is a QGraphicsPixmapItem, is created with the appropriate image
*/
BackgroundImage::BackgroundImage(QString image_path)
{
    //create an image object by loading the image path
    QImage * image_object = new QImage();
    image_object->load(image_path);

    //create the Pixamp and set the background
    QPixmap final_pixmap = QPixmap::fromImage(*image_object);
    setPixmap(QPixmap(final_pixmap));
}
