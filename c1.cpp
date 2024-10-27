#include<iostream>
#include<random>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 2500);
 
    cout << distrib(gen) << endl;
 
} 