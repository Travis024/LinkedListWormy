#include "pellet.h"

Pellet::Pellet()
{
    QImage * image_object = new QImage();
    image_object->load(":/imgs/imgs/pellet.png");

    //create the Pixamp and set the image
    QPixmap final_pixmap = QPixmap::fromImage(*image_object);
    setPixmap(QPixmap(final_pixmap));

    //Load the pellet eaten sound into the media player
    this -> pellet_media_player_ = new QMediaPlayer;
    this -> pellet_media_player_ -> setMedia(QUrl("qrc:/sounds/sounds/pelletEaten.wav"));
}

void Pellet::PlaySound(){
    if(pellet_media_player_ -> state() == QMediaPlayer::PlayingState){
        this -> pellet_media_player_ -> setPosition(0);
    }else{
       this -> pellet_media_player_ -> play();
    }
}
