#ifndef ANALYZE_WINDOW_H
#define ANALYZE_WINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QInputDialog>
#include"analyze_capacity.h"

namespace Ui {
class analyze_window;
}

class analyze_window : public QWidget
{
    Q_OBJECT

public:
    explicit analyze_window(QWidget *parent = nullptr);
    ~analyze_window();

public slots:
    void onComboBoxActivated(int index);


private slots:
    void on_a_start_clicked();

private:
    Ui::analyze_window *ui;
    QString selectedFilePath;//自定义的文件路径
    long long amount;
    a_c ac_object;
    void init();
};

#endif // ANALYZE_WINDOW_H
