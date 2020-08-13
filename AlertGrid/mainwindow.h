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

    void setTargetValue(QString name, int index, int value);
    QVariant getTargetValue(QString name, int index);
    void gerRadarIndex(int targetIndex);
    void selectAllTargets();
    void checkTableModifiable();
private slots:
    void on_btn_addAlertArea_clicked();

    void on_btn_addIgnoreArea_clicked();

    void on_btn_cancelAlertAreas_clicked();

    void on_btn_cancelIgnoreAreas_clicked();

    void receiveTestData(int data);
    void receiveTestData(Area area);
//    void receiveTestData(Target* targetList);
    void receiveTestData(Target target);
    void receiveTestData(QVector<Target> targetList);

    void slot_clickRightMenu(QPoint pos);               //菜单 点击   获取当前位置
    void slot_menuChoiceAction(QAction *act);           //得知菜单当前的位置

private:
    Ui::MainWindow *ui;   
    QMenu *rightClickMenu;
    QAction *deleteAction;
    TableModel *alertAreasModel;
    TableModel *ignoreAreasModel;
    TableModel *infraredTargetModel;
    TableModel *radarTargetModel;
    QVector<Target> lineList;
    bool static isDirectionValid(double startDirection, double endDirection);
    bool static isRadiusValid(double startRadius, double endRadius);
    void initialDelegate(QTableView *tableView);
    void initialSize(QStandardItemModel *model, QTableView *tableView);
    void initialHeaders(QStandardItemModel *model, QTableView *tableView);
    void initialPopMenu();
    void initialEditorValidators();
};
#endif // MAINWINDOW_H
