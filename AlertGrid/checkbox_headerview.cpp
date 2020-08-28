#define CHECK_BOX_COLUMN 5
#include "checkbox_headerview.h"
#include<QCheckBox>
#include<QMouseEvent>
#include<QPainter>

CheckboxHeaderView::CheckboxHeaderView(Qt::Orientation orientation, QWidget *parent): QHeaderView(orientation, parent),
    m_bPressed(false),
    m_bChecked(false),
    m_bTristate(false),
    m_bNoChange(false),
    m_bMoving(false)
{
     setStretchLastSection(true);
    setHighlightSections(false);
    setMouseTracking(true);

    // 响应鼠标
    setSectionsClickable(true);
}
// 槽函数，用于更新复选框状态
void CheckboxHeaderView::onStateChanged(int state)
{
//    if (state == Qt::PartiallyChecked) {
//        m_bTristate = true;
//        m_bNoChange = true;
//    } else {
//        m_bNoChange = false;
//    }

//    m_bChecked = (state != Qt::Unchecked);
//    update();

}

// 绘制复选框
void CheckboxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (logicalIndex == CHECK_BOX_COLUMN)
    {
        QStyleOptionButton option;
        option.initFrom(this);

//        if (m_bChecked)
//            option.state |= QStyle::State_Sunken;

//        if (m_bTristate && m_bNoChange)
//            option.state |= QStyle::State_NoChange;
//        else
            option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off;
//        if (testAttribute(Qt::WA_Hover) && underMouse()) {
//            if (m_bMoving)
//                option.state |= QStyle::State_MouseOver;
//            else
//                option.state &= ~QStyle::State_MouseOver;
//        }


        QCheckBox checkBox;
        int leftPos = this->sectionViewportPosition(0);
        checkBox.setGeometry(leftPos,0,20,this->height());
        option.iconSize = QSize(20, 20);
        option.rect = QRect(rect.left() - 40,rect.top(),rect.width(),rect.height());
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &checkBox);
//        style()->drawItemPixmap(painter, rect, Qt::AlignCenter, QPixmap(":/images/checkBoxChecked"));
//        style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
    }
}

// 鼠标按下表头
void CheckboxHeaderView::mousePressEvent(QMouseEvent *event)
{
    int nColumn = logicalIndexAt(event->pos());
    if ((event->buttons() & Qt::LeftButton) && (nColumn == CHECK_BOX_COLUMN))
    {
        m_bPressed = true;
    }
    else
    {
        QHeaderView::mousePressEvent(event);
    }
}

// 鼠标从表头释放，发送信号，更新model数据
void CheckboxHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_bPressed)
    {
//        if (m_bTristate && m_bNoChange)
//        {
//            m_bChecked = true;
//            m_bNoChange = false;
//        }
//        else
        int nColumn = logicalIndexAt(event->pos());

        if (nColumn == CHECK_BOX_COLUMN)
        {
            m_bChecked = !m_bChecked;
        }

        update();

        bool state = m_bChecked;

        emit stateChanged(state);
    }
    else
    {
        QHeaderView::mouseReleaseEvent(event);
    }

    m_bPressed = false;
}

// 鼠标滑过、离开，更新复选框状态
//bool CheckboxHeaderView::event(QEvent *event)
//{
//    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
//    {
//        QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
//        int nColumn = logicalIndexAt(pEvent->x());
//        if (nColumn == CHECK_BOX_COLUMN)
//        {
//            m_bMoving = (event->type() == QEvent::Enter);

//            update();
//            return true;
//        }
//    }

//    return QHeaderView::event(event);
//}
