#include "analyze_window.h"
#include "ui_analyze_window.h"
#include <QListView>
#include<QMessageBox>
#include<iostream>
#include<analyze_picture.h>
analyze_window::analyze_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analyze_window)
{
    ui->setupUi(this);
    init();
}

analyze_window::~analyze_window()
{
    delete ui;
}
void analyze_window::onComboBoxActivated(int index){
    if (index == 0) {
        ui->textout->clear();
            bool ok;
            int inputValue = QInputDialog::getInt(this, tr("输入数字"), tr("请输入一个数字:"), 2000, 0, 1000000, 100, &ok);
            if (ok) {
                amount = inputValue;
            }
        }
    else if (index == 1) {
        ui->textout->clear();
           QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), QDir::homePath(), tr("所有文件 (*.*)"));
           // 弹出文件选择对话框，并返回用户选择的文件路径
           if (!filePath.isEmpty()) {
               // 保存文件路径
               selectedFilePath = filePath;
           }
       }
}
void analyze_window::init(){

    //下拉框item行高
    ui->type_select->setView(new QListView(this));
    //数据来源
    QStringList strList;
    strList<<"随机生成"<<"文件读取";
    ui->type_select->addItems(strList);
    connect(ui->type_select, QOverload<int>::of(&QComboBox::activated), this, &analyze_window::onComboBoxActivated);
    ui->al_picture->show();

}

void analyze_window::on_a_start_clicked()
{

    QString text;
    if(ui->type_select->currentIndex()==0&&amount!=0){
        text="总排序数："+QString::number(amount)+"\n";
        QVector<double> array=ac_object.num_generate(amount);
        text+=ac_object.analyze(amount,array);
        ui->al_picture->draw(array);

        ui->textout->setText(text);

    }
    else if(ui->type_select->currentIndex()==1){
        QVector<double> array;
           QString filePath = selectedFilePath; // 使用 QString 指定文件路径
           QFile file(filePath);
           if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QTextStream in(&file);
               while (!in.atEnd()) {
                   QString line = in.readLine();
                   bool ok;
                   double number = line.toDouble(&ok);
                   if (ok) { // 如果转换成功
                       array.push_back(number);
                   }
               }
               file.close();
           } else {
               // 文件打开失败的处理
               qDebug() << "无法打开文件";
           }

           text=ac_object.analyze(amount,array);
           ui->al_picture->draw(array);
           ui->textout->setText(text);

    }


}
