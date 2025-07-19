# 涉及到的C++语法知识



## 构造函数 Constructor

### 概念

当用类创建对象时，构造函数会被**自动调用**

```cpp
Student stu;
```



### 语法

```cpp
class Student {
public:
    std::string name;
    int age;

    // 无参构造
    Student() : name(""), age(0) {}

    // 带一个参数
    Student(std::string n) : name(n), age(0) {}

    // 带两个参数
    Student(std::string n, int a) : name(n), age(a) {}
};
```



## 拷贝构造函数 Copy Constructor

### 概念



拷贝构造函数 什么时候会被调用

拷贝复制运算符
delete禁用

函数指针

成员函数 && 成员函数指针
运算符重载

友元函数

野指针

构析函数&&构造函数

单例模式 

Lambda表达式
[捕获列表] (参数列表) -> 返回类型 {
    函数体
}

function

move 

emplace_back

右值引用 
左值引用

万能引用

template