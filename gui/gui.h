#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "service/service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include "user/user.h"
#include <QHBoxLayout>
#include<QLineEdit>
#include<QObject>
#include<qobject.h>
#include<qdesktopservices.h>
#include <QShortcut>
#include "modelview/modelview.h"
#include <qtableview.h>
#include <QHeaderView>
#include <QSizePolicy>


class Gui : public QWidget
{
protected:
    Service service;
    QListWidget* list;
    QListWidget* userlist;
    char erf[20] = "events.txt";
    char cf[20] = "user.csv";
    char hf[20] = "user.html";
    EventRepo er = EventRepo(erf);
    CSVRepo csvr = CSVRepo(cf);
    HTMLRepo htmlr = HTMLRepo(hf);
    QHBoxLayout* mainLayout;
    QLineEdit* nameline;
    QLineEdit* descrline;
    QLineEdit* dateline;
    QLineEdit* timeline;
    QLineEdit* pplline;
    QLineEdit* linkline;
    Modelview* model;
    QTableView* tableView;
    QWidget* tableViewWindow;

private slots:
    void open_link_list(QListWidgetItem* item);
    void toggleRowHeight(const QModelIndex& index);
public:
    Gui(Service service);
    ~Gui();
    void populate_list();
    void initGui();
    void admin_gui();
    void add_handler();
    void del_handler();
    void update_handler();
    void undo_handler();
    void redo_handler();
    void user_gui();
    void populate_user();
    void show_events_by_month(int mon);
    void csv_handler();
    void html_handler();
    void del_user();
    void open_mon();
};
