#include "linkedlistwormydialog.h"
#include "ui_linkedlistwormydialog.h"

/*
The dialog window that is used for all dialogs, but can be "customized" depending on the fields passed through
The dialog text is set to the dialog text passed through, and a user input field is included if gets_user_input is true

@param: A parent (the LinkedListWormyWindow), QString dialog, and a bool for whether or not user input is required
@return: A custom dialog window is created and displayed on top of the LinkedListWormyWindow
*/
LinkedListWormyDialog::LinkedListWormyDialog(QWidget *parent, QString dialog_text, bool gets_user_input) :
    QDialog(parent),
    ui(new Ui::LinkedListWormyDialog)
{

    ui->setupUi(this);

    this -> setAttribute(Qt::WA_DeleteOnClose); //ensures the dialog is deleted when the user is done interacting with it

    this -> setWindowFlags(Qt::Window | Qt::FramelessWindowHint); //Hide the gray frame that typically comes with a dialog

    this -> CustomCursor(); //Set the same custom cursor as used in the LinkedListWormyWindo

    //Created two types of the same font, just different size
    QFont largeFont = QFont("Born2bSportyV2", 15, 1);
    QFont smallFont = QFont("Born2bSportyV2", 10, 1);

    //Set the fonts and the textLabel
    this -> ui -> textLabel -> setFont(largeFont);
    this -> ui -> inputBox -> setFont(largeFont);
    this -> ui -> enterLabel -> setFont(smallFont);

    this -> ui -> textLabel -> setText(dialog_text);

    //Hide the user_input button if it is not required
    //Set the value to -1 so that any input returned can be filtered out (the user is only allowed to enter 0 to 99)
    if(!gets_user_input){
        this -> ui -> inputBox -> hide();
        this -> ui -> inputBox -> setRange(-1,99);
        this -> ui -> inputBox -> setValue(-1);
    }


}

LinkedListWormyDialog::~LinkedListWormyDialog()
{
    delete ui;
}

/*
Respond to the enter/return key being pressed so that the dialog closes
Also pass the value that has been entered back to the LinkedListWormyWindow

@param: The event trigger
@return: If the key press is the enter/return key, close the dialog and pass the user input
*/
void LinkedListWormyDialog::keyPressEvent(QKeyEvent *e){

   if(e -> key() == Qt::Key_Enter || e -> key() == Qt::Key_Return){
       emit PassNodeValueSignal(this -> ui -> inputBox -> value());
       this -> close(); //Since the DeleteOnClose flag is set, this ensures the dialog closes properly
   }

}

/*
Create a custom cursor that is the same as the LinkedListWormyWindow

@param: None
@return: The cursor is set to a custom image
*/
void LinkedListWormyDialog::CustomCursor(){
    //create an image object by loading the image path
    QImage * image_object = new QImage();
    image_object->load(":/imgs/imgs/blackCursor.png");

    //create the Pixamp and set its hot point to -1, -1 (the point where clicks are registered)
    QPixmap final_pixmap = QPixmap::fromImage(*image_object);

    QCursor * custom_cursor = new QCursor(final_pixmap, -1, -1);
    this -> setCursor(*custom_cursor);
}
