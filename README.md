# 41043228 41043234

作業一

## 解題說明

實作排序 n 個數字的函式，包含以下：

 Insertion Sort
 
 Quick Sort 
 
 Merge Sort 
 
 Heap Sort
 
 Composite Sort
 

## 程式實作

WorstCaseData 實作：

```cpp
#include <vector>
#include <iostream>
#include "WorstCase.h"

std::vector<int> generateWorstCaseInsertion(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return arr;
}
std::vector<int> generateWorstCaseQuick(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i; // 近乎有序
    return arr;
}
```

AverageCaseData 實作：

```cpp

#include "permute.h"
#include <cstdlib>

void permute(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}
```

空間與時間複雜度測試 實作：

```cpp
#include "SortUtils.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>

double measureTime(std::function<void(std::vector<int>&)> sortFunc, std::vector<int> arr, int repeat) {
    double totalTime = 0;
    for (int i = 0; i < repeat; ++i) {
        std::vector<int> temp = arr;
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(temp);
        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return totalTime / repeat;
}

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize / 1024;
}

```

quicksort 實作：

```cpp
#include "QuickSort.h"
#include <algorithm>

int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    return mid;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIdx = medianOfThree(arr, low, high);
        std::swap(arr[pivotIdx], arr[high]);
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}
```

mergesort 實作：

```cpp
#include "MergeSort.h"
#include <algorithm>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = 0; i < k; ++i) arr[left + i] = temp[i];
}

void mergeSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size < n; curr_size *= 2) {
        for (int left = 0; left < n - curr_size; left += 2 * curr_size) {
            int mid = left + curr_size - 1;
            int right = std::min(left + 2 * curr_size - 1, n - 1);
            merge(arr, left, mid, right);
        }
    }
}
```

heapsort 實作：

```cpp
#include "HeapSort.h"

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

insertionsort  實作：

```cpp
#include "InsertionSort.h"

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
```

compositesort  實作：

```cpp
#include "CompositeSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include <algorithm>

long long countInversions(const std::vector<int>& arr) {
    long long inversions = 0;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) ++inversions;
        }
    }
    return inversions;
}

void compositeSort(std::vector<int>& arr) {
    int n = arr.size();
    // 小規模資料：使用插入排序
    if (n < 100) {
        insertionSort(arr);
        return;
    }
    // 檢查是否近乎有序
    long long inversions = countInversions(arr);
    double inversion_ratio = static_cast<double>(inversions) / (n * (n - 1) / 2.0);
    if (inversion_ratio < 0.1) {
        insertionSort(arr);
        return;
    }
    // 檢查重複元素比例
    std::vector<int> temp = arr;
    std::sort(temp.begin(), temp.end());
    int unique_count = std::unique(temp.begin(), temp.end()) - temp.begin();
    double unique_ratio = static_cast<double>(unique_count) / n;
    if (unique_ratio < 0.5) {
        mergeSort(arr);
        return;
    }
    // 預設：使用快速排序
    quickSort(arr);
}
```

主程式實作

```cpp
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "CompositeSort.h"
#include "SortUtils.h"
#include "permute.h"
#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>
#include <ctime>

// 生成隨機資料（average-case）
std::vector<int> generateRandomData(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    permute(arr);
    return arr;
}

// 生成插入排序最壞情況（逆序）
std::vector<int> generateWorstCaseInsertion(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return arr;
}

// 生成快速排序最壞情況（近乎有序）
std::vector<int> generateWorstCaseQuick(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    return arr;
}

