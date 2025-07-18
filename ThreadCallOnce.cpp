#include <thread>
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;
queue<int> Q;
mutex mtx;
condition_variable cv;
void Producer()
{
    for (int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> ul(mutex);
        Q.push(i);
        cout << "Producing : " << i << endl;
        cv.notify_one();
    }
}

void Consumer()
{
    while (1)
    {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, []() -> bool
            { return !Q.empty(); });
        int i = Q.front();
        Q.pop();
        cout << "Consumming : " << i << endl;
        if (i == 9)
            break;
    }
}

int main(void)
{
    thread t1(Producer);
    thread t2(Consumer);
    t1.join();
    t2.join();
    return 0;
}
