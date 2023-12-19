#ifndef ANALYZE_CAPACITY_H
#define ANALYZE_CAPACITY_H
#include<QVector>
#include "BubbleSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
class a_c{
public:
    void Bubble(QVector<double>& array, long long& comparisons, long long& swaps);
    void Insertion_normal(QVector<double>& array, long long& comparisons, long long& swaps);
    void Insertion_proved(QVector<double>& array, long long& comparisons, long long& swaps);//二分查找找插入位置
    void Quick(QVector<double>& array, int low, int high, long long& comparisons, long long& swaps);
    void Select_nomal(QVector<double>& array, long long& comparisons, long long& swaps);
    void Select_proved(QVector<double>& array, long long& comparisons, long long& swaps);//只在最小索引交换，减少交换次数
    void Shell(QVector<double>& array, long long& comparisons, long long& swaps);
    QString analyze(long long amount,QVector<double>& array);
    QVector<double>  num_generate(int size);
private:
    void reset(QVector<double>& original,QVector<double>& now);

};


#endif // ANALYZE_CAPACITY_H
