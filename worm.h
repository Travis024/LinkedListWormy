#ifndef WORM_H
#define WORM_H

#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include "wormbodypiece.h"

class Worm : public QObject
{
    Q_OBJECT
public:

    Worm(); //Create a worm with just a head and set its position

    WormBodyPiece * get_head_(){return this -> head_; } //Get the head of the worm

    void ShiftCoordinates(WormBodyPiece * to_shift, int direction_starting_with_up, bool is_playing); //Used for shifting a body piece in the worm, either when a piece is added, deleted, or the game is being played

    void AddBodyPiece(WormBodyPiece * body_piece_to_add); //Add a body piece to the linked list; this body piece becomes the tail

    WormBodyPiece * DeleteBodyPiece(int value_to_delete); //Delete a body piece from the worm or alert the user that a body piece with that value does not exist

    void StartTimer(bool traverse_true_play_false); //A helper function to start the timer when the traverse button is clicked OR when the play button is clicked

    void StopTimer(); //A helper function to stop the timer when the traverse button ends

    void Traverse(); //A function that is called every time the timer fires to demonstarte traversing through a linked list

    void PlaySound(); //A wrapper function to help with playing sounds

    void GameMovement(); //When the game is being played, this function handles moving each worm body piece

    void HidePointsAsText(); //Hide each body piece's points_as_text_ graphics item

    void CheckBodyPieceCollision(); //Checks to see if the head has collided with any other body pieces; if so, game over!

    void HideWorm(); //When the game is over, this function hides every body piece

    void SwitchTimerConnections(bool traverse_true_play_false); //Used to switch the timer between being connected for Traversering and for playing the game

    //inline getter functions for the max and current size
    int get_current_size_(){return this -> current_size_; }
    int get_max_size_(){return this -> max_size_; }

    void add_direction_change(QVector<int> t_direction_change){this -> direction_change_vector_.push_back(t_direction_change); } //When a keypress occurs on the LinkedListWormYWindow, this function is used to store the location of the direction change

signals:

    void TimerFinished(); //Shoots a signal to the LinkedListWormyWindow to alert it that the timer has been stopped

    void PelletEatenSignal(); //Shoots a signal to the LinkedListWormyWindow to determine if the pellet is under the head

    void GameOverSignal();//Shoots a signal to the LinkedListWormyWindow that the game is over

private:

    WormBodyPiece * head_; //The beginning of the worm/linked list
    WormBodyPiece * tail_; //The end of the worm/linked list

    int max_size_ = 9; //The max size of the worm, including the head body piece. The tail body piece will still be added after this max size is reached.
    int current_size_; //The current size of the worm, incremented when AddBodyPiece is called and decremented when DeleteBodyPiece is called

    QTimer * worm_timer_; //The timer that fires when the traverse button is pressed

    WormBodyPiece * traverse_body_piece_; //Track the current body piece that is being traversed over so it can be updated when the timer fires

    QVector<QVector<int>> direction_change_vector_; //Store the location of direction changes; each inner vector is {x-coord, y_coord, direction}

    QMediaPlayer * worm_media_player_; //Controls playing sounds for the worm

};

#endif // WORM_H
