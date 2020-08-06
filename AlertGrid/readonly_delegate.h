#ifndef READONLY_DELEGATE_H
#define READONLY_DELEGATE_H
#include<QItemDelegate>

class ReadonlyDelegate: public QItemDelegate
{
public:
    ReadonlyDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // READONLY_DELEGATE_H
