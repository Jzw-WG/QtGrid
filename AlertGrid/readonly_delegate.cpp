#include "readonly_delegate.h"

ReadonlyDelegate::ReadonlyDelegate()
{

}

QWidget * ReadonlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return NULL;
}
