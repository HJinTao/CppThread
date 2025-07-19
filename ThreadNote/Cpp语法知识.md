# 涉及到的C++语法知识(C++11)



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

一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。

### 语法

```cpp
MyClass(const MyClass &other) {  // 错误形参(const MyClass other) 会无限递归调用拷贝构造函数 &引用则不会调用
    x = other.x;
}
```

### 应用场景

1. 一个对象作为函数参数，以值传递的方式传入函数体

```cpp
void fun(MyClass A){}
fun(A);       
```

2. 一个对象作为函数返回值，以值传递的方式从函数返回

```cpp
MyClass fun(MyClass A){return A;}
fun(A); 
```

3. 一个对象用于给另外一个对象进行初始化(常称为赋值初始化)

```cpp
MyClass B = A;
MyClass C(A);
```

### 深拷贝 vs 浅拷贝

**浅拷贝**：只是简单拷贝指针，多个对象共享同一块内存（可能导致问题）。

**深拷贝**：分配新的内存，复制内容，避免共享。



## 运算符重载

### 概念

自定义类对象之间用运算符，把运算符变成函数

### 语法

```cpp
class 类名 {
public:
    返回类型 operator运算符(参数) {
        // 自定义逻辑
    }
};
```

```cpp
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    // 运算符重载：+
    Point operator+(const Point& other) const {     //  const修饰成员函数:承诺不修改成员变量
        return Point(x + other.x, y + other.y);
    }
};
```



## delete显示禁用函数

### 概念

在 C++11 及以上版本中，可以使用 `= delete` 来**显式禁用函数**，包括构造函数、拷贝构造、赋值运算符等。

### 语法

```cpp
class MyClass {
public:
    MyClass() = default;

    MyClass(const MyClass&) = delete;        // 禁用拷贝构造
    MyClass& operator=(const MyClass&) = delete; // 禁用赋值
};
```



## Lambda表达式

### 概念

**Lambda 是 C++ 引入的一种“匿名函数”，它可以定义在任何地方，并且可以捕获周围的变量。**

它本质上是一个**可调用对象（函数对象）**，可以像函数那样调用。

### 语法

```cpp
[capture](parameters) -> return_type {
    function_body
};
```

| 参数                       | 作用               |
| :------------------------- | ------------------ |
| `[capture]`                | 捕获外部变量的方法 |
| `(parameters)`             | 参数列表           |
| `-> return_type`（可省略） | 返回类型           |
| `{...}`                    | 函数体             |

### 示例

```cpp
/*因为 lambda 表达式的类型是编译器生成的匿名类类型，我们无法直接写出它的类型名，所以必须用 auto 或 std::function 来接收。*/
auto f = [](int a, int b) { return a + b; };   
```



## 成员函数

### 概念

成员函数就是定义在类里面的函数，它们是类的“行为”，用来操作类的“属性”（成员变量）。

### This

每个成员函数都有一个隐藏参数 `this`，指向调用该函数的对象。

```cpp
void fuck() {
    cout << this->name << " says: fuck!";
}
```



## 函数指针

### 概念

函数存放在内存的代码区域内，它们同样有地址.如果我们有一个 **int test(int a)** 的函数，那么，**它的地址就是函数的名字**，这一点如同数组一样，数组的名字就是数组的起始地址。

### 语法

```cpp
data_types (*func_pointer)( data_types arg1, data_types arg2, ...,data_types argn);
```

```cpp
int (*fp)(int a); // 这里就定义了一个指向函数(这个函数参数仅为一个 int 类型，函数返回值是 int 类型)的指针 fp。
```

```cpp
int add(int a, int b) {
    return a + b;
}
int (*fp)(int, int); // 声明一个指向返回int，参数为(int, int) 的函数指针
fp = add;
fp = &add;  // & 可省略
```

### 调用函数指针

```cpp
int result = fp(3, 5);  // 就像调用函数一样

void operate(int a, int b, int (*op)(int, int)) {
    cout << "Result: " << op(a, b) << endl;
}
```



## 成员函数指针

### 注意事项

成员函数指针不能直接调用，必须加上对象

### 语法

```cpp
class MyClass {
public:
    void greet() {
        std::cout << "Hello!" << std::endl;
    }
};
int main() {
    MyClass obj;

    // 定义成员函数指针
    void (MyClass::*funcPtr)() = &MyClass::greet;   //不属于具体对象，需要结合对象调用

    // 使用成员函数指针调用函数：必须通过对象或指针
    (obj.*funcPtr)();        // 输出 Hello!
    
    MyClass* pObj = &obj;
    (pObj->*funcPtr)();      // 输出 Hello!
    
}
```

```cpp
thread thread1(&MyClass::greet,&obj);
thread thread2(funcPtr,&obj);
```



## std::bind

### 概念

`std::bind` 是 C++11 引入的工具，用来**将函数的一部分参数预先绑定（固定）住，返回一个可调用对象**

### 语法

```cpp
std::bind(可调用对象, 参数1, 参数2, ...)
```

- **可调用对象**：普通函数、lambda、成员函数指针、函数对象等。

参数可以是：

- **具体值**：提前绑定的参数。
- **占位符**（`std::placeholders::_1`, `_2`, ...）：调用新函数对象时传入的参数。

### 示例

#### 1.绑定普通函数

```cpp
int add(int a, int b) {
    return a + b;
}
int main() {
    auto add5 = std::bind(add, 5, std::placeholders::_1);  // 第一个参数绑定为5，第二个留着外部输入
    std::cout << add5(3);  // 输出 8，相当于调用 add(5, 3)
}
```

#### 2.绑定成员函数

```cpp
class MyClass {
public:
    void greet(int x) {
        std::cout << "Hello x" << x << "\n";
    }
};
int main() {
    MyClass obj;
    auto f = std::bind(&MyClass::greet, &obj, std::placeholders::_1); // 传入成员函数指针 + 实例引用
    f(3);  // 调用 obj.greet(3)
}
```



## std :: function

### 概念

`std::function` 是 C++11 引入的一个**通用的函数包装器（function wrapper）**，可以储存：

- 普通函数
- Lambda 表达式
- 函数指针
- 成员函数（配合 `std::bind`）

### 语法

#### 1.普通函数(普通函数指针)

```cpp
int add(int a, int b) {
    return a + b;
}
int main() {
    function<int(int, int)> f = add;
    cout auto lambda = [](int x, int y) { return x * y; };
}
```

#### 2.Lambda表达式

```cpp
auto lambda = [](int x, int y) { return x * y; };
function<int(int, int)> f2 = lambda;
```

#### 3.成员函数

```cpp
class MyClass {
public:
    int multiply(int a, int b) {
        return a * b;
    }
};
int main() {
    MyClass obj;
    function<int(int, int)> f = bind(&MyClass::multiply, &obj, placeholders::_1, placeholders::_2);
    cout << f(2, 5) << endl; // 输出 10
}
```



函数模版

友元函数

野指针

构析函数

单例模式 



static

move 

emplace_back

右值引用 
左值引用

万能引用

template



forward

