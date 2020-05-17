#ifndef WORMBODYPIECE_H
#define WORMBODYPIECE_H

#include <QObject>
#include <QMouseEvent>
#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <string>

class WormBodyPiece : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    WormBodyPiece(int t_body_piece_number, int t_points = 0); //Create a body piece that is either the head (0), a body segment (1), or the tail (2) and assign that body piece points

    //inline getter and setters for the class' fields
    int get_piece_identification_(){return this -> piece_identification_; }

    void set_points_(int t_points){this -> points_ = t_points; }
    int get_points_(){return this -> points_; }

    void set_next_body_piece_(WormBodyPiece * t_next_body_piece){this -> next_body_piece_= t_next_body_piece; }
    WormBodyPiece * get_next_body_piece_(){return this -> next_body_piece_; }

    void set_points_as_text_coordinates_(int t_x, int t_y){this -> points_as_text_ -> setPos(t_x, t_y); }
    void set_points_as_text_color_(QColor t_color){this -> points_as_text_ -> setDefaultTextColor(t_color); }
    void set_points_as_text_font_(QFont t_font){this -> points_as_text_ -> setFont(t_font); }
    QGraphicsTextItem * get_points_as_text(){return this -> points_as_text_; }

    int get_current_direction(){return this -> current_direction; }
    int get_next_direction(){return this -> next_direction; }
    void set_current_direction(int t_direction){this -> current_direction = t_direction; }
    void set_next_direction(int t_direction){this -> next_direction = t_direction; }

    void set_image_direction(int t_direction); //Code in .cpp file due to extra length; utilizes the image fields in the class to change the image of the body piece when its direction changes

private:

    int piece_identification_; //used for keeping track of the head (0) and distinguishing from the body (1) or tail (2)

    int points_; //Stores the number of points this piece is worth; essentially the value of a node

    WormBodyPiece * next_body_piece_; //Store a pointer to the next body piece in the worm

    QGraphicsTextItem * points_as_text_ = new QGraphicsTextItem; //Store the points_ variable as text that is visible and moves along with the body piece

    int current_direction; //Stores the current direction that the worm is travelling

    int next_direction; //Stores the direction that the worm should begin travelling on the next turn

    //Store the four different images that the body piece can take on
    QImage * up_image_;
    QImage * right_image_;
    QImage * down_image_;
    QImage * left_image_;


};

#endif // WORMBODYPIECE_H
