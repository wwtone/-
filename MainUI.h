#pragma once
#include <QMainWindow>
#include"analyze_window.h"

namespace Ui {
class MainUI;
}

//主窗口

class MainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);
    ~MainUI();

private slots:
    void on_analyze_clicked();

private:
    void init();

private:
    Ui::MainUI *ui;
};
