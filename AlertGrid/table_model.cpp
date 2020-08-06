#define CHECK_BOX_COLUMN 5
#include<table_model.h>

AreasTableModel::AreasTableModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

AreasTableModel::~AreasTableModel()
{

}

Qt::ItemFlags AreasTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QStandardItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() == CHECK_BOX_COLUMN)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}
