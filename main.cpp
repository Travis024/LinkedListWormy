#include "linkedlistwormywindow.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(NULL)); //seed for placing pellet in a random position
    QApplication a(argc, argv);
    LinkedListWormyWindow w;
    w.show();
    return a.exec();
}
