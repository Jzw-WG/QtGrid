#ifndef BUTTON_DELEGATE_H
#define BUTTON_DELEGATE_H
#include<QItemDelegate>

class ButtonDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate();
    explicit ButtonDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  collButtons;
    collButtons m_btns;
};

#endif // BUTTON_DELEGATE_H
