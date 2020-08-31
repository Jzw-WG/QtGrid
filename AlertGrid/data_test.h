#ifndef DATA_TEST_H
#define DATA_TEST_H
#include<QThread>
#include<QTimer>
#include<Area.h>
#include<Target.h>

Q_DECLARE_METATYPE(QVector<SCTarget>);

class DataTest: public QThread
{
    Q_OBJECT
signals:
    void sendData(int data);
    void sendData(Area data);
    void sendData(SCTarget data);
    void sendData(SCTarget* data);
    void sendData(QVector<SCTarget> data1, QVector<SCTarget> data2);
public:
    int currentNum;
    SCTarget *target;
    Area *area;

    QVector<SCTarget> infraredTargetList;
    QVector<SCTarget> radarTargetList;
    QVector<SCTarget> linkedTargetList;
    QVector<Area> alertAreaList;
    QVector<Area> ignoreAreaList;
    void sendSignal();
    DataTest();
    ~DataTest();
    void run();
private:
    QTimer *timer;
    void observer();
    SCTarget updateTarget(QVector<SCTarget> list, SCTarget targetInfo);
    SCTarget createTarget(SCTarget targetInfo);
    bool static LessLineNo(const SCTarget &t1, const SCTarget &t2);
private slots:
    void clearTimeoutTargets();
    void changeCheckState(int index, bool checked);
};

#endif // DATA_TEST_H
