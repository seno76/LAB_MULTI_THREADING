#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;


int main(){
    cout << "HELLOO";
    vector<int> a;
    for (int i = 0; i < 30; i++)
        a.push_back(1 + rand()%23);
    for (auto x: a)
        cout << x << endl;
}