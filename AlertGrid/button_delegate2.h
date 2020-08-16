#ifndef BUTTON_DELEGATE2_H
#define BUTTON_DELEGATE2_H
#include<QItemDelegate>

class ButtonDelegate2:public QItemDelegate
{
    Q_OBJECT
public:
    QString buttonText = "X";
    ButtonDelegate2();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
    QMap<QModelIndex, QStyleOptionButton*> m_btns;
signals:
    void clicked(QModelIndex);
};

#endif // BUTTON_DELEGATE2_H
