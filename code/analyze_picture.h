#ifndef ANALYZE_PICTURE_H
#define ANALYZE_PICTURE_H
#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include<QVector>
QT_CHARTS_USE_NAMESPACE
class analyzeCanvas : public QWidget
{
    Q_OBJECT

public:
    analyzeCanvas(QWidget *parent = 0);
    QChart *m_ptrChart;
    QChartView *m_ptrChartView;
    QLineSeries * mLineSeries;
    ~analyzeCanvas();
    void draw(QVector<double>& arr);
private:
    void initUI();


};


#endif // ANALYZE_PICTURE_H
