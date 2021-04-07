#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
using namespace std;
int times = 7;
LARGE_INTEGER nFreq;
LARGE_INTEGER nBeginTime;
LARGE_INTEGER nEndTime;
//b0829027 (27+2)mod 4 =1
//quick + merge + heap
void Rand_Array(int *a, int begin, int end) //給陣列輸入隨機數
{
    for (int i = begin; i < end; i++)
    {
        a[i] = rand() % 100000 + 1;
    }
}
void Array_out(int *a,int begin, int n) //陣列輸出
{
    for (int i = begin; i < n; i++)
    {
        cout << a[i]<<"\t" ;
    }
    cout << endl;
}
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
  
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
  
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
  
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
  
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
  
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
/* void Adjust(int *a,int root,int n)
{
    int e = a[root];
    for (int j = 2 * root; j <= n;j*=2){
        if(j<n&&a[j]<a[j+1])
            j++;
        if (e >= a[j]) break;
        a[j / 2] = a[j];
    }
}
void HeapSort(int *a,int n)
{
    for (int i = n / 2; i >= 1;i--)
        Adjust(a, i, n);
    for (int i = n - 1; i >= 1;i--)
    {
        swap(a[1], a[i + 1]);
        Array_out(a,1, 12);
        Adjust(a, 1, i);
    }
} */

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
        return; //returns recursively
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
    for (int i = 0; i < times; i++)
    {
        n[i] = pow(10, i) * 10;
    }          //給N值
    int k = 0; //k為執行次數

    /* //quick sort and time
    while (k < times)
    {
        int *a = new int[n[k] + 1]; //用於排序的陣列
        srand(5);
        Rand_Array(a, n[k]);
        a[n[k]] = 200000;

        double time = 0;

        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime); //开始计时

        QuickSort(a, 0, n[k] - 1); //排序

        QueryPerformanceCounter(&nEndTime);                                                //停止计时
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

        cout << pow(10, k) * 10 << " " << time << "s" << endl;
        delete[] a;
        k++;
    } */

    /* //mergesort and time
    while (k < times)
    {
        int *a = new int[n[k]]; //用於排序的陣列
        srand(5);
        Rand_Array(a, n[k]);

        double time = 0;

        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime); //开始计时

        mergeSort(a, 0, n[k] - 1);

        QueryPerformanceCounter(&nEndTime);                                                //停止计时
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s

        cout << pow(10, k) * 10 << " " << time << "s" << endl;
        delete[] a;
        k++;
    } */
    //heapsort and time
    /* while (k < times)
    { */
        //int *a = new int[n[k]+1]; //用於排序的陣列
    int a[] = {0,12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18};//0-11
    srand(5);
    //Rand_Array(a, 0, n[k] + 1);
    Array_out(a, 1, 12);
    double time = 0;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时

    heapSort(a, 12);

    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    Array_out(a, 0, 12);
    cout << pow(10, k) * 10 << " " << time << "s" << endl;
    //delete[] a;
    k++;
    /* } */
}
