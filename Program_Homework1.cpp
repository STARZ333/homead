#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
using namespace std;
int times = 101;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
//b0829027 (27+2)mod 4 =1
//quick + merge + heap
void Rand_Array(int *a, int begin, int end) //給陣列輸入隨機數
{
    int num;
    int totalNum;
    srand(5);
    for (int i = begin; i < end; i++)
    {
        totalNum = 0;
        for (int j = 0; j < 5; j++)
        {
            num = rand() % 10;
            totalNum += num * pow(10, j);
        }
        totalNum = totalNum / 2 + 1;
        a[i] = totalNum;
    }
}
void Array_out(int *a, int begin, int n) //陣列輸出
{
    for (int i = begin; i < n; i++)
    {
        cout << a[i] << "\t";
    }
    cout << endl;
}
void heapify(int arr[], int n, int i)
{
    int largest = i;   // 父節點
    int l = 2 * i + 1; // 左子，陣列從0開始，需要+1
    int r = 2 * i + 2; // 右子

    //左子比父節點大
    if (l < n && arr[l] > arr[largest])
        largest = l;

    //右子比父節點大
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // 上面情況有發生
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // 向下遞迴
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n)
{
    // 從最後一顆樹開始n / 2 - 1
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // 排序完一次頭尾交換，最後一個不進入下一次排序
        swap(arr[0], arr[i]);

        // 從根0向下比較交換
        heapify(arr, i, 0);
    }
}

//分成[l:m]和[m+1:r]兩個部分
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    //左右陣列的初始位置
    int i = 0;

    int j = 0;

    // 合成後的陣列位置
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //把兩邊剩下的資料貼上
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l >= r)
    {
        return; 
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}
void QuickSort(int *a, int left, int right)
{
    if (left < right)
    {
        int i = left,
            j = right + 1,
            pivot = a[left];
        do
        {
            do
                i++;
            while (a[i] < pivot);
            do
                j--;
            while (a[j] > pivot);
            if (i < j)
            {
                swap(a[i], a[j]);
                //Array_out(a, 11);
            }
        } while (i < j);
        swap(a[left], a[j]);
        //Array_out(a, 11);
        QuickSort(a, left, j - 1);

        QuickSort(a, j + 1, right);
        //Array_out(a, 11);
    }
}
int main()
{
    int n[times]; //10  100  1000  10000  100000
    for (int i = 1; i < times; i++)
    {
        n[i] = i * 1000;
    } //給N值
    int mode_select, amount;
    cout << "Select:" << endl;
    while (1)
    {
        cout << "1.Quicksort\t2.Mergesort\t3.Heapsort\t4.ALL Auto 1,000 to 100,000\t0.Quit" << endl;
        cin >> mode_select;
        if (mode_select == 0)
            break;
        if (mode_select == 4)
        {
            int k = 1; //k為執行次數
            cout << "quicksort and time" << endl;
            //quick sort and time
            while (k < times)
            {
                int *a = new int[n[k] + 1]; //用於排序的陣列

                Rand_Array(a, 0, n[k]);
                a[n[k]] = 200000;

                double time = 0;

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime); //开始计时

                QuickSort(a, 0, n[k] - 1); //排序

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << n[k] << " " << time << "s" << endl;
                delete[] a;
                k++;
            }
            k = 1;
            cout << "mergesort and time" << endl;
            //mergesort and time
            while (k < times)
            {
                int *a = new int[n[k]]; //用於排序的陣列
                Rand_Array(a, 0, n[k]);

                double time = 0;

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime); //开始计时

                mergeSort(a, 0, n[k] - 1);

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << n[k] << " " << time << "s" << endl;
                delete[] a;
                k++;
            }
            k = 1;
            cout << "heapsort and time" << endl;
            //heapsort and time
            while (k < times)
            {
                int *a = new int[n[k]]; //用於排序的陣列
                //int a[] = {0,12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18};//0-11

                Rand_Array(a, 0, n[k]);

                double time = 0;

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime); //开始计时

                heapSort(a, n[k]);

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << n[k] << " " << time << "s" << endl;
                delete[] a;
                k++;
            }
        }
        else
        {
            cout << "input amount:" << endl;
            cin >> amount;
            if (mode_select == 1) //quicksort
            {
                int *a = new int[amount + 1]; //用於排序的陣列

                Rand_Array(a, 0, amount);
                a[amount] = 200000;

                double time = 0;

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime); //开始计时

                QuickSort(a, 0, amount - 1); //排序

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << amount << " " << time << "s" << endl;
                cout << "Output results?(1/0)" << endl;
                int ifResults;
                cin >> ifResults;
                if (ifResults)
                    Array_out(a, 0, amount);
                delete[] a;
            }
            else if (mode_select == 2) //mergesort
            {

                int *a = new int[amount]; //用於排序的陣列
                Rand_Array(a, 0, amount);

                double time = 0;

                QueryPerformanceFrequency(&nFreq);//获得机器内部计时器的时钟频率
                QueryPerformanceCounter(&nBeginTime); //开始计时

                mergeSort(a, 0, amount - 1);

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << amount << " " << time << "s" << endl;
                cout << "Output results?(1/0)" << endl;
                int ifResults;
                cin >> ifResults;
                if (ifResults)
                    Array_out(a, 0, amount);
                delete[] a;
            }
            else if (mode_select == 3) //heapsort
            {
                int *a = new int[amount]; //用於排序的陣列

                Rand_Array(a, 0, amount);

                double time = 0;

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime); //开始计时

                heapSort(a, amount);

                QueryPerformanceCounter(&nEndTime);                                                //停止计时
                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

                cout << amount << " " << time << "s" << endl;
                cout << "Output results?(1/0)" << endl;
                int ifResults;
                cin >> ifResults;
                if (ifResults)
                    Array_out(a, 0, amount);
                delete[] a;
            }
        }
    }
}
