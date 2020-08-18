#define TAB_TARGETLIST 0
#define TAB_ALERTAREA 1
#define TAB_IGNOREAREA 2

#define BATCHNO_COL 0
#define DIRECTION_COL 1
#define PITCH_COL 2
#define TARGETCATEGORY_COL 3
#define PLATFORMTYPEDELEGATE_COL 4
#define CONFIRM_COL 5

#define OPERATE_COL 4

#define LIST_SIZE 10

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
#include<data_test.h>
#include<Area.h>
#include<Target.h>
#include<checkbox_headerview.h>
#include<button_delegate2.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialTables();
    addTarget_Test();
    updateData_Test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialTables()
{
    alertAreasModel = new QStandardItemModel(this);
    ignoreAreasModel = new QStandardItemModel(this);
    infraredTargetModel = new TableModel(this);
    radarTargetModel = new QStandardItemModel(this);

    ui->table_alertAreas->setModel(alertAreasModel);
    initialHeaders(alertAreasModel, ui->table_alertAreas);
    initialSize(alertAreasModel, ui->table_alertAreas);

    ui->table_ignoreAreas->setModel(ignoreAreasModel);
    initialHeaders(ignoreAreasModel, ui->table_ignoreAreas);
    initialSize(ignoreAreasModel, ui->table_ignoreAreas);

    ui->table_infraredTargets->setModel(infraredTargetModel);
    initialHeaders(infraredTargetModel, ui->table_infraredTargets);
    initialSize(infraredTargetModel, ui->table_infraredTargets);
    initialDelegate(ui->table_infraredTargets);

    ui->table_radarTargets->setModel(radarTargetModel);
    initialHeaders(radarTargetModel, ui->table_radarTargets);
    initialSize(radarTargetModel, ui->table_radarTargets);
    initialDelegate(ui->table_radarTargets);

    initialDelegate(ui->table_alertAreas);
    initialDelegate(ui->table_ignoreAreas);
    initialEditorValidators();
    initialPopMenu();
}

void MainWindow::addTarget_Test()
{

    infraredTargetModel->setItem(1,1,new QStandardItem("zhang"));
//    QModelIndex index2 = infraredTargetModel->index(1,CONFIRM_COL,QModelIndex());
//    infraredTargetModel->setData(index2,Qt::CheckState::Checked,Qt::CheckStateRole);
}

void MainWindow::updateData_Test()
{
    d = new DataTest();
    connect(d,SIGNAL(sendData(Area)),this,SLOT(receiveTestData(Area)));
    connect(d,SIGNAL(sendData(Target)),this,SLOT(receiveTestData(Target)));
//    connect(d,SIGNAL(sendData(Target*)),this,SLOT(receiveTestData(Target*)));
    connect(d,SIGNAL(sendData(QVector<Target>)),this,SLOT(receiveTestData(QVector<Target>)));
    connect(infraredTargetModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(check_changed(QStandardItem*)));

    d->start();
}

