#ifndef CHECKBOX_HEADER_H
#define CHECKBOX_HEADER_H
#include<QHeaderView>

class CheckboxHeaderView: public QHeaderView
{
    Q_OBJECT
public:
    CheckboxHeaderView(Qt::Orientation orientation, QWidget *parent);
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    bool event(QEvent *event);
signals:
    void stateChanged(bool state);
private slots:
    void onStateChanged(int state);
private:
    bool m_bPressed;
    bool m_bChecked;
    bool m_bTristate;
    bool m_bNoChange;
    bool m_bMoving;
};

#endif // CHECKBOX_HEADER_H