int main() {
    srand(time(0));
    // 測試資料規模
    std::vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    // 排序演算法列表
    std::vector<std::function<void(std::vector<int>&)>> sorts = {
        insertionSort, quickSort, mergeSort, heapSort, compositeSort
    };
    // 排序演算法名稱
    std::vector<std::string> sortNames = {
        "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort", "Composite Sort"
    };

    // 輸出表頭
    std::cout << std::left << std::setw(15) << "n";
    for (const auto& name : sortNames) {
        std::cout << std::setw(25) << (name + " Worst (us)") << std::setw(25) << (name + " Avg (us)");
    }
    std::cout << std::endl;

    // 對每個資料規模進行測試
    for (int n : ns) {
        std::cout << std::setw(15) << n;
        // 生成測試資料
        std::vector<int> worstData = generateWorstCaseQuick(n); // 使用快速排序最壞情況
        std::vector<int> avgData = generateRandomData(n);

        // 測試每個排序演算法
        for (size_t i = 0; i < sorts.size(); ++i) {
            // 測量最壞情況
            double worstTime = measureTime(sorts[i], worstData);
            // 測量平均情況
            double avgTime = measureTime(sorts[i], avgData);

            std::cout << std::fixed << std::setprecision(2);
            std::cout << std::setw(25) << worstTime << std::setw(25) << avgTime;
        }
        std::cout << std::endl;
    }

    return 0;
}

```

## 效能分析

1.時間複雜度
Insertion Sort Worst-case: $O(n^2)$

Insertion Sort Aerage-case: $O(n^2)$

Quick Sort Worst-case: $O(n^2)$

Quick Sort  Aerage-case: $O(n log n)$

Merge Sort Worst-case: $O(n log n)$

Merge Sort  Aerage-case: $O(n log n)$

Heap Sort Worst-case: $O(n log n)$

Heap Sort  Aerage-case: $O(n log n)$

Composite Sort (n < 100）：O(1)

Composite Sort (低有序度）：$O(n^2)$

Composite Sort (高重複率）：$O(n log n)$
 
2.空間複雜度
Insertion Sort：O(1)。

Quick Sort：O(log n)。

Merge Sort：O(log n)。

Heap Sort：O(1)。

Composite Sort：取決於選擇的演算法。

## 測試與驗證

1.時間(μs)
| n    |  Insertion Sort worst Time |  Insertion Sort Avg Time |  Insertion Sort worst MEM  |  Insertion Sort Avg Time  |   Quick Sort worst Time  |  Quick Sort Avg Time  |  Quick Sort worst MEM  |  Quick Sort Avg MEM  |  Merge Sort worst Time  |  Merge Sort Avg Time  |  Merge Sort worst MEM  |  Merge Sort Avg MEM  | Heap Sort worst Time  |  Heap Sort Avg Time  |  Heap Sort worst MEM  |  Heap Sort Avg MEM  |  Composite Sort worst Time |  Composite Sort Avg Time |  Composite Sort worst MEM |   Composite Sort Avg MEM  | 
|----------|--------------|----------|----------|--------------|----------|----------|--------------|----------|----------|----------|----------|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| 500  |   569.69   |  409.32    |  53  |  0  |   502.69   |   41.88    |   6   |   16    |   118.24   |    120.30    |     17    |    22   |    96.40  |    94.65    |  22   |  22 | 117.13   |   182.32  |   22  |  22  | 
| 1000 |   2541.09  |  1162.95   |  61  |  22 |   1924.20  |   104.97   |   0   |   22    |   301.54   |    347.36    |     42    |    16   |    236.30 |    213.27   |  16   |  16 | 243.87   |   435.96  |   16  |  16  |
| 2000 |   9689.96  |  5100.64   |  81  |  12 |   7657.20  |   232.35   |   40  |   19    |   560.44   |    715.64    |     60    |    15   |    475.53 |    472.07   |  15   |  15 | 681.25   |   882.79  |   23  |  15  |
| 3000 |   21733.01 |  10738.30  |  79  |  31 |   17667.50 |   426.40   |   31  |    0    |   982.30   |    956.95    |     41    |    12   |    910.35 |    886.65   |  12   |  12 | 962.86   |   1527.80 |   12  |  12  |
| 4000 |   38731.99 |  19511.23  |  119 |  0  |   31886.71 |   541.04   |   44  |    0    |   1360.43  |    1344.78   |     89    |     0   |   1175.30 |    1083.76  |   0   |   0 | 1319.05  |   2043.87 |    0  |   0  |
| 5000 |   59558.36 |  29759.68  |  28  |  28 |   48489.81 |   751.75   |   60  |    28   |   1671.40  |    1673.04   |     49    |    35   |   1332.40 |    1508.84  |  19   |  19 | 1710.93  |   2709.63 |   57  |  57  |







