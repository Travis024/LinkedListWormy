#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QObject>
#include <QMouseEvent>
#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>


class GameButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    GameButton(QString image_path, QString identifier, QString dialog_text, bool gets_user_input); //A GameButton is given an image path, an identifier, text-dialog for a pop-up that intiialzies on click, and a bool specifying whether or not user input must be returned as a result of pressing the button

    void mousePressEvent(QGraphicsSceneMouseEvent * /*unused*/) override; //Actions are taken when a button is presed (such as changing screens or creating a dialog

    void PlaySound(); //A wrapper for restarting the sound after it's been played and then playing it again; used so that mutliple sounds can occur from the same button

signals:

    void DialogSignal(QString identifier, QString dialog_text, bool gets_user_input); //Sends a signal to create a dialog with the given text and a user input functionality if true

    void StartSignal(); //Sends a signal when the start button is pressed to change from the menu screen to the active screen

    void TraverseSignal(); //Sends a signal when the traverse button is pressed to go from head to tail through the linked list/worm

    void PlaySignal(); //Sends a signal when the play button is pressed to start the wormy game
private:

    QString identifier_;

    QString dialog_text_; //Store the dialog text that appears in the pop-up window; this is set in the constructor

    bool gets_user_input_; //Store whether or not the pop-up window should take user input; this is set in the constructor

    QMediaPlayer * button_sound_player_; //The sound player, which stores a unique sound depending on the button; this is set in the constructor
};

#endif // GAMEBUTTON_H
