#include <stdio.h>
#include <iostream>
using namespace std;

int A(int m, int n) {
    if (m == 0) {
        return n + 1;
    }//��m��0��:�^��n+1
    else if (n == 0) {
        return A(m - 1, 1);
    }//��n��0��:m=m-1�An=1
    else {
        return A(m - 1, A(m, n - 1));
    }//��m!=0�An!=0��:m=m-1�An=A(m, n - 1)
}

int main() {
    int m, n;
    cout << "�п�J m �M n ����: ";
    cin >> m >> n;
    cout << "A(" << m << ',' << n << ") = " << A(m, n);
    return 0;
}
