#include "wormbodypiece.h"

/*
The constructor for building up parts of the worm
This includes the body piece and a corresponding piece of text if not the head or tail

@param: A number corresponding to the head (0), body (1), or tail (2) and the points for the body piece
@return: A new body piece is created with the proper image and fields initialized
*/
WormBodyPiece::WormBodyPiece(int t_body_piece_number, int t_points)
{

   //Set up the image fields so that the can set the images using paths
   this -> up_image_ = new QImage();
   this -> right_image_ = new QImage();
   this -> down_image_ = new QImage();
   this -> left_image_ = new QImage();

   //the body piece is a head
   if(t_body_piece_number == 0){
       this -> up_image_ -> load(":/imgs/imgs/wormHeadUp.png");
       this -> right_image_ -> load(":/imgs/imgs/wormHeadRight.png");
       this -> down_image_ -> load(":/imgs/imgs/wormHeadDown.png");
       this -> left_image_ -> load(":/imgs/imgs/wormHeadLeft.png");

       this -> piece_identification_ = 0;
       this -> points_ = t_points;
   }

   //body pieces that are not a head or tail have a corresponding piece of text
   else if(t_body_piece_number == 1){
       this -> up_image_ -> load(":/imgs/imgs/wormBodyUp.png");
       this -> right_image_ -> load(":/imgs/imgs/wormBodyRight.png");
       this -> down_image_ -> load(":/imgs/imgs/wormBodyDown.png");
       this -> left_image_ -> load(":/imgs/imgs/wormBodyLeft.png");

       this -> points_ = t_points;
       this -> piece_identification_ = 1;

       //Set the piece of text as a QGraphicsItem with a leading 0 if the number is less than 10
       if(t_points > 9){
            this -> points_as_text_ -> setPlainText(QString::number(t_points));
        }else{
            this -> points_as_text_ -> setPlainText(QString("0") + QString::number(t_points));
        }

       //Set the font and the color of the text
       QFont pixelFont = QFont("Born2bSportyV2", 20, 1);
        this -> points_as_text_ -> setFont(pixelFont);
        this -> points_as_text_ -> setDefaultTextColor(QColor(15,56,15));
   }

   //the body piece is the tail
   else if(t_body_piece_number == 2){
       this -> up_image_ -> load(":/imgs/imgs/wormTailUp.png");
       this -> right_image_ -> load(":/imgs/imgs/wormTailRight.png");
       this -> down_image_ -> load(":/imgs/imgs/wormTailDown.png");
       this -> left_image_ -> load(":/imgs/imgs/wormTailLeft.png");

        this -> piece_identification_ = 2;
        this -> points_ = t_points;
   }

    //create the Pixamp
    QPixmap final_pixmap = QPixmap::fromImage(*right_image_);
    setPixmap(QPixmap(final_pixmap));

    //Set the z-value for the body pieces so that they are above the background image and pellets
    this -> setZValue(2);

    //All body pieces start by travelling to the right
    this -> current_direction = 1;
    this -> next_direction = 1;

    //Finally, set the next body piece pointer to nullptr
    this -> next_body_piece_ = nullptr;

}

/*
A function for setting the correct image to display on the scene when the body piece direction changes

Utilizes the stored images within the body piece to access the image and change the pixmap accordingly

@param: The direction that the piece is now moving in
@return: The image for the spceific body piece is set to be moving in the correct direction
*/
void WormBodyPiece::set_image_direction(int t_direction){

    QPixmap direction_pixmap;

    if(t_direction == 0){
        direction_pixmap = QPixmap::fromImage(*up_image_);
        setPixmap(QPixmap(direction_pixmap));
    }else if(t_direction == 1){
        direction_pixmap = QPixmap::fromImage(*right_image_);
        setPixmap(QPixmap(direction_pixmap));
    }else if(t_direction == 2){
        direction_pixmap = QPixmap::fromImage(*down_image_);
        setPixmap(QPixmap(direction_pixmap));
    }else{
        direction_pixmap = QPixmap::fromImage(*left_image_);
        setPixmap(QPixmap(direction_pixmap));
    }

}
