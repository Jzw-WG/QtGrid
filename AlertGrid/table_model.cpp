#define CHECK_BOX_COLUMN 5
#define COMBO_BOX_COLUMN1 3
#define COMBO_BOX_COLUMN2 4
#include<table_model.h>

TableModel::TableModel(QObject *parent)
    : QStandardItemModel(parent)
{
//    for (int i = 0; i < 10; ++i)
//    {
//        recordList.append("");
//    }
}

TableModel::~TableModel()
{

}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QStandardItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() == CHECK_BOX_COLUMN)
    {
        if (!isEnable)
            flags &= ~Qt::ItemIsEnabled;
        if (!isSelectable)
            flags &= ~Qt::ItemIsSelectable;
        flags |= Qt::ItemIsUserCheckable;
    }
    else if (index.column() == COMBO_BOX_COLUMN1 || index.column() == COMBO_BOX_COLUMN2)
        flags |= Qt::ItemIsEditable;

    return flags;
}


//bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//        return false;

//    int nColumn = index.column();
//    QString record = recordList.at(index.row());
//    switch (role)
//    {
//    case Qt::DisplayRole:
//    {
//        if (nColumn != CHECK_BOX_COLUMN)
//        {
//            record = value.toString();
//            recordList.replace(index.row(), record);
//            emit dataChanged(index, index);
//            return true;
//        }
//    }
//    case Qt::CheckStateRole:
//    case Qt::UserRole:
//    {
//        if (nColumn == CHECK_BOX_COLUMN)
//        {
////            record.bChecked = value.toBool();

//            recordList.replace(index.row(), record);
//            emit dataChanged(index, index);
//            return true;
//        }
//    }
//    default:
//        return false;
//    }
//    return true;
//}

//QVariant TableModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    int nRow = index.row();
//    int nColumn = index.column();
//    QString record = recordList.at(nRow);

//    switch (role)
//    {
//    case Qt::TextColorRole:
//        return QColor(Qt::white);
//    case Qt::TextAlignmentRole:
//        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
//    case Qt::DisplayRole:
//    {
//        if (nColumn != CHECK_BOX_COLUMN)
//            return record;
//        return "";
//    }
//    case Qt::UserRole:
//    {
//        if (nColumn == CHECK_BOX_COLUMN)
//            return true;// test
////            return record.bChecked;
//    }
//    default:
//        return QVariant();
//    }

//    return QVariant();
//}
