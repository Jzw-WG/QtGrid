#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H
#include<QObject>
#include<QAbstractItemModel>
#include<QStandardItemModel>
class AreasTableModel: public QStandardItemModel
{
    Q_OBJECT
public:
    AreasTableModel(QObject *parent);
    ~AreasTableModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // TABLE_MODEL_H
