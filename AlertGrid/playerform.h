#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>
#include<table_model.h>
#include<ReplayFile.h>

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerForm(QWidget *parent = nullptr);
    ~PlayerForm();
    QVector<ReplayFile> replayFileList;
    void initialTable();
    void initialHeader();
    void initialSize();
    void initialDelegate();
    void replayFileByName(ReplayFile replayFile);
    void selectReplayFileByName(ReplayFile replayFile);
    void receiveFileList(QVector<ReplayFile> replayFileList);
    void addReplayList_Test();
signals:
    void sendPlayerCommand(const char*, char*);
private slots:
    void on_cancel_clicked();
    void receive_replayClicked(QModelIndex index);

private:
    Ui::PlayerForm *ui;
    QStandardItemModel *replayModel;
};

#endif // PLAYERFORM_H
