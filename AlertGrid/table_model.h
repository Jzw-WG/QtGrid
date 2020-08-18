#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H
#include<QObject>
#include<QAbstractItemModel>
#include<QStandardItemModel>

class TableModel: public QStandardItemModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent);
    ~TableModel();
    bool isSelectable = true;
    bool isEnable = true;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void onStateChanged();
//    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
//    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<QString> recordList;//暂时为QString
    QMap<int, QVariant> checkedMap;
};

#endif // TABLE_MODEL_H
