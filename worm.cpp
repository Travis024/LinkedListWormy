#include "worm.h"

/*
When initializing a worm, it only begins with a head/tail in the middle-left of the screen
Head and tail are the same at this point because there is only one item in the linked list

The worm's timer must also be created and its traverse_body_piece field set so that the traverse button can be clicked and used

Finally, create the worm's media player for playing sounds

@param: None
@return: The worm is given a head/tail and the position is set to the middle-left of the screen
*/
Worm::Worm()
{
    this -> head_ = new WormBodyPiece(0);
    this -> head_ -> setPos(5, 225);
    this -> tail_ = this -> head_;
    this -> traverse_body_piece_ = this -> head_; //By setting the traverse body piece as the head, the first text to always be updated is the first "real" body piece

    this -> current_size_ = 1; //count the head in the current size

    this -> worm_timer_ = new QTimer;

    this -> worm_media_player_ = new QMediaPlayer;

}

/*
Shift the coordinates of body pieces in the worm when a new body piece is added, deleted, or the game is being played
Also shift the text above the body pieces that are not the head or tail

@param: An int denoting the direction to move the body piece (start with 0 = up and going clockwise)
@return: The worm's body pieces and text are shifted appropriately
*/
void Worm::ShiftCoordinates(WormBodyPiece * to_shift, int direction_starting_with_up, bool is_playing){

        //Used for moving up
        if(direction_starting_with_up == 0){
            to_shift -> setPos(to_shift ->x(), to_shift -> y() - 50);
        }

        //Used for adding a body piece and moving to the right
        else if(direction_starting_with_up == 1){
            to_shift -> setPos(to_shift ->x() + 50, to_shift -> y());
        }

        //Used for moving down
        else if(direction_starting_with_up == 2){
            to_shift -> setPos(to_shift ->x(), to_shift -> y() + 50);
        }

        //Used for deleting a body piece and moving to the left
        else if(direction_starting_with_up == 3){
            to_shift -> setPos(to_shift ->x() - 50, to_shift -> y());
        }

        //Move the corresponding text to the new coordinates of the body piece
        //ONLY when adding or deleting, in which case is_playing will be false
        //When playing, these graphics items are hidden
        if(!is_playing){
            to_shift -> set_points_as_text_coordinates_(to_shift -> x() + 10, to_shift -> y() - 25);
        }

}

/*
Add a new body piece to the end of the worm.
This involves shifting the other body pieces forward, setting the position of the new body piece, and updating the tail_ field.
The new body piece that is being added becomes the tail

@param: A pointer to the WormBodyPiece to add
@return: The new body piece is added as the tail and all other body pieces shift forward
*/
void Worm::AddBodyPiece(WormBodyPiece * body_piece_to_add){

    this -> worm_media_player_ -> setMedia(QUrl("qrc:/sounds/sounds/addSound.wav"));

    //Shift every body piece to the right using the ShiftCoordinates functions
    //Parameter is false to show that the points_as_text items should move as well
    WormBodyPiece * current_body_piece = this -> head_;
    while(current_body_piece != nullptr){
        this -> ShiftCoordinates(current_body_piece, 1, false);
        current_body_piece = current_body_piece -> get_next_body_piece_();
    }

    body_piece_to_add -> setPos(5,225);
    body_piece_to_add -> set_points_as_text_coordinates_(body_piece_to_add -> x() + 10, body_piece_to_add -> y() - 25); //remember, body pieces have a corresponding piece of text that hovers above
    this -> tail_ -> set_next_body_piece_(body_piece_to_add);
    this -> tail_ = body_piece_to_add;

    this -> current_size_ += 1;

    //Play the sound at the end so it matches better with the body piece being added
    this -> PlaySound();

}


