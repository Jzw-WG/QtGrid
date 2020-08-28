#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QTableView>
#include<table_model.h>
#include<data_test.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DataTest *d;
    int currentRow_Alert;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialTables();
    void addTarget_Test();
    void updateData_Test();

    void clearAllAreasInput();
    void removeAllAlertAreas();
    void removeAllIgnoreAreas();
    void removeAlertAreaAt(int index);
    void removeIgnoreAreaAt(int index);
    bool isDirectionEmpty();
    void addAlertArea();
    void addIgnoreArea();
    void adjustAreaHeaderNum();

    void onInit();
    void initialLineList();

    void setTargetValue(QString name, int index, int value);
    QVariant getTargetValue(QString name, int index);
    void getRadarIndex(int targetIndex);
    void checkTableModifiable(bool state);

    void showATarget(int row);
private slots:
    void on_btn_addAlertArea_clicked();

    void on_btn_addIgnoreArea_clicked();

    void on_btn_cancelAlertAreas_clicked();

    void on_btn_cancelIgnoreAreas_clicked();

    void receiveTestData(int data);
    void receiveTestData(Area area);
//    void receiveTestData(Target* targetList);
    void receiveTestData(Target target);
    void receiveTestData(QVector<Target> infraredList, QVector<Target> radarList);

    void receive_deleteClicked(QModelIndex index);

    void receiveCatagroy(int col, int row, QString text);
    void selectAllTargets(bool state);
    void check_changed(QStandardItem *item);
    void slot_clickRightMenu(QPoint pos);               //菜单 点击   获取当前位置
    void slot_menuChoiceAction(QAction *act);           //得知菜单当前的位置

private:
    Ui::MainWindow *ui;   
    QMenu *rightClickMenu;
    QAction *deleteAction;
    QStandardItemModel *alertAreasModel;
    QStandardItemModel *ignoreAreasModel;
    TableModel *infraredTargetModel;
    QStandardItemModel *radarTargetModel;
    QVector<Target> lineList;
    QVector<Target> radarIndexList;
    QVector<Target> radarTargetList;
    QVector<Target> radarResList;
    bool upLoadFlag = false;// 上报模式：true为手动 false为自动
    bool isNeedBlank = true;
    bool static isDirectionValid(double startDirection, double endDirection);
    bool static isRadiusValid(double startRadius, double endRadius);
    void initialDelegate(QTableView *tableView);
    void initialSize(QStandardItemModel *model, QTableView *tableView);
    void initialHeaders(QStandardItemModel *model, QTableView *tableView);
    void initialPopMenu();
    void initialEditorValidators();

    void dataHandler();
    void radarDataHandler();
    void uploadPolicyHandler();
};
#endif // MAINWINDOW_H
