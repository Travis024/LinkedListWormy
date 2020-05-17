#ifndef LINKEDLISTWORMYWINDOW_H
#define LINKEDLISTWORMYWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include "backgroundimage.h"
#include "gamebutton.h"
#include "linkedlistwormydialog.h"
#include "worm.h"
#include "pellet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LinkedListWormyWindow; }
QT_END_NAMESPACE

class LinkedListWormyWindow : public QMainWindow
{
    Q_OBJECT

public:
    LinkedListWormyWindow(QWidget *parent = nullptr);
    ~LinkedListWormyWindow();

    void SetBackgrounds(); //Initialize both of the two backgrounds used in the game
    void ChangeBackgrounds(); //Add and remove backgrounds backgrounds depending on the state of the game

    void SetButtons(); //Initialize the button fields and add the start and about button to the scene
    void ChangeButtons(); //Add and remove buttons to and from the scene depending on the state of the game
    void HideButtons(); //Hides all of the buttons when the worm is being traversed or the game is being played

    void InitializeWorm(); //When the Start button is pressed, create a worm that only has a head

    void keyPressEvent(QKeyEvent * e); //Used for changing the direction of the head when an arrow key is pressed

    void PlacePellet(bool initialize); //Place a pellet in a random position; if initialize is true, create a new pellet, if false, just move its position

    void CustomCursor(); //Sets a custom cursor for the game


private slots:

    void ShowButtons(); //Shows all of the buttons after the action that hid the buttons is completed

    void DialogSlot(QString identifier, QString dialog_text, bool gets_user_input); //Responds to a GameButton press that triggers a dialog action

    void StartSlot(); //Responds to the start button being pressed and begins the game

    void PassNodeValueSlot(int node_value); //Receives a value that is to be added or deleted from the dialog

    void TraverseSlot(); //Receives a signal that calls on the game_worm_ to utilize its Traverse method

    void PlaySlot(); //Receives a signal that tells the LinkedListWormyWindow to start the game

    void PelletEatenSlot(); //Checks to see if a pellet is underneath the head; if so, remove it, play a sound, and place a new pellet

    void GameOverSlot(); //When the game is over, stop playing music and show a dialog

private:
    Ui::LinkedListWormyWindow *ui;

    QGraphicsScene * game_scene_; //The game scene from the UI; this is the only UI element

    //All fields pertaining to background images
    BackgroundImage * menu_background_; //Store the image that is used as the menu background
    BackgroundImage * active_background_; //Store the image that is used as the active background
    int current_background_; //Keep track of the current background, where 0 = menu_background_ and 1 = active_background_

    //All fields pertaining to game buttons
    GameButton * start_button_;
    GameButton * about_button_;
    GameButton * add_button_;
    GameButton * delete_button_;
    GameButton * traverse_button_;
    GameButton * play_button_;
    int current_buttons_; //Keep track of the current set of buttons on the screen, where 0 = menu buttons and 1 = active buttons
    bool adding_node_; //Determine if the user has just pressed the Add button
    bool deleting_node_; //Determine if the user has just pressed the Delete button

    Worm * game_worm_; //The worm that is used to make a linked list and play the game
    WormBodyPiece * game_worm_head_; //The head that starts the game_worm_

    Pellet * current_pellet_; //The pellet that is place when the game begins playing and re-placed every time it is eaten

    bool is_playing_; //A bool to tell whether or not the game is playing, used so that key press events only register at that time

    LinkedListWormyDialog * dialog_window_; //The dialog window that acts as a pop-up window

    //All fields pertaining to playlist media
    QMediaPlaylist * background_playlist_; //Create a playlist that can loop
    QMediaPlayer * background_player_; //Play the above playlist
};
#endif // LINKEDLISTWORMYWINDOW_H
