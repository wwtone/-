#include "BubbleSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QEventLoop>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>

BubbleSort::BubbleSort(QObject *parent)
    : SortObject(parent)
{
    //属性动画控制交换动画效果
    //animation.setDuration(2000);
    animation.setTargetObject(this);
    animation.setPropertyName("offset");
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);
    animation.setEasingCurve(QEasingCurve::OutQuart);
    connect(&animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
}

double BubbleSort::getOffset() const
{
    return swapOffset;
}

void BubbleSort::setOffset(double offset)
{
    swapOffset = offset;
    emit offsetChanged(offset);
    emit updateRequest();
}

/*//一般的冒泡排序写法
template<typename T>
void bubble_sort(std::vector<T>& arr)
{
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j],arr[j+1]);
            }
        }
    }
}*/

void BubbleSort::sort(int count, int interval)
{
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateRequest();
    });
    Q_UNUSED(guard)

    stop();
    initArr(count);
    setRunFlag(true);

    int len = arr.length();
    for (arrI = 0; arrI < len - 1; arrI++)
    {
        for (arrJ = 0; arrJ < len - 1 - arrI; arrJ++)
        {
            if (arr[arrJ] > arr[arrJ + 1]) {
                animation.setDuration(interval * 3);
                animation.start();
                swapFlag = true;
                loop.exec();
                if (getRunFlag()) {
                    qSwap(arr[arrJ], arr[arrJ + 1]);
                    swapFlag = false;
                }
            } else {
                animation.setDuration(interval);
                animation.start();
                loop.exec();
            }
            emit updateRequest();
            if (!getRunFlag()) {
                return;
            }
        }
        if (!getRunFlag()) {
            return;
        }
    }
}

void BubbleSort::stop()
{
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

void BubbleSort::draw(QPainter *painter, int width, int height)
{
    painter->setPen(QColor(200, 200, 200));
    const int len = arr.length();
    //边框距离
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 50;

    const int item_space = 10; //柱子横项间隔
    const int text_height = painter->fontMetrics().height();
    const int text_space = 15; //文字和柱子间隔
    const double item_width = (width + item_space - left_space - right_space) / (double)len - item_space;
    const double item_bottom = height - bottom_space;
    const double height_factor = (height - top_space - bottom_space) / (double)len;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    for (int i = 0; i < len; i++)
    {
        //色块位置x
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        //色块颜色
        color = QColor(200, 200, 200);
        //在执行排序操作的时候标记比较的两个元素
        if (getRunFlag()) {
            if (i == arrJ) {
                color = QColor(255, 170 , 0);
                if (swapFlag) {
                    item_left += swapOffset * (item_width + item_space);
                }
            } else if (i == arrJ + 1) {
                color = QColor(0, 170 , 255);
                if (swapFlag) {
                    item_left -= swapOffset * (item_width + item_space);
                }
            } else if (i >= len - arrI) {
                //已排序好的
                color = QColor(0, 170, 0);
            }
        }
        //画文字
        painter->drawText(item_left, item_bottom + text_height + text_space,
                          QString::number(arr.at(i)));
        //画色块柱子
        painter->fillRect(item_left, item_bottom - item_height,
                          item_width, item_height,
                          color);
    }
}

void BubbleSort::initArr(int count)
{
    if (count < 2) {
        return;
    }

    //初始化并随机打乱数据
    arr.resize(count);
    for (int i = 0; i < count; i++)
    {
        arr[i] = i + 1;
    }
    std::random_shuffle(arr.begin(), arr.end());

    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    swapOffset = 0.0;
    emit updateRequest();
}
