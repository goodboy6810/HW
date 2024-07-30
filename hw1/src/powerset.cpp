#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

void PowerSet(char *set, int n, int index, char *subset) {
    if (index == n) {
        cout<<subset;
        return;
    }
    subset[index] = ' ';
    PowerSet(set, n, index + 1, subset);
    subset[index] = set[index];
    PowerSet(set, n, index + 1, subset);
}

int main() {
    char set[] = "abc"; //�ק令�Q�n�����X
    int n = strlen(set);
    char subset[n]; //�o�̤��|
    PowerSet(set, n, 0, subset);
    return 0;
}
