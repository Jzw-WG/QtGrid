#define TAB_TARGETLIST 0
#define TAB_ALERTAREA 1
#define TAB_IGNOREAREA 2

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStandardItemModel>
#include<table_model.h>
#include<QStandardItem>
#include<QMessageBox>
#include<frc_const.h>
#include<QComboBox>
#include<combobox_delegate.h>
#include<readonly_delegate.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialTables();
    addTarget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialTables()
{
    alertAreasModel = new AreasTableModel(this);
    ignoreAreasModel = new AreasTableModel(this);
    infraredTargetModel = new QStandardItemModel(this);
    radarTargetModel = new QStandardItemModel(this);

    ui->table_alertAreas->setModel(alertAreasModel);
    initialHeaders(alertAreasModel, ui->table_alertAreas);
    alertAreasModel->setColumnCount(5);
//    alertAreasModel->setRowCount(10);

    ui->table_ignoreAreas->setModel(ignoreAreasModel);
    initialHeaders(ignoreAreasModel, ui->table_ignoreAreas);
    ignoreAreasModel->setColumnCount(5);
//    ignoreAreasModel->setRowCount(10);

    ui->table_infraredTargets->setModel(infraredTargetModel);
    initialHeaders(infraredTargetModel, ui->table_infraredTargets);
    infraredTargetModel->setColumnCount(6);
    infraredTargetModel->setRowCount(10);
    initialDelegate(ui->table_infraredTargets);

    ui->table_radarTargets->setModel(radarTargetModel);
    initialHeaders(radarTargetModel, ui->table_radarTargets);
    radarTargetModel->setColumnCount(4);
    radarTargetModel->setRowCount(10);
    initialDelegate(ui->table_radarTargets);

    initialEditorValidators();

}

void MainWindow::addTarget()
{
    infraredTargetModel->setItem(1,1,new QStandardItem("zhang"));
    QModelIndex index2 = infraredTargetModel->index(1,4,QModelIndex());
    infraredTargetModel->setData(index2,1,Qt::CheckStateRole);


}

void MainWindow::initialHeaders(QStandardItemModel *model, QTableView *tableView)
{
    QStringList headers;
    if (!QString::compare(tableView->objectName(),"table_infraredTargets"))
    {
        headers.append("红外批号");
        headers.append("方位");
        headers.append("俯仰");
        headers.append("目标类型");
        headers.append("关联批号");
        headers.append("确认");
        tableView->verticalHeader()->hide();
    }
    else if (!QString::compare(tableView->objectName(),"table_radarTargets"))
    {
        headers.append("雷达批号");
        headers.append("方位");
        headers.append("俯仰");
        headers.append("距离");
        tableView->verticalHeader()->hide();
    } else if (!QString::compare(tableView->objectName(),"table_alertAreas") || !QString::compare(tableView->objectName(),"table_ignoreAreas"))
    {
        headers.append("起始方位角");
        headers.append("终止方位角");
        headers.append("起始俯仰角");
        headers.append("终止俯仰角");
        headers.append("操作");
    }
    model->setHorizontalHeaderLabels(headers);
    tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::initialDelegate(QTableView *tableView)
{
    if (!QString::compare(tableView->objectName(),"table_infraredTargets"))
    {
        ReadonlyDelegate* readOnlyDelegate = new ReadonlyDelegate();
        ComboBoxDelegate *targetCategoryDelegate = new ComboBoxDelegate();
        ComboBoxDelegate *platFormTypeDelegate = new ComboBoxDelegate();
        targetCategoryDelegate->comboList.append("不明");
        targetCategoryDelegate->comboList.append("飞机");
        targetCategoryDelegate->comboList.append("导弹");
        targetCategoryDelegate->comboList.append("末敏弹");
        for (int i = 0; i < tableView->model()->rowCount(); ++i)
        {
            switch (i)
            {
            case 3:
                tableView->setItemDelegateForColumn(i, targetCategoryDelegate);
                break;
            case 4:
                tableView->setItemDelegateForColumn(i, platFormTypeDelegate);
                break;
            default:
                tableView->setItemDelegateForColumn(i, readOnlyDelegate);
                break;
            }
        }
    }
    else if (!QString::compare(tableView->objectName(),"table_radarTargets"))
    {
        ReadonlyDelegate* readOnlyDelegate = new ReadonlyDelegate();
        for (int i = 0; i < tableView->model()->rowCount(); ++i)
        {
            tableView->setItemDelegateForColumn(i, readOnlyDelegate);
        }
    } else if (!QString::compare(tableView->objectName(),"table_alertAreas"))
    {

    } else if (!QString::compare(tableView->objectName(),"table_ignoreAreas"))
    {

    }
}

void MainWindow::initialEditorValidators()
{
    QIntValidator *directionValidator = new QIntValidator;
    directionValidator->setRange(FRCConst::MinDirection,FRCConst::MaxDirection);
    QIntValidator *pitchValidator = new QIntValidator;
    pitchValidator->setRange(FRCConst::MinPitch,FRCConst::MaxPitch);
    ui->lineEdit->setValidator(directionValidator);
    ui->lineEdit_2->setValidator(directionValidator);
    ui->lineEdit_5->setValidator(directionValidator);
    ui->lineEdit_6->setValidator(directionValidator);

    ui->lineEdit_3->setValidator(pitchValidator);
    ui->lineEdit_4->setValidator(pitchValidator);
    ui->lineEdit_7->setValidator(pitchValidator);
    ui->lineEdit_8->setValidator(pitchValidator);
}


void MainWindow::clearAllAreasInput()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    // todo 清空alert ignore对象
}

