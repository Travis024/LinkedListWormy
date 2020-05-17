#include "linkedlistwormywindow.h"
#include "ui_linkedlistwormywindow.h"
#include <QDebug>

LinkedListWormyWindow::LinkedListWormyWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LinkedListWormyWindow)
{
    //The UI must be set up before the scene can be drawn on
    this -> ui -> setupUi(this);

    //the QGraphicsView is the UI element that contains the scene that is drawn on
    //this section of code sets the scene and ensures that scroll bars are turned off
    QGraphicsView *gameView = this -> ui ->graphicsView;
    this -> game_scene_ = new QGraphicsScene;
    gameView -> setScene(this -> game_scene_);
    gameView -> setSceneRect(0,0,gameView->frameSize().width(), gameView -> frameSize().height());
    gameView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    gameView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    //Add the custom font to this application
    QFontDatabase::addApplicationFont(":/fonts/fonts/Born2bSportyV2.ttf");

    //Initialize the media playlist with the menu background music and set the mode so that the music loops
    this -> background_playlist_ = new QMediaPlaylist();
    this -> background_playlist_ -> addMedia(QUrl("qrc:/sounds/sounds/menuMusic.wav"));
    this -> background_playlist_ -> setPlaybackMode(QMediaPlaylist::Loop);

    //Set the is_playing field to denote that key press events should not register
    this -> is_playing_ = false;

    //Intiailize the media player with the playlist created above, decrease the volume, and play
    this -> background_player_ = new QMediaPlayer();
    this -> background_player_ -> setPlaylist(this -> background_playlist_);
    this -> background_player_ -> setVolume(10);
    this -> background_player_ -> play();

    //Set the custom cursor
    this -> CustomCursor();

    //Initialize the backgrounds that are used in the game
    this -> SetBackgrounds();

    //Initialize the buttons that are used in the game
    this -> SetButtons();

}

LinkedListWormyWindow::~LinkedListWormyWindow()
{
    delete this -> ui;
}

/*
Initialize the two backgrounds that are used in the game
There is the menu background, used upon initialization, and the active background, used when the game is being played

@param: None
@return: The two background fields of the LinkedListWormyClass are set
*/
void LinkedListWormyWindow::SetBackgrounds(){

    this -> menu_background_ = new BackgroundImage(":/imgs/imgs/menuBackground.png");
    this -> active_background_ = new BackgroundImage(":imgs/imgs/activeBackground.png");

    this -> game_scene_ -> addItem(this -> menu_background_);

    this -> current_background_ = 0;

}

/*
Change between the two backgrounds that are used in the game
Removes the current background and adds the appropraite background to the scene

@param: None
@return: Change from menu_background_ to active_background or vice versa
*/
void LinkedListWormyWindow::ChangeBackgrounds(){
    if(this -> current_background_ == 0){
        this -> game_scene_ -> removeItem(menu_background_);
        this -> game_scene_ -> addItem(active_background_);
        this -> current_background_ = 1;
    }else{
        this -> game_scene_ -> removeItem(active_background_);
        this -> game_scene_ -> addItem(menu_background_);
        this -> current_background_ = 0;
    }
}

