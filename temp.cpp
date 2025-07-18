#include<thread>
#include<iostream>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;

mutex mtx;
queue<int> Q;
condition_variable cv;

void Consumer(){
    int i = INT32_MAX;
    while(i != 9){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]()->bool{
            return !Q.empty();
        });
        i = Q.front();
        cout << "Consumed:" << i << endl;
        Q.pop();
    }
}

void Producer(){
    for(int i = 0; i < 10; i++){
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> lock(mtx);
        Q.push(i);
        cout << "Produced:"<< i << endl;
        cv.notify_one();
    }
}



int main(int argc, char const *argv[])
{
    thread t2(Producer);
    thread t1(Consumer);
    t2.join();
    t1.join();
    return 0;
}
