#include <iostream>
#include "SortTestHelper.h"
#include "Merge.h"
#include <algorithm>

using namespace std;


// 对arr[l...r]部分进行partition操作
// 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
template <typename T>
/**
 * @brief 对数组进行分区
 *
 * 使用快速排序算法中的分区操作，对数组进行分区。
 * 将数组划分为小于给定值 v 的部分和大于 v 的部分，并返回 v 所在的新位置。
 *
 * @param arr 数组
 * @param l 数组的左边界
 * @param r 数组的右边界
 *
 * @return v 所在的新位置
 */
int __partition(T arr[], int l, int r){

     // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
    swap( arr[l] , arr[rand()%(r-l+1)+l] );
    // 选取基准值v为arr[l]
    T v = arr[l];

    // 初始化指针j，表示小于v的元素的右边界
    int j = l; // arr[l+1...j] < v ; arr[j+1...i) > v
    for( int i = l + 1 ; i <= r ; i ++ )
        // 如果arr[i]小于v
        if( arr[i] < v ){
            // 将j右移一位
            j ++;
            // 交换arr[j]和arr[i]的位置
            swap( arr[j] , arr[i] );
        }

    // 将基准值v交换到正确的位置
    swap( arr[l] , arr[j]);

    // 返回基准值v的索引
    return j;
}

// 对arr[l...r]部分进行快速排序
template <typename T>
void __quickSort(T arr[], int l, int r){
    // 如果左边界大于等于右边界，则无需排序，直接返回
    // if( l >= r )
    //     return;
    if (r-l<=15)
    {
        insertionSort(arr, l, r);
        return;
    }

    // 对数组进行划分，并返回划分后基准元素的位置
    int p = __partition(arr, l, r);

    // 对基准元素左边的子数组进行递归排序
    __quickSort(arr, l, p-1 );

    // 对基准元素右边的子数组进行递归排序
    __quickSort(arr, p+1, r);
}

template <typename T>
void quickSort(T arr[], int n){

    srand(time(NULL));
    __quickSort(arr, 0, n-1);
}

int main() {

    // Merge Sort是我们学习的第一个O(nlogn)复杂度的算法
    // 可以在1秒之内轻松处理1000万数量级的数据
    // 注意：不要轻易尝试使用SelectionSort, InsertionSort或者BubbleSort处理100万级的数据
    // 否则，你就见识了O(n^2)的算法和O(nlogn)算法的本质差异：）
    int n = 100000000;

    // 测试1 一般性测试
    // cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    // int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    // int* arr2 = SortTestHelper::copyIntArray(arr1,n);

    // SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    // SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);



    // delete[] arr1;
    // delete[] arr2;

    // cout<<endl;

    // 测试2 测试近乎有序的数组
    // 加入了随机选择标定点的步骤后, 我们的快速排序可以轻松处理近乎有序的数组
    // 但是对于近乎有序的数组, 其效率比优化后的归并排序要低, 但完全再容忍范围里
    // 思考一下为什么对于近乎有序的数组, 快排的性能比优化后的归并排序低? :)
    int swapTimes = 100000;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    int *arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;
    return 0;
}


