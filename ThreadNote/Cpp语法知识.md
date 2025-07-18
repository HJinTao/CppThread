
构造函数语法

```cpp
class Person {
    int age;
    std::string name;
public:
    Person(int a, std::string n) : age(a), name(n) {}  // 初始化列表写法
};
```


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