/*
Initialize the buttons that are used in the game
These buttons exist on both the menu screen and athe active screen
While all button fields are intialized (meaning signals and slots connected, positions set), only the start and about buttons are added to the scene at first.

Set current_buttons_ to reflect that the menu buttons are currently on the screen

@param: None
@return: All button fields are initialized and the start and about buttons are added to the scene
*/
void LinkedListWormyWindow::SetButtons(){
    this -> start_button_ = new GameButton(":/imgs/imgs/startButton.png", "__start_button__", "", false);
    this -> about_button_ = new GameButton(":/imgs/imgs/aboutButton.png", "__about_button__", "Linked List + Wormy is a game that allows users to explore Linked List data structures... and then play a fun game! Users can add nodes, delete nodes, and traverse their list before playing Wormy, the classic game where you play as a worm eating pellets.", false);

    this -> add_button_ = new GameButton(":/imgs/imgs/addButton.png", "__add_button__", "Enter a value between 0 and 99 to add to the linked list!", true);
    this -> delete_button_ = new GameButton(":/imgs/imgs/deleteButton.png", "__delete_button__", "Choose a value to delete from the linked list. If the value exists, it will dissappear!", true);
    this -> traverse_button_ = new GameButton(":/imgs/imgs/traverseButton.png", "__traverse_button__", "", false);
    this -> play_button_ = new GameButton(":/imgs/imgs/playButton.png", "__play_button__", "", false);

    this -> add_button_ -> setScale(0.75);
    this -> delete_button_ -> setScale(0.75);
    this -> traverse_button_ -> setScale(0.75);
    this -> play_button_ -> setScale(0.75);

    connect(this -> start_button_, &GameButton::StartSignal, this, &LinkedListWormyWindow::StartSlot);
    connect(this -> about_button_, &GameButton::DialogSignal, this, &LinkedListWormyWindow::DialogSlot);
    connect(this -> add_button_, &GameButton::DialogSignal, this, &LinkedListWormyWindow::DialogSlot);
    connect(this -> delete_button_, &GameButton::DialogSignal, this, &LinkedListWormyWindow::DialogSlot);
    connect(this -> traverse_button_, &GameButton::TraverseSignal, this, &LinkedListWormyWindow::TraverseSlot);
    connect(this -> play_button_, &GameButton::PlaySignal, this, &LinkedListWormyWindow::PlaySlot);

    this -> start_button_ -> setPos(70, 380);
    this -> about_button_ -> setPos(290, 380);
    this -> add_button_ -> setPos(120, 2);
    this -> delete_button_ -> setPos(300, 2);
    this -> traverse_button_ -> setPos(120, 480);
    this -> play_button_ -> setPos(300, 480);

    this -> game_scene_ -> addItem(this -> start_button_);
    this -> game_scene_ -> addItem(this -> about_button_);

    this -> current_buttons_ = 0;
}

/*
A helper function to change the buttons currently on the scene when switxhing between the menu and active portions of the game

@param: None
@return: The scene removes the current buttons and adds the opposite set of buttons the screen. The current_buttons_ field is updated to reflect the change
*/
void LinkedListWormyWindow::ChangeButtons(){
    if(this -> current_buttons_ == 0){
        this -> game_scene_ -> removeItem(this -> start_button_);
        this -> game_scene_ -> removeItem(this -> about_button_);

        this -> game_scene_ -> addItem(this -> add_button_);
        this -> game_scene_ -> addItem(this -> delete_button_);
        this -> game_scene_ -> addItem(this -> traverse_button_);
        this -> game_scene_ -> addItem(this -> play_button_);

        this -> current_buttons_ = 1;
    }else{
        this -> game_scene_ -> removeItem(this -> add_button_);
        this -> game_scene_ -> removeItem(this -> delete_button_);
        this -> game_scene_ -> removeItem(this -> traverse_button_);
        this -> game_scene_ -> removeItem(this -> play_button_);

        this -> game_scene_ -> addItem(this -> start_button_);
        this -> game_scene_ -> addItem(this -> about_button_);

        this -> current_buttons_ = 0;
    }
}

/*
A function to hide the buttons when traversing or when the game is being played

@param: None
@return: The buttons on the screen are hidden
*/
void LinkedListWormyWindow::HideButtons(){
    this -> traverse_button_ -> hide();
    this -> play_button_ -> hide();
    this -> add_button_ -> hide();
    this -> delete_button_ -> hide();
}

/*
 A function to show the buttons after the action that hid them is over

 @param: None
 @return: The buttons show back up on the screen
 */
void LinkedListWormyWindow::ShowButtons(){
    this -> traverse_button_ -> show();
    this -> play_button_ -> show();
    this -> add_button_ -> show();
    this -> delete_button_ -> show();
}

/*
When the start button is pressed, create a new worm and connect signals and slots

@param: None
@return: A new worm is created, consisting of just a head, and appears on the screen
*/
void LinkedListWormyWindow::InitializeWorm(){
    this -> game_worm_ = new Worm();
    connect(this -> game_worm_, &Worm::TimerFinished, this, &LinkedListWormyWindow::ShowButtons);
    connect(this -> game_worm_, &Worm::PelletEatenSignal, this, &LinkedListWormyWindow::PelletEatenSlot);
    connect(this -> game_worm_, &Worm::GameOverSignal, this, &LinkedListWormyWindow::GameOverSlot);

    this -> game_worm_head_ = this -> game_worm_ -> get_head_();
    game_scene_ -> addItem(this -> game_worm_head_);
}