/*
This function handles searching for and deleting a body piece after the delete button is pressed
If the value is found, the WormBodyPiece containing it is returned, removed, and deleted
If the value is not found, a nullptr is returned

@param: The value to search for and delete
@return: A WormBodyPiece (if the value was found) or a nullptr (if the value was NOT found)
*/
WormBodyPiece * Worm::DeleteBodyPiece(int value_to_delete){

    this -> worm_media_player_ -> setMedia(QUrl("qrc:/sounds/sounds/deleteSound.wav"));

    //If there's nothing in the list, don't even bother running more code
    if(this -> current_size_ == 0){
        return nullptr;
    }

    WormBodyPiece * current_body_piece = this -> head_;
    WormBodyPiece * body_piece_to_delete;

    //Always check the value of the NEXT body piece so that we can store the current body piece we're at
    //This helps with adjusting pointers when the piece is removed
    while(current_body_piece -> get_next_body_piece_() != nullptr){

        if(current_body_piece -> get_next_body_piece_() -> get_points_() == value_to_delete){

            body_piece_to_delete = current_body_piece -> get_next_body_piece_();

            //Set the next body piece to nullptr so that the ShiftCoordinates function only shifts the coordinates up to this point
            current_body_piece -> set_next_body_piece_(nullptr);

            //Shift body pieces to the left using the ShiftCoordinates functions
            //This only shifts body pieces up to the body piece that was deleted
            //Parameter is false to denote that the points_as_text_ items should move as well
            WormBodyPiece * start_shifting_body_piece = this -> head_;
            while(start_shifting_body_piece != nullptr){
                this -> ShiftCoordinates(start_shifting_body_piece, 3, false);
                start_shifting_body_piece = start_shifting_body_piece -> get_next_body_piece_();
            }

            //Once coordinates are shifted, adhjust the pointers using the body piece that was stored
            current_body_piece -> set_next_body_piece_(body_piece_to_delete -> get_next_body_piece_());

            //Update the current size of the list and return
            this -> current_size_ -= 1;

            //Play the sound at the end so it matches beter with the piece leaving the scene
            this -> PlaySound();

            return body_piece_to_delete;
        }

        current_body_piece = current_body_piece -> get_next_body_piece_();
    }


    //This is only reached if the body piece wasn't found
    return nullptr;

}

/*
A helper function to set the timer interval and start the timer
Called either when the traverse button is pressed or when the play button is pressed (each has its own unique firing time)

@param: None
@return: The timer starts firing at an interval depending on which button was pressed
*/
void Worm::StartTimer(bool traverse_true_play_false){


    if(traverse_true_play_false == true){
        this -> worm_timer_ -> setInterval(1000);
        this -> worm_timer_ -> start();
    }else{
        this -> worm_timer_ -> setInterval(500);
        this -> worm_timer_ -> start();
    }
}

/*
A helper function to stop the timer (which resets its position to 0)

@param: None
@return: The timer stops
*/
void Worm::StopTimer(){
    this -> worm_timer_ -> stop();
}

/*
Because the traverse and gamemovement functions utilize the same timer, this function handles switching the connections so that they both don't fire at the same timeout event

@param: A bool of traverse (true) or play (false)
@return: The timer is connected to the appropriate function and disconnected from the other
*/
void Worm::SwitchTimerConnections(bool traverse_true_play_false){
    if(traverse_true_play_false == true){
        connect(this -> worm_timer_, &QTimer::timeout, this, &Worm::Traverse);
        disconnect(this -> worm_timer_, &QTimer::timeout, this, &Worm::GameMovement);
    }else{
        connect(this -> worm_timer_, &QTimer::timeout, this, &Worm::GameMovement);
        disconnect(this -> worm_timer_, &QTimer::timeout, this, &Worm::Traverse);
    }
}

/*
This function responds to a the timer timing out; it sets the next body piece's text to larger and highlighted, and resets the current body piece's text
Once the next body piece is a nullptr, the function resets the traverse_body_piece_ field and stops the timer

@param: None
@return: The points_as_text for each body piece update from head to tail, but finish in the same state as before this function was called
*/
void Worm::Traverse(){

    //Two fonts of the same type, one just a little larger than the other
    QFont normalFont = QFont("Born2bSportyV2", 20, 1);
    QFont biggerFont = QFont("Born2bSportyV2", 22, 1);

    //The current body piece resets, while the next body piece updates
    WormBodyPiece * current_body_piece = this -> traverse_body_piece_;
    WormBodyPiece * next_body_piece = current_body_piece -> get_next_body_piece_();

    current_body_piece -> set_points_as_text_color_(QColor(15,56,15));
    current_body_piece -> set_points_as_text_font_(normalFont);

    //Check to see if there is another body piece to update
    if(next_body_piece != nullptr){
        next_body_piece -> set_points_as_text_color_(QColor(48,98,48));
        next_body_piece -> set_points_as_text_font_(biggerFont);

        //Only play a sound when there is a next body piece to update
        this -> worm_media_player_ -> setMedia(QUrl("qrc:/sounds/sounds/traverseSound.wav"));
        this -> PlaySound();

        this -> traverse_body_piece_ = next_body_piece;

    }

    //If this list has reached its end, reset the traverse_body_piece field and stop the timer
    //Emit a signal so that buttons show again
    else{
        this -> traverse_body_piece_ = this -> head_;
        this -> StopTimer();
        emit TimerFinished();
    }


}

