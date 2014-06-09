
#include <QApplication>

#include "cockpit.h"

#ifdef _WIN32
#include <windows.h>
#endif
//Warthunder Cockpit "Rebirth"
// By M. "iikun" D.
//LGPL

int main(int argc, char *argv[])
{
   #ifdef _WIN32
    cout << "WIndows screensaver disable"<<endl;
    SetThreadExecutionState(ES_CONTINUOUS|ES_DISPLAY_REQUIRED );
   #elif defined __unix__
   //do something for unix like #include <unistd.h>
   #elif defined __APPLE__
   //do something for mac
   #endif



    QApplication a(argc, argv);
    Cockpit *window = new Cockpit;

    //window->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");

    //InstrumentPanel* panel = new InstrumentPanel(QUrl("http://localhost:8111") , 10);


    window->show();

    return a.exec();
}
