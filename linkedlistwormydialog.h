#ifndef LINKEDLISTWORMYDIALOG_H
#define LINKEDLISTWORMYDIALOG_H

#include <QDialog>
#include <QFont>
#include <QKeyEvent>

namespace Ui {
class LinkedListWormyDialog;
}

class LinkedListWormyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkedListWormyDialog(QWidget *parent = nullptr, QString dialog_text = "", bool gets_user_input = false); //Dialog created with the given text and a field for user input if true
    ~LinkedListWormyDialog();

    void keyPressEvent(QKeyEvent * e); //Used for exiting the dialog on the enter/return key being pressed

    void CustomCursor(); //Sets a custom cursor for the dialog; this is the same cursor as the LinkedListWormyWindow

signals:

    void PassNodeValueSignal(int node_value); //When a user enters a value to be added or deleted, this is passed to the main window

private:
    Ui::LinkedListWormyDialog *ui;
};

#endif // LINKEDLISTWORMYDIALOG_H
