# Cpp多线程详解



## 1.1 CPU相关参数

| 参数名称                                 | 含义                 | 与多线程关系                     |
| ---------------------------------------- | -------------------- | -------------------------------- |
| **Cores（核心数）**                      | 实际的物理处理单元数 | 每个核心可执行一个线程           |
| **Threads（线程数）**                    | 可同时处理的线程数   | 表示 CPU 的并发能力              |
| **Hyper-Threading** 或 SMT（对称多线程） | 每个核心运行多个线程 | 实现一个核心同时运行多个线程     |
| **L1/L2/L3 Cache**                       | 各级缓存             | 缓存命中率影响线程执行效率       |
| **Clock Speed（主频）**                  | 每秒执行的指令周期   | 与多线程无直接关系，但影响总性能 |
| **TDP**（热设计功耗）                    | CPU发热量（功率）    | 高并发运行时功耗和散热有关       |



## 1.2 核心概念

线程是程序中的轻量级执行单元，允许程序同时执行多个任务。

多线程是多任务处理的一种特殊形式，多任务处理允许让电脑同时运行两个或两个以上的程序。

一般情况下，两种类型的多任务处理：**基于进程和基于线程**。

- 基于进程的多任务处理是程序的**并发**执行。
- 基于线程的多任务处理是同一程序的片段的**并发**执行。

### 线程(Thread)

- 线程是程序执行中的单一顺序控制流，多个线程可以在同一个进程中独立运行。
- 线程共享进程的**地址空间**、文件描述符、**堆**和**全局变量**等资源，但每个线程有自己的**栈**、**寄存器**和**程序计数器**。

### 并发 (Concurrency) 与并行 (Parallelism)

- **并发**：多个任务在时间片段内交替执行，表现出同时进行的效果。

  在**单核 CPU** 上，同时只能执行一个线程；

  操作系统通过“时间片轮转”让多个线程交替运行；

  比如线程 A 执行 10ms，暂停后线程 B 执行 10ms……，用户感觉它们在“同时”运行；

  属于 **并发**。

- **并行**：多个任务在多个处理器或处理器核上同时执行。

  在**多核 CPU** 上，每个核心可以执行一个线程；

  如果你开了 4 个线程，有 4 个核心，它们可以真正**同时运行**；

  属于 **并行**

> 实际多线程编程中通常写的是“**并发程序**”，由操作系统决定能否**并行运行**。



## 1.3 C++多线程核心组件

### C++11 及以后的标准提供了多线程支持，核心组件包括：

- **`std::thread`**：用于创建和管理线程。
- **`std::mutex`**：用于线程之间的互斥，防止多个线程同时访问共享资源。
- **`std::lock_guard`** 和 **`std::unique_lock`**：用于管理锁的获取和释放。
- **`std::condition_variable`**：用于线程间的条件变量，协调线程间的等待和通知。
- **`std::future`** 和 **`std::promise`**：用于实现线程间的值传递和任务同步

### 编译命令

```sh
g++ -std=c++11 -pthread example.cpp -o example 
```

`-std=c++11`：启用 C++11 标准

`-pthread`：启用 POSIX 线程支持



## 1.4 创建线程  std::thread

```cpp
#include<thread>
std::thread thread_object(callable, args...);
```

- **`callable`**：可调用对象，可以是函数指针、函数对象、Lambda 表达式等。
- **`args...`**：传递给 `callable` 的参数列表，需与callable。

**示范**

```cpp
void fun(int x){
    cout << x << endl;
}
thread t1(fun,3);
```



## 1.5 线程管理

当线程启动后，一定要在和线程相关联的thread销毁前，确定以何种方式等待线程执行结束。

### join()

join() 等待启动的线程完成，才会继续往下执行。

```cpp
t1.join();
```

### detach()

启动的线程自主在后台运行，当前的代码继续往下执行，不等待新线程结束。

```cpp
t1.detach();
```

### this_thread

this_thread是一个类，它有4个功能函数