void MainWindow::initialHeaders(QStandardItemModel *model, QTableView *tableView)
{
    QStringList headers;
    if (!QString::compare(tableView->objectName(),"table_infraredTargets"))
    {
        for (int i = 0; i < (int) (sizeof (FRCConst::InfraredHeaders)/sizeof (FRCConst::InfraredHeaders[0])); ++i) {
            headers.append(QString(FRCConst::InfraredHeaders[i]));
        }
        CheckboxHeaderView *headerView = new CheckboxHeaderView(Qt::Horizontal, this);
        tableView->setHorizontalHeader(headerView);
        connect(headerView, SIGNAL(stateChanged(bool)), this, SLOT(selectAllTargets(bool)));
        tableView->verticalHeader()->hide();
    }
    else if (!QString::compare(tableView->objectName(),"table_radarTargets"))
    {
        for (int i = 0; i < (int) (sizeof (FRCConst::RadarHeaders)/sizeof (FRCConst::RadarHeaders[0])); ++i) {
            headers.append(QString(FRCConst::RadarHeaders[i]));
        }
        tableView->verticalHeader()->hide();
    } else if (!QString::compare(tableView->objectName(),"table_alertAreas") || !QString::compare(tableView->objectName(),"table_ignoreAreas"))
    {
        for (int i = 0; i < (int) (sizeof (FRCConst::AreaHeaders)/sizeof (FRCConst::AreaHeaders[0])); ++i) {
            headers.append(QString(FRCConst::AreaHeaders[i]));
        }
    }
    model->setHorizontalHeaderLabels(headers);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {""color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
}

void MainWindow::initialSize(QStandardItemModel *model, QTableView *tableView)
{
    if (!QString::compare(tableView->objectName(),"table_infraredTargets"))
    {
        model->setColumnCount(6);
        model->setRowCount(10);
    }
    else if (!QString::compare(tableView->objectName(),"table_radarTargets"))
    {
        model->setColumnCount(4);
        model->setRowCount(10);
    } else if (!QString::compare(tableView->objectName(),"table_alertAreas") || !QString::compare(tableView->objectName(),"table_ignoreAreas"))
    {
        model->setColumnCount(5);
    //    alertAreasModel->setRowCount(10);
    }
    tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::initialDelegate(QTableView *tableView)
{
    if (!QString::compare(tableView->objectName(),"table_infraredTargets"))
    {
        ReadonlyDelegate* readOnlyDelegate = new ReadonlyDelegate();
        ComboBoxDelegate *targetCategoryDelegate = new ComboBoxDelegate();
        ComboBoxDelegate *platFormTypeDelegate = new ComboBoxDelegate();
        for (int i = 0; i < (int) (sizeof (FRCConst::Categroy)/sizeof (FRCConst::Categroy[0])); ++i) {
            targetCategoryDelegate->comboList.append(QString(FRCConst::Categroy[i]));
        }
        for (int i = 0; i < tableView->model()->columnCount(); ++i)
        {
            switch (i)
            {
            case TARGETCATEGORY_COL:
                tableView->setItemDelegateForColumn(i, targetCategoryDelegate);
                break;
            case PLATFORMTYPEDELEGATE_COL:
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
        for (int i = 0; i < tableView->model()->columnCount(); ++i)
        {
            tableView->setItemDelegateForColumn(i, readOnlyDelegate);
        }
    } else if (!QString::compare(tableView->objectName(),"table_alertAreas") || !QString::compare(tableView->objectName(),"table_ignoreAreas"))
    {
        ReadonlyDelegate* readOnlyDelegate = new ReadonlyDelegate();
        ButtonDelegate2* buttonDelegate = new ButtonDelegate2();
        buttonDelegate->buttonText = "删除";
        for (int i = 0; i < tableView->model()->columnCount(); ++i)
        {
            switch (i)
            {
            case OPERATE_COL:
                tableView->setItemDelegateForColumn(i, buttonDelegate);
                break;
            default:
                tableView->setItemDelegateForColumn(i, readOnlyDelegate);
                break;
            }
        }

        connect(buttonDelegate,SIGNAL(clicked(QModelIndex)),this,SLOT(receive_deleteClicked(QModelIndex)));
    }
}

void MainWindow::initialPopMenu()
{
    ui->table_alertAreas->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单
    rightClickMenu = new QMenu(ui->table_alertAreas);               //右键点击菜单
    deleteAction = new QAction("删除",this);               //删除事件
    rightClickMenu->addAction(deleteAction);    //将action添加到菜单内

    connect(ui->table_alertAreas,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_clickRightMenu(QPoint)));
    connect(rightClickMenu,SIGNAL(triggered(QAction*)),this,SLOT(slot_menuChoiceAction(QAction*)));
}

void MainWindow::initialEditorValidators()
{
    QDoubleValidator *directionValidator = new QDoubleValidator;
    directionValidator->setRange(FRCConst::MinDirection,FRCConst::MaxDirection, 2);
    QDoubleValidator *pitchValidator = new QDoubleValidator;
    pitchValidator->setRange(FRCConst::MinPitch,FRCConst::MaxPitch, 2);
    ui->lineEdit  ->setValidator(directionValidator);
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
    ui->lineEdit  ->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
}

void MainWindow::addAlertArea()
{
    // 加对象
    Area *area = new Area(ui->lineEdit  ->text().toDouble(),ui->lineEdit_2->text().toDouble(),ui->lineEdit_3->text().toDouble(),ui->lineEdit_4->text().toDouble());
    d->alertAreaList.push_back(*area);
    QList<QStandardItem *> areaParas;
    areaParas.append(new QStandardItem(ui->lineEdit  ->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_2->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_3->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_4->text()));
    alertAreasModel->appendRow(areaParas);
    // 操作 列
    alertAreasModel->setVerticalHeaderItem(alertAreasModel->rowCount() - 1, new QStandardItem(FRCConst::AlertHead+QString::number(alertAreasModel->rowCount())));
    adjustAreaHeaderNum();

    QVariant a = infraredTargetModel->data(infraredTargetModel->index(3,5,QModelIndex()),Qt::CheckStateRole);
}

void MainWindow::addIgnoreArea()
{
    // 加对象
    Area *area = new Area(ui->lineEdit_5->text().toDouble(),ui->lineEdit_6->text().toDouble(),ui->lineEdit_7->text().toDouble(),ui->lineEdit_8->text().toDouble());
    d->ignoreAreaList.push_back(*area);
    QList<QStandardItem *> areaParas;
    areaParas.append(new QStandardItem(ui->lineEdit_5->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_6->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_7->text()));
    areaParas.append(new QStandardItem(ui->lineEdit_8->text()));
    ignoreAreasModel->appendRow(areaParas);
    // 操作 列
    ignoreAreasModel->setVerticalHeaderItem(ignoreAreasModel->rowCount() - 1, new QStandardItem(FRCConst::IgnoreHead+QString::number(ignoreAreasModel->rowCount())));
    adjustAreaHeaderNum();
}

void MainWindow::adjustAreaHeaderNum()
{
    for (int i = 0; i < ignoreAreasModel->rowCount(); ++i) {
        ignoreAreasModel->setVerticalHeaderItem(i, new QStandardItem(FRCConst::IgnoreHead + QString::number(i + 1)));
    }
    for (int i = 0; i < alertAreasModel->rowCount(); ++i) {
        alertAreasModel->setVerticalHeaderItem(i, new QStandardItem(FRCConst::AlertHead + QString::number(i + 1)));
    }

}

void MainWindow::removeAllAlertAreas()
{
    // 清表格
    alertAreasModel->removeRows(0, alertAreasModel->rowCount());
    // 清对象
    d->alertAreaList.clear();
}

void MainWindow::removeAllIgnoreAreas()
{
    // 清表格
    ignoreAreasModel->removeRows(0, alertAreasModel->rowCount());
    // 清对象
    d->ignoreAreaList.clear();
}

void MainWindow::removeAlertAreaAt(int index)
{
    // 清表格
    alertAreasModel->removeRow(index);
    // 删对象
    d->alertAreaList.remove(index);
    // 刷新序号
    adjustAreaHeaderNum();
}

void MainWindow::removeIgnoreAreaAt(int index)
{
    // 清表格
    ignoreAreasModel->removeRow(index);
    // 删对象
    d->ignoreAreaList.remove(index);
    // 刷新序号
    adjustAreaHeaderNum();
}

bool MainWindow::isDirectionEmpty()
{
    if (ui->targetAlertTabWidget->currentIndex() == TAB_ALERTAREA) {
        if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty()) {
            return true;
        }
    }
    else if (ui->targetAlertTabWidget->currentIndex() == TAB_IGNOREAREA)
    {
        if (ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty() || ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty()) {
            return true;
        }
    }
    return false;
}

bool MainWindow::isDirectionValid(double startDirection, double endDirection)
{
    if ((startDirection<FRCConst::MinDirection||startDirection>FRCConst::MaxDirection) || (endDirection<FRCConst::MinDirection||endDirection>FRCConst::MaxDirection))
    {
        return false;
    }
    return true;
}

bool MainWindow::isRadiusValid(double startRadius, double endRadius)
{
    if ((startRadius<FRCConst::MinPitch||startRadius>FRCConst::MaxPitch) || (endRadius<FRCConst::MinPitch||endRadius>FRCConst::MaxPitch))
    {
        return false;
    }
    return true;
}

void MainWindow::onInit()
{
    // dataHandler
    // radarDataHandler
    // uploadPolicyHandler
    initialLineList();
    for (int i = 0; i < LIST_SIZE; ++i) {
        radarTargetList.push_back(*new Target());
        radarTargetList[i].lineNo = -1;
    }
//    upLoadFlag = UPLOAD_POLICY == "auto"?false:true;
}

void MainWindow::initialLineList()
{
    for (int i = 0; i < lineList.size(); ++i) {
        lineList.push_back(*new Target());
        lineList[i].lineNo = -1;
    }
}

void MainWindow::dataHandler()
{
    initialLineList();
    for (int i = 0; i < d->infraredTargetList.size(); ++i) {
        if (d->infraredTargetList[i].lineNo > LIST_SIZE) break;
        lineList[d->infraredTargetList[i].lineNo] = d->infraredTargetList[i];
        if (!upLoadFlag)
        {
            d->infraredTargetList[i].checked = false;
        }
    }
}

void MainWindow::radarDataHandler()
{
    radarTargetList = d->radarTargetList;
    int count = radarTargetList.size();
    if (count < LIST_SIZE)
    {
        for (int i = 0; i < LIST_SIZE - count; ++i) {
            radarResList.push_back(*new Target());
        }
        isNeedBlank = true;
    }
    else
    {
        isNeedBlank = false;
    }
}

void MainWindow::uploadPolicyHandler()
{
//    upLoadFlag = UPLOAD_POLICY == "auto"?false:true;
}

void MainWindow::setTargetValue(QString name, int index, int value)
{
    int targetIndex;
    name = name + "-" + QString::number(index);
    for (int i = 0; i < d->infraredTargetList.size(); ++i) {
        if (d->infraredTargetList[i].lineNo == index)
        {
            targetIndex = i;
        }
    }
    if (name == "targetCategory-" + QString::number(index))
    {
        d->infraredTargetList[targetIndex].categoryChangedTo = value;
    }
    else if (name == "platformType-" + QString::number(index))
    {
        d->infraredTargetList[targetIndex].platformChangedTo = value;
    }
    else if (name == "targetTag-" + QString::number(index))
    {
        d->infraredTargetList[targetIndex].tagChangedTo = value;
    }
    else if (name == "radarbatchNo-" + QString::number(index))
    {
        if (value == -1)
        {
            d->infraredTargetList[targetIndex].radarBatchNoChangedTo = 0;
        }
        else
        {
           d->infraredTargetList[targetIndex].radarBatchNoChangedTo = value;
        }
    }
}

QVariant MainWindow::getTargetValue(QString name, int index)
{
    int temp;
    QVariant result;
    if (name == "targetCategory")
    {
        temp = lineList[index].categoryChangedTo;
        result = temp==-1?lineList[index].category:temp;
    }
    else if (name == "platformType")
    {
        temp = lineList[index].platformChangedTo;
        result = temp==-1?lineList[index].platform:temp;
    }
    else if (name == "targetTag")
    {
        temp = lineList[index].tagChangedTo;
        result = temp==-1?lineList[index].tag:temp;
    }
    else if (name == "radarbatchNo")
    {
        temp = lineList[index].radarBatchNoChangedTo;
        int radarBatchNo = temp==-1?lineList[index].radarBatchNo:temp;
        if (radarBatchNo == 0) {
            result = "";
        }
        else
        {
            result = radarBatchNo;
        }
    }
    return result;
}

void MainWindow::gerRadarIndex(int targetIndex)
{
    QVector<int> radarIndexList;
    for (int i = 0; i < radarIndexList.size(); ++i) {
        if (/*d->radarTargetList[i].batchNo != NULL
                && */d->radarTargetList[i].direction < lineList[targetIndex].direction + 50
                && d->radarTargetList[i].direction > lineList[targetIndex].direction - 50
                && d->radarTargetList[i].pitch > lineList[targetIndex].pitch - 2.5
                && d->radarTargetList[i].pitch < lineList[targetIndex].pitch + 2.5)
        {
            radarIndexList.push_back(d->radarTargetList[i].batchNo);
        }
    }
}

void MainWindow::selectAllTargets(bool state)
{
    checkTableModifiable(state);
//    switchUploadPolicy();
}

void MainWindow::checkTableModifiable(bool state)
{
    infraredTargetModel->isEnable = state;
    infraredTargetModel->isSelectable = state;
}

void MainWindow::on_btn_addAlertArea_clicked()
{
//    addAlertArea();//test
    if (!isDirectionValid(ui->lineEdit->text().toDouble(), ui->lineEdit_2->text().toDouble()) || !isRadiusValid(ui->lineEdit_3->text().toDouble(), ui->lineEdit_4->text().toDouble()))
    {
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

    }
    if (!isDirectionEmpty())
    {
        addAlertArea();
        clearAllAreasInput();
//        adjustAlertArea();
    }
}

void MainWindow::on_btn_addIgnoreArea_clicked()
{
//    addIgnoreArea();//test
        if (!isDirectionValid(ui->lineEdit_5->text().toDouble(), ui->lineEdit_6->text().toDouble()) || !isRadiusValid(ui->lineEdit_7->text().toDouble(), ui->lineEdit_8->text().toDouble()))
        {
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

        }
        if (!isDirectionEmpty())
        {
            addIgnoreArea();
            clearAllAreasInput();
    //        adjustIgnoreArea();
        }
}

void MainWindow::on_btn_cancelAlertAreas_clicked()
{
    clearAllAreasInput();
    removeAllAlertAreas();
//    adjustAlertArea();
}

void MainWindow::on_btn_cancelIgnoreAreas_clicked()
{
    clearAllAreasInput();
    removeAllIgnoreAreas();
//    adjustIgnoreArea();
}

void MainWindow::receiveTestData(int data)
{
    ui->lineEdit->setText(QString::number(data));
}

void MainWindow::receiveTestData(Area area)
{
    ui->lineEdit  ->setText(QString::number(area.startDirection));
    ui->lineEdit_2->setText(QString::number(area.endDirection));
    ui->lineEdit_3->setText(QString::number(area.startPitch));
    ui->lineEdit_4->setText(QString::number(area.endPitch));

    ui->lineEdit_5->setText(QString::number(area.startDirection));
    ui->lineEdit_6->setText(QString::number(area.endDirection));
    ui->lineEdit_7->setText(QString::number(area.startPitch));
    ui->lineEdit_8->setText(QString::number(area.endPitch));
}

void MainWindow::receiveTestData(QVector<Target> targetList)
{
    //先空表格再刷新数据
//    infraredTargetModel->removeRows(0, infraredTargetModel->rowCount());
//    initialSize(infraredTargetModel, ui->table_infraredTargets);
    for (int i = 0; i < targetList.size(); ++i) {
        QModelIndex index = infraredTargetModel->index(targetList[i].lineNo,BATCHNO_COL,QModelIndex());
        infraredTargetModel->setData(index,QString("%1").arg(targetList[i].batchNo,4,10,QLatin1Char('0')));
        index = infraredTargetModel->index(targetList[i].lineNo,DIRECTION_COL,QModelIndex());
        infraredTargetModel->setData(index,targetList[i].direction);
        index = infraredTargetModel->index(targetList[i].lineNo,PITCH_COL,QModelIndex());
        infraredTargetModel->setData(index,targetList[i].direction);
        index = infraredTargetModel->index(targetList[i].lineNo,TARGETCATEGORY_COL,QModelIndex());
        infraredTargetModel->setData(index,FRCConst::Categroy[targetList[i].category]);
        index = infraredTargetModel->index(targetList[i].lineNo,PLATFORMTYPEDELEGATE_COL,QModelIndex());
        infraredTargetModel->setData(index,targetList[i].platform);
        index = infraredTargetModel->index(targetList[i].lineNo,CONFIRM_COL,QModelIndex());
        infraredTargetModel->setData(index,targetList[i].checked?Qt::CheckState::Checked:Qt::CheckState::Unchecked, Qt::CheckStateRole);
        //上色
        for (int j = 0; j < infraredTargetModel->rowCount(); ++j) {
            index = infraredTargetModel->index(targetList[i].lineNo,j,QModelIndex());
            infraredTargetModel->setData(index,FRCConst::ColorForThreatLevel2[targetList[i].threatLevel], Qt::BackgroundColorRole);
        }

    }
}

void MainWindow::receiveTestData(Target target)
{
    QModelIndex index = infraredTargetModel->index(target.lineNo,BATCHNO_COL,QModelIndex());
    infraredTargetModel->setData(index,target.batchNo);
    index = infraredTargetModel->index(target.lineNo,DIRECTION_COL,QModelIndex());
    infraredTargetModel->setData(index,target.direction);
    index = infraredTargetModel->index(target.lineNo,PITCH_COL,QModelIndex());
    infraredTargetModel->setData(index,target.direction);
    index = infraredTargetModel->index(target.lineNo,TARGETCATEGORY_COL,QModelIndex());
    infraredTargetModel->setData(index,FRCConst::Categroy[target.category]);
    index = infraredTargetModel->index(target.lineNo,PLATFORMTYPEDELEGATE_COL,QModelIndex());
    infraredTargetModel->setData(index,target.platform);
    index = infraredTargetModel->index(target.lineNo,CONFIRM_COL,QModelIndex());
    infraredTargetModel->setData(index,target.checked?Qt::CheckState::Checked:Qt::CheckState::Unchecked, Qt::CheckStateRole);
}

void MainWindow::receive_deleteClicked(QModelIndex index)
{
    //弹出提示框，看是否删除数据
    QMessageBox message(QMessageBox::NoIcon, "提示","是否删除该区域?",QMessageBox::Yes | QMessageBox::No, NULL);

    //如确认删除
    if(message.exec() == QMessageBox::Yes)
    {
        if (ui->targetAlertTabWidget->currentIndex() == TAB_ALERTAREA) {
            removeAlertAreaAt(index.row());
        }
        else if (ui->targetAlertTabWidget->currentIndex() == TAB_IGNOREAREA)
        {
            removeIgnoreAreaAt(index.row());
        }
    }
}

void MainWindow::check_changed(QStandardItem *item)
{
    if (item->index().column() == CONFIRM_COL)
    {
        for (int i = 0; i < d->infraredTargetList.size(); ++i) {
            if (d->infraredTargetList[i].lineNo == item->index().row()){
                QVariant a = item->data(Qt::CheckStateRole);
                bool b = a==Qt::CheckState::Checked?true:false;
                d->infraredTargetList[i].checked = b;
            }
        }
    }
}

void MainWindow::slot_clickRightMenu(QPoint pos)
{
    QModelIndex index = ui->table_alertAreas->indexAt(pos);    //找到tableview当前位置信息
    currentRow_Alert = index.row();    //获取到了当前右键所选的行数

    if(index.isValid())        //如果行数有效，则显示菜单
    {
        rightClickMenu->exec(QCursor::pos());
    }
}


void MainWindow::slot_menuChoiceAction(QAction *act)
{
    //弹出提示框，看是否删除数据
    QMessageBox message(QMessageBox::NoIcon, "提示","是否删除该区域?",QMessageBox::Yes | QMessageBox::No, NULL);

    //如确认删除
    if(message.exec() == QMessageBox::Yes)
    {
        if(act->text() == "删除")
        {
            removeAlertAreaAt(currentRow_Alert);
        }
    }
}
