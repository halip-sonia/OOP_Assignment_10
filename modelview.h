#pragma once
#include <QAbstractTableModel>
#include <vector>
#include <QString>
#include "service.h"
#include <QFont>
#include "qfontmetrics.h"

class Modelview : public QAbstractTableModel {
private:
    EventRepo& repo;
    int count;

public:

    Modelview(EventRepo& repo, QObject* parent = NULL);
    ~Modelview();

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void updateInternalData();


};