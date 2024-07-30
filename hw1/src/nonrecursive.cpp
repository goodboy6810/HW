#include <stdio.h>
#include <iostream>
using namespace std;

int A(int m, int n) {
    int arr[100]; //用堆疊模擬遞迴呼叫
    int a = -1; //初始化堆疊
    arr[++a] = m;
    while (a >= 0) {
        //如果堆疊不為0，繼續處理
        m = arr[a--];
        if (m == 0) {
            n = n + 1;
        }//當m為0時:回傳n+1
        else if (n == 0) {
            arr[++a] = m - 1;
            n = 1;
        }//當n為0時:m=m-1，n=1
        else {
            arr[++a] = m - 1;
            arr[++a] = m;
            n = n - 1;
        }//當m!=0，n!=0時:m=m-1，n=A(m, n - 1)
    }
    return n;
}

int main() {
    int m, n;
    cout << "請輸入 m 和 n 的值: ";
    cin >> m >> n;
    cout << "A(" << m << ',' << n << ") = " << A(m, n);
    return 0;
}