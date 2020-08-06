#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QTableView>
#include<table_model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialTables();
    void addTarget();
    void clearAllAreasInput();
    void removeAllAlertAreas();
    void removeAllIgnoreAreas();
    bool isDirectionEmpty();
private slots:
    void on_btn_addAlertArea_clicked();

    void on_btn_addIgnoreArea_clicked();

    void on_btn_cancelAlertAreas_clicked();

    void on_btn_cancelIgnoreAreas_clicked();

private:
    Ui::MainWindow *ui;
    AreasTableModel *alertAreasModel;
    AreasTableModel *ignoreAreasModel;
    QStandardItemModel *infraredTargetModel;
    QStandardItemModel *radarTargetModel;
    void static initialDelegate(QTableView *tableView);
    void static initialHeaders(QStandardItemModel *model, QTableView *tableView);
    void initialEditorValidators();
};
#endif // MAINWINDOW_H
