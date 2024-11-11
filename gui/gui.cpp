#include "gui.h"
#include <QHBoxLayout>
#include <QLabel>
#include <warning.h>
#include <qmessagebox.h>
#include<qcombobox.h>


void Gui::toggleRowHeight(const QModelIndex& index)
{
	int row = index.row();
	int currentHeight = tableView->rowHeight(row);
	int newHeight = (currentHeight == 50) ? 100 : 50; 

	tableView->setRowHeight(row, newHeight);
}

Gui::Gui(Service service) :service(service)
{

}

Gui::~Gui()
{
	this->hide();
	QLayoutItem* item;
	while ((item = mainLayout->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}
	delete mainLayout;
}

void Gui::initGui()
{
	er.initialise_repo(er);
	mainLayout = new QHBoxLayout{ this };
	QPushButton* admin = new QPushButton{ "Admin mode" };
	QPushButton* user = new QPushButton{ "User mode" };
	mainLayout->addWidget(admin);
	mainLayout->addWidget(user);
	QObject::connect(admin, &QPushButton::clicked, this, &Gui::admin_gui);
	QObject::connect(user, &QPushButton::clicked, this, &Gui::user_gui);

}

void Gui::populate_list()
{
	std::ifstream file(erf);
	std::string line;
	list->clear();
	while (std::getline(file, line)) {
		QString qline = QString::fromStdString(line);
		QStringList eventparts = qline.split(';');
		if (eventparts.size() == 6)
		{
			QString title = eventparts[0];
			QString descr = eventparts[1];
			QString date = eventparts[2];
			QString time = eventparts[3];
			QString ppl = eventparts[4];
			QString link = eventparts[5];
			QString event = QString("Title: %1\nDescription: %2\nDate: %3\nTime: %4\nNumber of people: %5\nLink: %6")
				.arg(title).arg(descr).arg(date).arg(time).arg(ppl).arg(link);
			QListWidgetItem* item = new QListWidgetItem{ event };
			QFont font = { "Calibri",10,15 };
			item->setFont(font);
			list->addItem(item);
		}
	}
	file.close();
}

void Gui::open_link_list(QListWidgetItem* item) {
	QString itemText = item->text();
	QStringList lines = itemText.split('\n');

	QString link;
	for (const QString& line : lines) {
		if (line.startsWith("Link: ")) {
			link = line.mid(6);
			break;
		}
	}

	QDesktopServices::openUrl(QUrl(link));

}

void Gui::admin_gui()
{
	this->hide();
	QLayoutItem* item;
	while ((item = mainLayout->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}
	QVBoxLayout* secLayout = new QVBoxLayout{ };
	QHBoxLayout* editLayout = new QHBoxLayout{ };
	QVBoxLayout* listLayout = new QVBoxLayout{ };


	list = new QListWidget;

	QLabel* name = new QLabel{ "Title" };
	nameline = new QLineEdit;
	secLayout->addWidget(name);
	secLayout->addWidget(nameline);

	QLabel* descr = new QLabel{ "Description" };
	descrline = new QLineEdit;
	secLayout->addWidget(descr);
	secLayout->addWidget(descrline);

	QLabel* date = new QLabel{ "Date" };
	dateline = new QLineEdit;
	secLayout->addWidget(date);
	secLayout->addWidget(dateline);

	QLabel* time = new QLabel{ "Time" };
	timeline = new QLineEdit;
	secLayout->addWidget(time);
	secLayout->addWidget(timeline);

	QLabel* ppl = new QLabel{ "Number of people" };
	pplline = new QLineEdit;
	secLayout->addWidget(ppl);
	secLayout->addWidget(pplline);

	QLabel* link = new QLabel{ "Link" };
	linkline = new QLineEdit;
	secLayout->addWidget(link);
	secLayout->addWidget(linkline);

	QPushButton* add = new QPushButton{ "Add" };
	editLayout->addWidget(add);
	QPushButton* del = new QPushButton{ "Delete" };
	editLayout->addWidget(del);
	QPushButton* update = new QPushButton{ "Update" };
	editLayout->addWidget(update);
	secLayout->addLayout(editLayout);

	populate_list();

	listLayout->addWidget(list);

	mainLayout->addLayout(secLayout);
	mainLayout->addLayout(listLayout);

	QObject::connect(add, &QPushButton::clicked, this, &Gui::add_handler);
	QObject::connect(del, &QPushButton::clicked, this, &Gui::del_handler);
	QObject::connect(update, &QPushButton::clicked, this, &Gui::update_handler);
	QObject::connect(list, &QListWidget::itemClicked, this, &Gui::open_link_list);

	QString borderStyle = "QListWidget::item { border: 1px solid black; padding: 5px; }";
	list->setStyleSheet(borderStyle);

	QPushButton* undo_button = new QPushButton{ "Undo" };
	QShortcut* undo_shortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QPushButton* redo_button = new QPushButton{ "Redo" };
	QShortcut* redo_shortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	secLayout->addWidget(undo_button);
	secLayout->addWidget(redo_button);

	QObject::connect(undo_shortcut, &QShortcut::activated, this, &Gui::undo_handler);
	QObject::connect(undo_button, &QPushButton::clicked, this, &Gui::undo_handler);

	QObject::connect(redo_shortcut, &QShortcut::activated, this, &Gui::redo_handler);
	QObject::connect(redo_button, &QPushButton::clicked, this, &Gui::redo_handler);


	this->show();
}

void Gui::add_handler() {
	QString title = nameline->text();
	QString description = descrline->text();
	QString date = dateline->text();
	QString time = timeline->text();
	QString ppl = pplline->text();
	QString link = linkline->text();

	if (title.isEmpty() || description.isEmpty() || date.isEmpty() || time.isEmpty() || ppl.isEmpty() || link.isEmpty()) {
		QMessageBox::warning(this, "Input Error", "All fields must be filled out!!");
		return;
	}

	bool ok;
	int numberOfPeople = ppl.toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Input Error", "Number of people must be a valid integer!!");
		return;
	}

	QByteArray titleBytes = title.toLocal8Bit();
	char* titleCStr = titleBytes.data();
	QByteArray descriptionBytes = description.toLocal8Bit();
	char* descriptionCStr = descriptionBytes.data();
	QByteArray dateBytes = date.toLocal8Bit();
	char* dateCStr = dateBytes.data();
	QByteArray timeBytes = time.toLocal8Bit();
	char* timeCStr = timeBytes.data();
	QByteArray linkBytes = link.toLocal8Bit();
	char* linkCStr = linkBytes.data();
	Event newEvent(titleCStr, descriptionCStr, dateCStr, timeCStr, numberOfPeople, linkCStr);

	EventValidator validator;
	try {
		/*validator.validate_event(&newEvent);

		er.add_event(newEvent);*/
		service.service_add(er, newEvent);
		QMessageBox::information(nullptr, "Success", "Event added successfully.");
	}
	catch (const EventException& e) {
		QMessageBox::warning(nullptr, "Error", "Input invalid!!");
		return;
	}
	catch (const RepoException& e) {
		QMessageBox::warning(nullptr, "Error", "Duplicate event!!");
		return;
	}
	populate_list();
}

void Gui::del_handler()
{
	QString title = nameline->text();
	if (title.isEmpty())
	{
		QMessageBox::warning(this, "Input Error", "Title field empty.");
		return;
	}
	QByteArray titleBytes = title.toLocal8Bit();
	char* titleCStr = titleBytes.data();
	bool ok = service.service_remove(er, titleCStr);
	if (!ok)
	{
		QMessageBox::warning(this, "Error", "Event does not exist!!");
		return;
	}
	else
	{
		QMessageBox::information(this, "Success", "Event removed successfully.");
		populate_list();
		return;
	}
}

void Gui::update_handler() {
	QString title = nameline->text();
	if (title.isEmpty()) {
		QMessageBox::warning(this, "Error", "Title cannot be empty.");
		return;
	}

	QByteArray titleBytes = title.toLocal8Bit();
	char* titleCStr = titleBytes.data();

	int index = service.search_title(er, titleCStr);

	if (index == -1) {
		QMessageBox::warning(this, "Error", "Event not found.");
		return;
	}

	Event event = er.getEvent(index);

	QString newDescr = descrline->text();
	QString newDate = dateline->text();
	QString newTime = timeline->text();
	QString newPeople = pplline->text();
	QString newLink = linkline->text();

	if (!newDescr.isEmpty())
	{
		QByteArray newDescrBytes = newDescr.toLocal8Bit();
		char* newDescrCStr = newDescrBytes.data();
		service.service_update_descr(er, titleCStr, newDescrCStr);
	}
	if (!newDate.isEmpty())
	{
		QByteArray newDateBytes = newDate.toLocal8Bit();
		char* newDateCStr = newDateBytes.data();
		service.service_update_date(er, titleCStr, newDateCStr);
	}
	if (!newTime.isEmpty())
	{
		QByteArray newTimeBytes = newTime.toLocal8Bit();
		char* newTimeCStr = newTimeBytes.data();
		service.service_update_time(er, titleCStr, newTimeCStr);
	}
	if (!newPeople.isEmpty())
	{
		bool ok;
		int ppl = newPeople.toInt(&ok);
		if (ok)
		{
			service.service_update_people(er, titleCStr, ppl);
		}
		else {
			QMessageBox::warning(this, "Error", "Invalid number of people.");
		}
	}
	if (!newLink.isEmpty())
	{
		QByteArray newLinkBytes = newLink.toLocal8Bit();
		char* newLinkCStr = newLinkBytes.data();
		service.service_update_link(er, titleCStr, newLinkCStr);
	}

	populate_list();
}

void Gui::undo_handler()
{
	if (service.uempty()) 
	{
		QMessageBox::warning(this, "Error", "No more undos!!");
		return;
	}
	else
	{
		service.service_undo(er);
		populate_list();
	}
}

void Gui::redo_handler()
{
	if (service.rempty())
	{
		QMessageBox::warning(this, "Error", "No more redos!!");
		return;
	}
	else
	{
		service.service_redo(er);
		populate_list();
	}
}

void Gui::user_gui()
{
	this->hide();
	QLayoutItem* item;
	while ((item = mainLayout->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}

	QVBoxLayout* secLayout = new QVBoxLayout{ };
	QLabel* firstLabel = new QLabel{ "CSV or HTML?" };
	QPushButton* csv = new QPushButton{ "CSV" };
	QPushButton* html = new QPushButton{ "HTML" };

	secLayout->addWidget(firstLabel);
	secLayout->addWidget(csv);
	secLayout->addWidget(html);

	mainLayout->addLayout(secLayout);

	userlist = new QListWidget{};
	mainLayout->addWidget(userlist);

	QLabel* mon_label = new QLabel{ "For which month would you like to see the events?" };
	secLayout->addWidget(mon_label);
	QComboBox* month = new QComboBox{};
	for (int i = 1; i <= 12; i++) {
		month->addItem(QString::number(i));
	}
	secLayout->addWidget(month);
	QPushButton* mon_button = new QPushButton{ "Show events" };
	secLayout->addWidget(mon_button);

	nameline = new QLineEdit;
	secLayout->addWidget(nameline);

	QPushButton* u_del = new QPushButton{ "Delete event" };
	secLayout->addWidget(u_del);

	QObject::connect(mon_button, &QPushButton::clicked, this, [this, month]() {
		int mon = month->currentText().toInt();
		show_events_by_month(mon);
		});
	QObject::connect(csv, &QPushButton::clicked, this, &Gui::csv_handler);
	QObject::connect(html, &QPushButton::clicked, this, &Gui::html_handler);
	QObject::connect(userlist, &QListWidget::itemClicked, this, &Gui::open_link_list);
	QObject::connect(u_del, &QPushButton::clicked, this, &Gui::del_user);
	
	QString borderStyle = "QListWidget::item { border: 1px solid black; padding: 5px; }";
	userlist->setStyleSheet(borderStyle);

	QPushButton* table = new QPushButton{ "Show table view" };
	QObject::connect(table, &QPushButton::clicked, this, &Gui::open_mon);
	mainLayout->addWidget(table);

	this->show();
}

void Gui::show_events_by_month(int mon)
{
	char month[3];
	_itoa(mon, month, 10);
	auto auxrepo = service.sort_month_repo(er, month);
	int size = auxrepo.getSize();

	bool ok = true;
	while (ok && size != 0) {
		for (auto event : auxrepo) {
			if (service.search_title(csvr, event.getTitle()) == -1) {
				QString eventInfo = QString("Title: %1\nDescription: %2\nDate: %3\nTime: %4\nNumber of people: %5\nLink: %6")
					.arg(event.getTitle())
					.arg(event.getDescription())
					.arg(event.getDate())
					.arg(event.getTime())
					.arg(event.getPeople())
					.arg(event.getLink());

				QDesktopServices::openUrl(QUrl(event.getLink()));

				QMessageBox msgBox;
				msgBox.setText(eventInfo);
				msgBox.addButton("Add to List", QMessageBox::AcceptRole);
				msgBox.addButton("Skip", QMessageBox::RejectRole);
				msgBox.addButton("Exit", QMessageBox::DestructiveRole);

				int response = msgBox.exec();
				switch (response) {
				case QMessageBox::AcceptRole:
					service.service_update_people(er, event.getTitle(), event.getPeople() + 1);
					service.service_update_people(auxrepo, event.getTitle(), event.getPeople() + 1);
					event.setPeople(event.getPeople() + 1);
					service.service_add(csvr, event);
					service.service_add(htmlr, event);
					populate_user();
					size--;
					break;
				case QMessageBox::RejectRole:
					break;
				case QMessageBox::DestructiveRole:
					ok = false;
					break;
				default:
					break;
				}

			}
			else
				size--;
			if (!ok || size == 0) { break; };
		}
	}

	if (auxrepo.getSize() == 0) {
		QMessageBox::information(this, "Error", "No more events found!!");
	}
}

void Gui::populate_user()
{
	userlist->clear();
	for (auto event : csvr) {
		string endl = "\n";
		string name = event.getTitle();
		string descr = event.getDescription();
		string date = event.getDate();
		string time = event.getTime();
		string ppl = to_string(event.getPeople());
		string link = event.getLink();
		string e_info = "Title: " + name + endl + "Description: " + descr + endl + "Date: " + date + endl + "Time: " + time + endl + "Number of people: " + ppl + endl + "Link: " + link + endl;
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(e_info) };
		userlist->addItem(item);
	}
}

void Gui::del_user()
{
	QString title = nameline->text();
	if (title.isEmpty())
	{
		QMessageBox::warning(this, "Input Error", "Title field empty.");
		return;
	}
	QByteArray titleBytes = title.toLocal8Bit();
	char* titleCStr = titleBytes.data();
	bool ok = service.service_remove(csvr, titleCStr);
	if (!ok)
	{
		QMessageBox::warning(this, "Error", "Event does not exist!!");
		return;
	}
	else
	{
		QMessageBox::information(this, "Success", "Event removed successfully.");
		int pos = service.search_title(er, titleCStr);
		Event event = er.getEvent(pos);
		int new_people = event.getPeople() - 1;
		service.service_update_people(er, titleCStr, new_people);
		populate_user();
		return;
	}
}

void Gui::open_mon()
{
	tableView = new QTableView;
	model = new Modelview(csvr);
	tableView->setModel(model);

	int coldesc = 1;  
	int maxwidth = 300; 
	tableView->setColumnWidth(coldesc, maxwidth);
	


	//tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	/*int fixedHeight = 50;
	for (int row = 0; row < csvr.getSize(); ++row)
	{
		tableView->setRowHeight(row, fixedHeight);
	}*/

	//connect(tableView, &QTableView::clicked, this, &Gui::toggleRowHeight);

	this->tableView->resize(1200, 800);
	this->tableView->resizeRowsToContents();
	//this->tableView->resizeColumnsToContents();
	tableView->horizontalHeader()->setStretchLastSection(true);
	tableView->verticalHeader()->hide();
	this->tableView->show();
}

void Gui::csv_handler()
{
	if (csvr.getSize() == 0) {
		QMessageBox::warning(this, "Error", "No events!!");
		return;
	}
	else {
		csvr.open_link();
	}
}

void Gui::html_handler()
{
	if (htmlr.getSize() == 0) {
		QMessageBox::warning(this, "Error", "No events!!");
		return;
	}
	else {
		std::string command = "start " + std::string(hf);
		system(command.c_str());
	}
}


