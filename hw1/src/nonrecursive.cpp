#include <stdio.h>
#include <iostream>
using namespace std;

int A(int m, int n) {
    int arr[100]; //�ΰ��|�������j�I�s
    int a = -1; //��l�ư��|
    arr[++a] = m;
    while (a >= 0) {
        //�p�G���|����0�A�~��B�z
        m = arr[a--];
        if (m == 0) {
            n = n + 1;
        }//��m��0��:�^��n+1
        else if (n == 0) {
            arr[++a] = m - 1;
            n = 1;
        }//��n��0��:m=m-1�An=1
        else {
            arr[++a] = m - 1;
            arr[++a] = m;
            n = n - 1;
        }//��m!=0�An!=0��:m=m-1�An=A(m, n - 1)
    }
    return n;
}

int main() {
    int m, n;
    cout << "�п�J m �M n ����: ";
    cin >> m >> n;
    cout << "A(" << m << ',' << n << ") = " << A(m, n);
    return 0;
}