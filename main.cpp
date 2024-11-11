#include "gui.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    char er_fn[20];
    strcpy(er_fn, "events.txt");
    EventRepo er = EventRepo(er_fn);
    er.initialise_repo(er);

    Service s;
    Gui w(s);
    w.initGui();
    w.show();
    return a.exec();
}