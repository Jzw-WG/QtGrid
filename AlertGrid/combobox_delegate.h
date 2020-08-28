#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H
#include<QItemDelegate>
#include<QStringList>

class ComboBoxDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    QStringList comboList;
    ComboBoxDelegate();
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
signals:
    void send(int col, int row, QString text) const;
};

#endif // COMBOBOX_DELEGATE_H
