#include <stdio.h>
#include <iostream>
using namespace std;

int A(int m, int n) {
    if (m == 0) {
        return n + 1;
    }//當m為0時:回傳n+1
    else if (n == 0) {
        return A(m - 1, 1);
    }//當n為0時:m=m-1，n=1
    else {
        return A(m - 1, A(m, n - 1));
    }//當m!=0，n!=0時:m=m-1，n=A(m, n - 1)
}

int main() {
    int m, n;
    cout << "請輸入 m 和 n 的值: ";
    cin >> m >> n;
    cout << "A(" << m << ',' << n << ") = " << A(m, n);
    return 0;
}