/*
Change the cursor to a custom image

@param: None
@return: The cursor is set to a custom image
*/
void LinkedListWormyWindow::CustomCursor(){
    //create an image object by loading the image path
    QImage * image_object = new QImage();
    image_object->load(":/imgs/imgs/blackCursor.png");

    //create the Pixamp and set its hot point to -1, -1 (the point where clicks are registered)
    QPixmap final_pixmap = QPixmap::fromImage(*image_object);
    QCursor * custom_cursor = new QCursor(final_pixmap, -1, -1);
    this -> setCursor(*custom_cursor);
}

/*
Respond to a button press that triggers a dialog by reating and showing the dialog with the custom text and a possible field for user input
The dialog is connect to the window so that, if the user inputs a value, that value can be returned to the window
The dialog also checks for which button has been pressed for setting certain fields in the LinkedListWormyWindow

@param: The button identifier, dialog text, and a bool for whether or not user input is required
@return: A LinkedListWormyDialog is created and shown on top of this window
*/
void LinkedListWormyWindow::DialogSlot(QString identifier, QString dialog_text, bool gets_user_input){

    //determine if the add or delete button has been pressed, or if it's just another button
    if(identifier == "__add_button__"){
        this -> adding_node_ = true;
        this -> deleting_node_ = false;

        //Check to see if the max size has been reached; if so, alert the user and DON'T allow anythign to be added by setting adding_node to false
        if(this -> game_worm_ -> get_current_size_() == this -> game_worm_ -> get_max_size_()){
            dialog_text = "This worm is full! Nothing more can be added.";
            gets_user_input = false;
            this -> adding_node_ = false;
        }

    }else if(identifier == "__delete_button__"){
        this -> adding_node_ = false;
        this -> deleting_node_ = true;
    }else{
        this -> adding_node_ = false;
        this -> deleting_node_ = false;
    }

    this -> dialog_window_ = new LinkedListWormyDialog(this, dialog_text, gets_user_input);
    connect(this -> dialog_window_, &LinkedListWormyDialog::PassNodeValueSignal, this, &LinkedListWormyWindow::PassNodeValueSlot);
    this -> dialog_window_ -> show();
}

/*
Respond to the start button being pressed so that the game changes from the menu to the active screen

@param: None
@return: The backgrounds and buttons change, the worm is initialized,  and the music stops playing while the user updates their linked list (positon set to 0 so the music restarts at its beginning)
*/
void LinkedListWormyWindow::StartSlot(){
    this -> ChangeBackgrounds();
    this -> ChangeButtons();

    this -> background_player_ -> stop();
    this -> background_player_ -> setPosition(0);

    this -> InitializeWorm();
}

/*
When the game returns to the main window after a dialog, check to see if a worm body piece should be added or deleted
If adding, create the new body piece and pass it to the Worm class. Also add the corresponding text
If deleting, get a WormBodyPiece from the Worm, remove it from the scene, and delete it and its corresponding text

@param: The value that returns from the user input
@return: A new body piece is added or deleted from the linked list
*/
void LinkedListWormyWindow::PassNodeValueSlot(int node_value){
    if(this -> adding_node_ == true){

        WormBodyPiece * body_piece_to_add = new WormBodyPiece(1, node_value);
        this -> game_worm_ -> AddBodyPiece(body_piece_to_add);
        this -> game_scene_ -> addItem(body_piece_to_add);
        this -> game_scene_ -> addItem(body_piece_to_add -> get_points_as_text());

    }else if(this -> deleting_node_ == true){

        WormBodyPiece * body_piece_to_delete = this -> game_worm_ -> DeleteBodyPiece(node_value);

        //If the body piece was found (meaning the value exists), remove & delete it and its text
        if(body_piece_to_delete != nullptr){
            this -> game_scene_ -> removeItem(body_piece_to_delete);
            this -> game_scene_ -> removeItem(body_piece_to_delete -> get_points_as_text());
            delete body_piece_to_delete -> get_points_as_text();
            delete body_piece_to_delete;
        }

        //If the body piece was not found (meaning the value doesn't exist), alert the user
        //This also works when there is simply nothing to delete (the list is empty)
        else{
            this -> DialogSlot("", "That value does not exist within this list! Nothing has been removed.", false);
        }

    }
}