void MainWindow::removeAllAlertAreas()
{
    // service？
}

void MainWindow::removeAllIgnoreAreas()
{
    // service？
}

bool MainWindow::isDirectionEmpty()
{
    if (ui->targetAlertTabWidget->currentIndex() == TAB_ALERTAREA) {
        if (QString::compare(ui->lineEdit->text(),"") || QString::compare(ui->lineEdit_2->text(),"") || QString::compare(ui->lineEdit_3->text(),"") || QString::compare(ui->lineEdit_4->text(),"")) {
            return false;
        }
    }
    else if (ui->targetAlertTabWidget->currentIndex() == TAB_IGNOREAREA)
    {
        if (QString::compare(ui->lineEdit_5->text(),"") || QString::compare(ui->lineEdit_6->text(),"") || QString::compare(ui->lineEdit_7->text(),"") || QString::compare(ui->lineEdit_8->text(),"")) {
            return false;
        }
    }

    return true;
}

void MainWindow::on_btn_addAlertArea_clicked()
{
//    if (isDirectionValid() || isRadiusValid())
//    {
        QMessageBox messageBox(QMessageBox::Information,"输入错误","请修改方位角为" + QString::number(FRCConst::MinDirection) + "~" + QString::number(FRCConst::MaxDirection) +
                               "，俯仰角为" + QString::number(FRCConst::MinPitch) + "~" + QString::number(FRCConst::MaxPitch) + "。");
        int result=messageBox.exec();
        switch (result)
        {
        case QMessageBox::Yes:
            close();
            return;
        case QMessageBox::No:
            return;
        default:
            return;
        }

//    }
    if (!isDirectionEmpty())
    {
//        addAlertArea();
//        clearAllAreasInput();
//        adjustAlertArea();
    }
}

void MainWindow::on_btn_addIgnoreArea_clicked()
{
    //    if (isDirectionValid() || isRadiusValid())
    //    {
            QMessageBox messageBox(QMessageBox::Information,"输入错误","请修改方位角为" + QString::number(FRCConst::MinDirection) + "~" + QString::number(FRCConst::MaxDirection) +
                                   "，俯仰角为" + QString::number(FRCConst::MinPitch) + "~" + QString::number(FRCConst::MaxPitch) + "。");
            int result=messageBox.exec();
            switch (result)
            {
            case QMessageBox::Yes:
                close();
                return;
            case QMessageBox::No:
                return;
            default:
                return;
            }

    //    }
    //    if (!isDirectionEmpty())
    //    {
    //        addIgnoreArea();
    //        clearAllAreasInput();
    //        adjustIgnoreArea();
    //    }
}

void MainWindow::on_btn_cancelAlertAreas_clicked()
{
    clearAllAreasInput();
//    removeAllAlertAreas();
//    adjustAlertArea();
}

void MainWindow::on_btn_cancelIgnoreAreas_clicked()
{
    clearAllAreasInput();
//    removeAllIgnoreAreas();
//    adjustIgnoreArea();
}