| 函数        | 使用                                                  | 说明                       |
| ----------- | ----------------------------------------------------- | -------------------------- |
| get_id      | std::this_thread::get_id()                            | 获取线程id                 |
| yield       | std::this_thread::yield()                             | 放弃线程执行，回到就绪状态 |
| sleep_for   | std::this_thread::sleep_for(std::chrono::seconds(1)); | 暂停1秒                    |
| sleep_until | /                                                     | 一分钟后执行吗，如下       |



## 1.6 线程同步与互斥

在多线程编程中，线程同步与互斥是两个非常重要的概念，它们用于控制多个线程对共享资源的访问，以避免数据竞争、死锁等问题。

### 1.互斥量 (Mutex)

互斥量是一种同步原语，用于防止多个线程同时访问共享资源。当一个线程需要访问共享资源时，它首先需要锁定（lock）互斥量。**如果互斥量已经被其他线程锁定，那么请求锁定的线程将被阻塞，直到互斥量被解锁（unlock）。**

```cpp
std::mutex mtx;
mtx.lock();   // 锁定互斥锁
// 访问共享资源
mtx.unlock(); // 释放互斥锁
```



**mutex头文件**主要声明了与互斥量(**mutex**)相关的类。mutex提供了4种互斥类型，如下表所示。

| 类型                       | 说明                |
| -------------------------- | ------------------- |
| std::mutex                 | 最基本的 Mutex 类。 |
| std::recursive_mutex       | 递归 Mutex 类。     |
| std::time_mutex            | 定时 Mutex 类。     |
| std::recursive_timed_mutex | 定时递归 Mutex 类。 |

std::mutex 是C++11 中最基本的互斥量



### 2.锁 (Locks)

C++提供了多种锁类型，用于简化互斥量的使用和管理。

常见的锁类型包括：

- **std::lock_guard**：作用域锁，当构造时自动锁定互斥量，当析构时自动解锁。
- **std::unique_lock**：与std::lock_guard类似，但提供了更多的灵活性，例如可以转移所有权和手动解锁。

```cpp
mutex mtx;  
void print_block (int n, char c) 
{
    lock_guard<mutex> lock(mtx);     //在新的作用域都要声明一次
    for (int i=0; i<n; ++i) 
    {
       std::cout << c; 
    }
    cout << '\n';
}
```



### 3.条件变量 (Condition Variable)

条件变量用于线程间的协调，允许一个或多个线程等待某个条件的发生。它通常与互斥量一起使用，以实现线程间的同步。

**condition_variable头文件**有两个variable类，一个是`condition_variable`，另一个是`condition_variable_any`。

1. `condition_variable`必须结合`unique_lock`使用。

2. `condition_variable_any`可以使用任何的锁。

**condition_variable条件变量可以阻塞（`wait`、`wait_for`、`wait_until`）调用的线程直到使用（`notify_one`或`notify_all`）通知恢复为止。**

condition_variable是一个类，这个类既有构造函数也有析构函数，使用时需要构造对应的condition_variable对象，调用对象相应的函数来实现上面的功能。



#### wait

当前线程调用 wait() 后将被阻塞*(此时当前线程应该获得了锁(mutex)，不妨设获得锁 lck)，*直到另外某个线程调用 notify 唤醒了当前线程。

在线程被阻塞时，该函数会自动调用 lck.unlock() 释放锁，使得其他被阻塞在锁竞争上的线程得以继续执行。

一旦当前线程获得通知(notified，通常是另外某个线程调用 notify唤醒了当前线程)，wait()函数将自动调用 lck.lock()，使得lck的状态和 wait 函数被调用时相同。



##### **函数原型**

```cpp
void wait(std::unique_lock<std::mutex>& lock);

template< class Predicate >
void wait(std::unique_lock<std::mutex>& lock, Predicate pred);
```



##### 示例

```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void workerThread() {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{ return ready; }); // 等待条件
    // 当条件满足时执行工作
}

void mainThread() {
    {
        std::lock_guard<std::mutex> lk(mtx);
        // 准备数据
        ready = true;
    } // 离开作用域时解锁
    cv.notify_one(); // 通知一个等待的线程
}
```

























