#include "analyze_picture.h"
#include <QValueAxis>
#include <QTime>
analyzeCanvas::analyzeCanvas(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartView(new QChartView())
    , mLineSeries(new QLineSeries)
{
   // setChart();
    initUI();
}

analyzeCanvas::~analyzeCanvas()
{

}

void analyzeCanvas::initUI()
{
     setWindowTitle("折线图样例");
     QValueAxis * mAxY = new QValueAxis();
     QValueAxis * mAxX = new QValueAxis();

      //y轴范围
      mAxY->setRange(0, 10);
      // Y轴分等份
      mAxY->setTickCount(10);
      mAxX->setRange(1,5000);
      mAxX->setTickCount(20);
      // 分辨设置X轴和Y轴的标题
      //mAxX->setTitleText(QString(tr("数据")));
      mAxY->setTitleText(QString(tr("密度")));
      // 将系列添加到图表
      m_ptrChart->addSeries(mLineSeries);
      m_ptrChart->setTheme(QtCharts::QChart::ChartThemeBrownSand);


      m_ptrChart->addAxis(mAxY, Qt::AlignLeft);
      m_ptrChart->addAxis(mAxX, Qt::AlignBottom);
      mLineSeries->attachAxis(mAxX);

      mLineSeries->attachAxis(mAxY);

      //突出曲线上的点
      mLineSeries->setPointsVisible(true);

      // 设置颜色
      mLineSeries->setColor(QColor(255,0,255));


      //隐藏背景
      m_ptrChart->setBackgroundVisible(true);
      //设置外边界全部为0
      m_ptrChart->setContentsMargins(0, 0, 0, 0);
      //设置内边界全部为0
      m_ptrChart->setMargins(QMargins(0, 0, 0, 0));
      //设置背景区域无圆角
      m_ptrChart->setBackgroundRoundness(0);


      //在底部显示图例
     QLegend *mlegend = m_ptrChart->legend();
     mlegend->setAlignment(Qt::AlignBottom);
     mlegend->show();
      m_ptrChartView->setChart(m_ptrChart);
//      for(int i = 0 ;i <= 12;i++){
//             mLineSeries->append(i+1, i);
//     }

      m_ptrChartView->setParent(this);
      m_ptrChartView->resize(800,450);

}

void analyzeCanvas::draw(QVector<double>& arr){
    mLineSeries->clear();
    //m_ptrChart->removeAllSeries();
    QVector<double> data(10000,0);
    for(int i=0;i<arr.size();i++){
        data[int(arr[i])]++;
    }

     m_ptrChartView->setChart(m_ptrChart);
      for(int i = 0 ;i <5000;i++){
             mLineSeries->append(i, data[i]);
     }

     m_ptrChartView->setParent(this);
     m_ptrChartView->resize(800,450);


}
