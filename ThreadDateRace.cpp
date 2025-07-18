#include<thread>
#include<iostream>
#include<mutex>
using namespace std;

class A{
public:
    A(){
        cout << "BORN!" << endl;
    }

    ~A(){
        cout << "DIE!" << endl;
    }
};

void fun(){
    A x;
}

int a = 1;
mutex mtx;
void addA(){
    lock_guard<mutex> lg(mtx);
    int i = 100000;
    while(i--)  a++;
    return;
}

int main(){
    thread thread1(addA);
    thread thread2(addA);
    thread1.join();
    cout << a << endl;
    
    thread2.join();
    cout << a << endl;
    return 0;
}