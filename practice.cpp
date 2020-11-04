#include <iostream>
using namespace std;

int counter();

int main () {
    cout << "yoOOooOoOOO" << endl;
    int x = 3;
    counter(x);
    return 0;
}

int counter(int i) {
    i++;
    return i;
}