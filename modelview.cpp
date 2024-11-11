#include "modelview.h"

Modelview::Modelview(EventRepo& repo, QObject* parent): repo(repo)
{
	this->count = repo.getSize();
}

Modelview::~Modelview()
{

}

int Modelview::rowCount(const QModelIndex& parent) const
{
	return count;
}

int Modelview::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant Modelview::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        std::vector<Event> events = repo.getEvents(); 
        Event e = events[row];
        switch (column)
        {
        case 0:
            return QString::fromStdString(e.getTitle());

        case 1:
            return QString::fromStdString(e.getDescription());

        case 2:
            return QString::fromStdString(e.getDate());

        case 3:
            return QString::fromStdString(e.getTime());

        case 4:
            return QString::fromStdString(std::to_string(e.getPeople()));

        case 5:
            return QString::fromStdString(e.getLink());

        default:
            break;

        }
    }

    /*if (role == Qt::SizeHintRole)
    {
        return QSize(-1, 50); 
    }*/

    if (role == Qt::FontRole) {

        QFont font{ "Times", 15, 10, true };
        font.setItalic(false);
        return font;
    }
	return QVariant();
}

QVariant Modelview::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString{ "Event name" };
            case 1:
                return QString{ "Event description" };
            case 2:
                return QString{ "Event date" };
            case 3:
                return QString{ "Event time" };
            case 4:
                return QString{ "Number of people" };
            case 5:
                return QString{ "Event link" };
            default:
                break;
            }
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

	return QVariant();
}

Qt::ItemFlags Modelview::flags(const QModelIndex& index) const
{
	return Qt::ItemFlags();
}

void Modelview::updateInternalData()
{

}
