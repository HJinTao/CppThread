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
    bool stop;                      // 指示线程池是否应该停止
    vector<thread> threads;        // 线程数组 获取任务 完成任务
    queue<function<void()>> tasks; // 任务队列
    mutex mtx;                      // mutex主要是保护共享状态 (tasks,stop) 防止多个线程同时修改
    condition_variable cv;

    void threadWork(){

    }

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

    ~ThreadPool(){
        {
            unique_lock<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for(auto &t : threads){
            t.join();
        }
    }

    template<class F,class... Args> void enqueue(F&& f,Args&&... args){
        function<void()> task = bind(forward<F>(f),forward<Args>(args)...);
        {
            unique_lock<mutex> lock(mtx);
            tasks.emplace(move(task));
        }
        cv.notify_one();
    }

};

int main(){
    
    ThreadPool pool(4);
    for(int i = 0; i < 10;i++){
        pool.enqueue([i]{
            printf("task %d is running\n",i);
            this_thread::sleep_for(chrono::seconds(1));
            printf("task %d is done\n",i);
        });
    }

    return 0;
}