/*
A wrapper function to help with playing sound when a button is pressed
Ensures that after a sound has been played it is reset to the start or the sound file

@param: None
@return: The sound that belongs to the button is played
*/
void Worm::PlaySound(){
    if(worm_media_player_ -> state() == QMediaPlayer::PlayingState){
        this -> worm_media_player_ -> setPosition(0);
    }else{
       this -> worm_media_player_ -> play();
    }
}

/*
This function handles the movement of the worm following the play button being pressed
If the body piece is on a location that is stored in the direction_change_vector, then both its direction and its image change accrodingly
Furthermore, if the body piece is the tail, the direction change is erased from the vector so that it will no longer act as a flag

Note: This function is connected to the timer's timeout signal

@param: None
@return: Every time the timer fires, this function is called and the worm moves in the appropriate direction
*/
void Worm::GameMovement(){

    WormBodyPiece * current_body_piece = this -> head_;

    while (current_body_piece != nullptr){

        //Check to see if the current body piece is on a direction that is marked as a change of direction
        for(int i = 0; i < this -> direction_change_vector_.size(); i++){

            //If the x and y coordinates are the same, update the piece's direction and change its image
            if(current_body_piece -> x() == this -> direction_change_vector_[i][0] && current_body_piece -> y() == this -> direction_change_vector_[i][1]){
                current_body_piece -> set_current_direction(this -> direction_change_vector_[i][2]);
                current_body_piece -> set_image_direction(this -> direction_change_vector_[i][2]);

                //If the piece is the tail, remove the direction change so that it no longer causes body pieces to change directions
                if(current_body_piece == this -> tail_){
                    this -> direction_change_vector_.erase(direction_change_vector_.begin() + i);
                }
           }
        }

        //Now that the body piece's direction has been updated, shift the body piece in that direction
        //Pass the bool paramater as true to denote that points_as_text should NOT move since they have been hidden
        this -> ShiftCoordinates(current_body_piece, current_body_piece -> get_current_direction(), true);

        current_body_piece = current_body_piece -> get_next_body_piece_();
    }

    //Check to see if the pellet has been eaten
    emit PelletEatenSignal();

    //Check to see if the head is colliding with another body piece
    this -> CheckBodyPieceCollision();

}

/*
When the play button is pressed, hide all of the text above each body piece since it clutters the screen and adds unnecessary objects to deal with in gameplay

@param: None
@return: The text is hidden
*/
void Worm::HidePointsAsText(){

    WormBodyPiece * current_body_piece = head_ -> get_next_body_piece_();
    QGraphicsTextItem * text_to_hide_;

    while(current_body_piece != nullptr){
        text_to_hide_  = current_body_piece -> get_points_as_text();
        text_to_hide_ ->hide();

        current_body_piece = current_body_piece -> get_next_body_piece_();
    }

}

/*
Check to see if the head has collided with another body piece
If so, then the game is over; hide the worm and send a signal to the LinkedListWormyWindow

@param: None
@return: The timer stops, the worm is hidden, and a signal is sent to the LinkedListWormyWindow
*/
void Worm::CheckBodyPieceCollision(){

    WormBodyPiece * current_body_piece = this -> head_ -> get_next_body_piece_();

    while(current_body_piece != nullptr){

        if(current_body_piece -> collidesWithItem(this -> head_)){

            this -> worm_media_player_ -> setMedia(QUrl("qrc:/sounds/sounds/gameOver.wav"));
            this -> worm_media_player_ -> play();

            this -> StopTimer();
            this -> HideWorm();
            emit GameOverSignal();
            return;
        }

        current_body_piece = current_body_piece -> get_next_body_piece_();
    }

}

/*
Hides every body piece in the worm when the game is over

@param: None
@return: Every body piece is hidden
*/
void Worm::HideWorm(){
    WormBodyPiece * current_body_piece = this -> head_;

    while(current_body_piece != nullptr){
        current_body_piece -> hide();
        current_body_piece = current_body_piece -> get_next_body_piece_();
    }
}
