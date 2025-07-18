#include <thread>
#include <iostream>
#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>
#include <functional>
using namespace std;

class ThreadPool
{

private:
    bool stop;
    vector<thread> threads;        // 线程数组 获取任务 完成任务
    queue<function<void()>> tasks; // 任务队列
    mutex mtx;
    condition_variable cv;

public:
    ThreadPool(int threadsNum) : stop(false){
        for (int i = 0; i < threadsNum; i++){
            threads.emplace_back([this]{
                while(true){
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(mtx);
                        cv.wait(lock,[this]{
                            return !tasks.empty() || stop;
                        });
                        if(tasks.empty() && stop){
                            return;
                        }
                        task = (move(tasks.front()));
                        tasks.pop();
                    }   // 作用域结束lock自动解锁
                    task();
                }
            });
        }
    }

    
};

int main(int argc, char const *argv[]){

    return 0;
}
