#include "combobox_delegate.h"
#include<QComboBox>

ComboBoxDelegate::ComboBoxDelegate()
{

}

QWidget * ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    QComboBox *editor = new QComboBox(parent);
    for (int i = 0, size = comboList.count(); i < size; i++)
        editor->addItem(comboList.at(i));
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
    emit send(index.column(), index.row(), text);
}
