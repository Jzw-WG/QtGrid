#define FILENAME_COL 0
#define CREATIONDATE_COL 1
#define CREATIONTIME_COL 2
#define FILETYPE_COL 3
#define FILELENGTH_COL 4
#define OPERATE_COL 5

#include "playerform.h"
#include "ui_playerform.h"
#include<frc_const.h>
#include<readonly_delegate.h>
#include<button_delegate2.h>

PlayerForm::PlayerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerForm)
{
    ui->setupUi(this);
    initialTable();
    initialHeader();
    initialDelegate();
    addReplayList_Test();
}

PlayerForm::~PlayerForm()
{
    delete ui;
}

void PlayerForm::initialTable()
{
    replayModel = new QStandardItemModel(this);

    ui->table_replay->setModel(replayModel);
    initialHeader();
    initialSize();
}

void PlayerForm::initialHeader()
{
    QStringList headers;
    for (int i = 0; i < (int) (sizeof (FRCConst::ReplayHeaders)/sizeof (FRCConst::ReplayHeaders[0])); ++i) {
        headers.append(QString(FRCConst::ReplayHeaders[i]));
    }
    ui->table_replay->verticalHeader()->hide();
    replayModel->setHorizontalHeaderLabels(headers);
    ui->table_replay->horizontalHeader()->setStretchLastSection(true);
    ui->table_replay->horizontalHeader()->setStyleSheet("QHeaderView::section {""color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
}

void PlayerForm::initialSize()
{
    replayModel->setColumnCount(6);
}

void PlayerForm::initialDelegate()
{
    ReadonlyDelegate* readOnlyDelegate = new ReadonlyDelegate();
    ButtonDelegate2* buttonDelegate = new ButtonDelegate2();
    buttonDelegate->buttonText = "播放";
    for (int i = 0; i < ui->table_replay->model()->columnCount(); ++i)
    {
        switch (i)
        {
        case OPERATE_COL:
            ui->table_replay->setItemDelegateForColumn(i, buttonDelegate);
            break;
        default:
            ui->table_replay->setItemDelegateForColumn(i, readOnlyDelegate);
            break;
        }
    }
    connect(buttonDelegate,SIGNAL(clicked(QModelIndex)),this,SLOT(receive_replayClicked(QModelIndex)));
}

void PlayerForm::addReplayList_Test()
{
    for (int i = 0; i < 10; ++i) {        
        QList<QStandardItem *> areaParas;
        areaParas.append(new QStandardItem("target_2019-10-06-170010"));
        areaParas.append(new QStandardItem("2019-10-06"));
        areaParas.append(new QStandardItem(""));
        areaParas.append(new QStandardItem(".bin"));
        areaParas.append(new QStandardItem(QString("100") + QString(" KB")));
        replayModel->appendRow(areaParas);
        // 操作 列

    }
}

void PlayerForm::on_cancel_clicked()
{
    this->close();
}

void PlayerForm::receive_replayClicked(QModelIndex index)
{
    qDebug("Test");
//    replayFileByName(ReplayFile replayFile);
    on_cancel_clicked();
}

void PlayerForm::replayFileByName(ReplayFile replayFile)
{
//    if (state == "recording") {
//        stopRecorder();
//    }
    selectReplayFileByName(replayFile);
}

void PlayerForm::selectReplayFileByName(ReplayFile replayFile)
{
    emit sendPlayerCommand("play", replayFile.fileName);
//    state = "play";
}

void PlayerForm::receiveFileList(QVector<ReplayFile> replayFileList)
{
//    if (event.target != "replay_select" || event.type != "fileList") return;
    for (int i = 0; i < replayFileList.size(); ++i) {
        ReplayFile *replayFile = new ReplayFile();
        replayFile->fileName = replayFileList[i].fileName;
        replayFile->creationDate = replayFileList[i].creationDate;
//        replayFile->creationTime = replayFileList[i].creationTime;
        replayFile->recordType = replayFileList[i].recordType;
        replayFile->fileLength = replayFileList[i].fileLength;
        replayFile->duration = replayFileList[i].duration;
        replayFile->deviceid = replayFileList[i].deviceid;
        replayFile->operatorid = replayFileList[i].operatorid;
        replayFile->workingMode = replayFileList[i].workingMode;
        this->replayFileList.push_back(*replayFile);
    }
}
