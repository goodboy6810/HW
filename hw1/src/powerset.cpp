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
    char set[] = "abc"; //修改成想要的集合
    int n = strlen(set);
    char subset[n]; //這裡不會
    PowerSet(set, n, 0, subset);
    return 0;
}
