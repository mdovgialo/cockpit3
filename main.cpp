
#include <QApplication>

#include "cockpit.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cockpit *window = new Cockpit;

    //window->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");

    //InstrumentPanel* panel = new InstrumentPanel(QUrl("http://localhost:8111") , 10);


    window->show();

    return a.exec();
}
