#include"analyze_capacity.h"
#include <chrono>
#include <random>
using namespace std;

QVector<double> a_c::num_generate(int size){
    QVector<double> arr;
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> distribution(1, 500);
    for (int i = 0; i < size; ++i) {
            arr.push_back(distribution(gen));
        }
    return arr;

}

void a_c::reset(QVector<double>& original,QVector<double>& now){
    for(int i=0;i<original.size();i++)
        now[i]=original[i];
}


void a_c:: Bubble(QVector<double>& arr, long long& comparisons, long long& swaps){
    int len = arr.length();
    bool swapped;
    for (int arrI = 0; arrI < len - 1; arrI++){
        swapped = false;
        for (int arrJ = 0; arrJ < len - 1 - arrI; arrJ++){
            ++comparisons;
            if (arr[arrJ] > arr[arrJ + 1]) {
                ++swaps;
                qSwap(arr[arrJ], arr[arrJ + 1]);
                swapped = true;
            }
        }
        if (!swapped){
            break;
        }
    }


}

void a_c:: Insertion_normal(QVector<double>& arr, long long& comparisons, long long& swaps){
        int n = arr.size();

        for (int i = 1; i < n; ++i) {
            double key = arr[i];
            int j = i - 1;
            ++comparisons;
            // 将比 key 大的元素向后移动
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                ++swaps;
                --j;
                ++comparisons;
            }

            arr[j + 1] = key;
        }
}


int binarySearch(const QVector<double>& array, int left, int right, double key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == key) {
            return mid;
        } else if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

void a_c::Insertion_proved(QVector<double>& array, long long& comparisons, long long& swaps){
    int n = array.size();

       for (int i = 1; i < n; ++i) {
           double key = array[i];
           int insertPosition = binarySearch(array, 0, i - 1, key);

           // 移动元素以腾出插入位置
           for (int j = i - 1; j >= insertPosition; --j) {
               array[j + 1] = array[j];
               ++swaps; // 记录交换次数
           }

           array[insertPosition] = key;

           // 记录比较次数
           comparisons += (i - insertPosition);
       }
}

void swap(double& a, double& b, long long& swaps) {
    double temp = a;
    a = b;
    b = temp;
    ++swaps;
}

int partition(QVector<double>& array, int low, int high, long long& comparisons, long long& swaps) {
    double pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        // 记录比较次数
        ++comparisons;

        if (array[j] < pivot) {
            ++i;
            swap(array[i], array[j], swaps);
        }
    }
    swap(array[i + 1], array[high], swaps);
    return (i + 1);
}

void a_c:: Quick(QVector<double>& array, int low, int high, long long& comparisons, long long& swaps){
    if (low < high) {
            int partitionIndex = partition(array, low, high, comparisons, swaps);

            Quick(array, low, partitionIndex - 1, comparisons, swaps);
            Quick(array, partitionIndex + 1, high, comparisons, swaps);
        }

}
void a_c:: Select_nomal(QVector<double>& array, long long& comparisons, long long& swaps){
    int n = array.size();

        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;

            for (int j = i + 1; j < n; ++j) {
                // 记录比较次数
                ++comparisons;

                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }

            // 交换元素
            if (minIndex != i) {
                swap(array[i], array[minIndex],swaps);
            }
        }
}


void a_c::Select_proved(QVector<double> &array, long long &comparisons, long long &swaps){
        int n = array.size();

       for (int i = 0; i < n - 1; ++i) {
           int minIndex = i;

           for (int j = i + 1; j < n; ++j) {
               // 记录比较次数
               ++comparisons;

               if (array[j] < array[minIndex]) {
                   minIndex = j;
               }
           }

           // 仅在找到最小元素后进行交换
           if (minIndex != i) {
               std::swap(array[i], array[minIndex]);
               // 记录交换次数
               ++swaps;
           }
       }
}


void a_c:: Shell(QVector<double>& array, long long& comparisons, long long& swaps){
    int n = array.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                double temp = array[i];
                int j;

                // 在每个子序列中进行插入排序
                for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                    // 记录比较次数
                    ++comparisons;

                    array[j] = array[j - gap];
                    // 记录交换次数
                    ++swaps;
                }

                // 将元素插入到正确的位置
                array[j] = temp;
            }
        }
}


QString a_c::analyze(long long amount,QVector<double>& array){
    //QVector<double> array;
    //array=num_generate(amount);
//    for(int i=0;i<array.size();i++)//初始化用于重置的Vector
//        original[i].push_back(array.at(i));
    QVector<double> original(array);
    long long comparisons=0,swaps=0;
    QString text;
    auto beforeTime =chrono::steady_clock::now();
    Bubble(array,comparisons,swaps);
    auto afterTime =chrono::steady_clock::now();
    double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text="冒泡排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Insertion_normal(array,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="未优化插入排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Insertion_proved(array,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="优化插入排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Select_nomal(array,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="未优化选择排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Select_proved(array,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="优化选择排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Shell(array,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="希尔排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;
    reset(original,array);

    beforeTime =chrono::steady_clock::now();
    Quick(array,0,array.size()-1,comparisons,swaps);
    afterTime =chrono::steady_clock::now();
    duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    text+="快速排序 用时："+QString::number(duration_second)+" 比较次数："+QString::number(comparisons)+" 交换次数："+QString::number(swaps)+"\n";
    comparisons=0;
    swaps=0;

    text+="\n\n冒泡排序 平均时间复杂度：O(n^2) 稳定性：稳定\n插入排序 平均时间复杂度：O(n^2) 稳定性：稳定\n选择排序 平均时间复杂度：O(n^2) 稳定性：不稳定\nShell排序 平均时间复杂度：O(nlogn) 稳定性：不稳定\n快速排序 平均时间复杂度：O(nlogn) 稳定性：不稳定";

    return text;
}
