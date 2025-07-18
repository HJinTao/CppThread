#include<thread>
#include<iostream>
#include<mutex>
using namespace std;
mutex m1,m2;

void fun1(){
    m1.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    m2.unlock();
    m1.unlock();
    
}

void fun2(){
    m1.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    m2.unlock();
    m1.unlock();  
}

void fun3(){
    m2.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m1.lock();
    m1.unlock();
    m2.unlock();  
}

int main(){
    thread thread1(fun1);
    thread thread2(fun2);
    thread1.join();
    thread2.join();
    cout << "over" << endl;
    return 0;
}