/*
This slot responds to the traverse button being pressed
It starts a timer within the Worm class that, when fired, demonstrates traversing through the linked list.
The worm class handles stopping the timer

@param: None
@return: The timer in the worm class begins
*/
void LinkedListWormyWindow::TraverseSlot(){
    this -> HideButtons();

    this -> game_worm_ -> SwitchTimerConnections(true);
    this -> game_worm_ -> StartTimer(true);
}

/*
This slot responds to the play button being pressed
It hides the buttons, plays music, adds a tail to the worm, and starts the worm's timer
It is the timer's timeout events that cause movement for the worm to occur

@param: None
@return: The game enters its active, playing state
*/
void LinkedListWormyWindow::PlaySlot(){
    this -> HideButtons();
    this -> PlacePellet(true); //true denote that the pellet needs to be created within the PlacePellet function
    this -> background_player_ -> play();
    this -> is_playing_ = true;

    //Create the tail, but no reason to add its text since the text is only going to be hidden right after anyways
    WormBodyPiece * tail_to_add = new WormBodyPiece(2,0);
    this -> game_worm_ -> AddBodyPiece(tail_to_add);
    this -> game_scene_ -> addItem(tail_to_add);

    game_worm_ -> HidePointsAsText();

    this -> game_worm_ -> SwitchTimerConnections(false);
    this -> game_worm_ -> StartTimer(false);
}

/*
Respond to keypress events on the WASD keys to change the direction of the game_worm_head_
This change will be stored in a vector so that all future body piece also know to change direction at that point

@param: A key press event (only handles WASD)
@return: The next direction of the game_worm_head_ changes
*/
void LinkedListWormyWindow::keyPressEvent(QKeyEvent *e){

    //If the game is at a menu screen, no key press events should register
    if(!is_playing_){
        return;
    }

    QVector<int> new_direction_change;

    new_direction_change.push_back(game_worm_head_ -> x());
    new_direction_change.push_back(game_worm_head_ -> y());

    if(e -> key() == Qt::Key_W){ //up
       new_direction_change.push_back(0);
   }else if(e -> key() == Qt::Key_D){ //right
       new_direction_change.push_back(1);
   }else if(e -> key() == Qt::Key_S){ //down
       new_direction_change.push_back(2);
   }else if(e -> key() == Qt::Key_A){ //left
       new_direction_change.push_back(3);
   }

    this -> game_worm_ -> add_direction_change(new_direction_change);

}

/*
Place a pellet when the wormy game begins
Also used to iniaitlize the pellet that is stored within the LinkedListWormyWindow

@param: A bool indicating wether or not a pellet needs to be initialized
@return: A new pellet is (potentially) created and set to a random position on the screen
*/
void LinkedListWormyWindow::PlacePellet(bool initialize){

    if(initialize == true){
        this -> current_pellet_ = new Pellet;
        current_pellet_-> setZValue(0);
        this -> game_scene_ -> addItem(current_pellet_);
    }

    int rand_x = rand() % (500);
    int rand_y = rand() % (500);
    current_pellet_ -> setPos(rand_x, rand_y);
}

/*
A slot to check if the head of the worm and the pellet are colliding
If so, move the pellet to a new location and add a sound

This slot responds to the timer firing with the Worm class

@param: None
@return: If the head and the pellet are colliding, move the pellet to a new location and play a sound
*/
void LinkedListWormyWindow::PelletEatenSlot(){
    if(this -> current_pellet_ -> collidesWithItem(this -> game_worm_head_)){
        this -> current_pellet_ -> PlaySound();
        this -> PlacePellet(false); //false denotes that a new pellet does not need to be initialized
    }
}

/*
Upon receiving a signal that the game is over, stop the music and display a game over dialog

@param: None
@return: Music stops and a dialog is displayed
*/
void LinkedListWormyWindow::GameOverSlot(){
    this -> background_player_ -> stop();
    emit DialogSlot("", "GAME OVER! Thanks so much for playing!", false);
}
