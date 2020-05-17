#include "gamebutton.h"
#include <QDebug>

/*
The constructor for the GameButton sets the object's identifier, image, and dialog text and user input fields for if the button triggers a dialog

@param: The image path, dialog text, and user inout true/false
@return: A GameButton which is a QGraphicsPixmapItem, is created with its fields set
*/
GameButton::GameButton(QString image_path, QString identifier, QString dialog_text, bool gets_user_input)
{
    //create an image object by loading the image path
    QImage * image_object = new QImage();
    image_object->load(image_path);

    //create the Pixamp and set the background
    QPixmap final_pixmap = QPixmap::fromImage(*image_object);
    setPixmap(QPixmap(final_pixmap));

    //fill class fields using the parameters passed through
    this -> dialog_text_ = dialog_text;
    this -> gets_user_input_ = gets_user_input;
    this -> identifier_ = identifier;

    //Create the media player and set the sound
    this -> button_sound_player_ = new QMediaPlayer();
    this -> button_sound_player_ -> setMedia(QUrl("qrc:/sounds/sounds/genericButtonClick.wav"));

}

/*
On a mouse press event, the majority of buttons trigger a dialog
A few select buttons trigger other actions
All buttons trigger a sound from the media player

@param: None
@return: The proper action is triggered depending on the type of button
*/
void GameButton::mousePressEvent(QGraphicsSceneMouseEvent * /*unused*/){

    this -> PlaySound(); //play the button's sound, which is set in the constructor

    if(this -> identifier_ == "__start_button__"){
        emit StartSignal();
    }else if(this -> identifier_ == "__traverse_button__"){
        emit TraverseSignal();
    }else if(this -> identifier_ == "__play_button__"){
        emit PlaySignal();
    }else{
        emit DialogSignal(this -> identifier_, this -> dialog_text_, this -> gets_user_input_);
    }
}

/*
A wrapper function to help with playing sound when a button is pressed
Ensures that after a sound has been played it is reset to the start or the sound file

@param: None
@return: The sound that belongs to the button is played
*/
void GameButton::PlaySound(){
    if(button_sound_player_ -> state() == QMediaPlayer::PlayingState){
        this -> button_sound_player_ -> setPosition(0);
    }else{
       this -> button_sound_player_ -> play();
    }
}
