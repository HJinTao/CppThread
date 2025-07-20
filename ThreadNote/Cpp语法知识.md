# 涉及到的C++语法知识(C++11)



## 1. 构造函数 Constructor

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



## 2. 拷贝构造函数 Copy Constructor

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





## 3. delete显示禁用函数

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



## 4. Lambda表达式

### 概念

**Lambda 是 C++ 引入的一种“匿名函数”，它可以定义在任何地方，并且可以捕获周围的变量。**

它本质上是一个**可调用对象（函数对象）**，可以像函数那样调用。

### 语法

```cpp
[capture](parameters) -> return_type {
    function_body
};
```

| 参数                       | 作用                                   |
| :------------------------- | -------------------------------------- |
| `[capture]`                | 捕获外部变量，也就是可以在函数体内使用 |
| `(parameters)`             | 参数列表                               |
| `-> return_type`（可省略） | 返回类型                               |
| `{...}`                    | 函数体                                 |

### 示例

```cpp
/*因为 lambda 表达式的类型是编译器生成的匿名类类型，我们无法直接写出它的类型名，所以必须用 auto 或 std::function 来接收。*/
auto f = [](int a, int b) { return a + b; };   
```



## 5. 成员函数

### 概念

成员函数就是定义在类里面的函数，它们是类的“行为”，用来操作类的“属性”（成员变量）。

### This

每个成员函数都有一个隐藏参数 `this`，指向调用该函数的对象。

```cpp
void fuck() {
    cout << this->name << " says: fuck!";
}
```



## 6. 友元函数

### 概念

**友元函数**是一个 **可以访问类的私有成员和保护成员** 的**非成员函数**。虽然它不是类的成员，但它获得了像成员函数一样的访问权限。

###  为什么需要友元函数？

在 C++ 中，类通常会把数据成员声明为 `private` 或 `protected`，不允许外部访问。但有时候，**你希望某些外部函数访问类的私有数据**，这时就可以使用 `friend` 来授权访问权限，而不破坏封装性。

### 基本语法

```cpp
class MyClass {
private:
    int secret;

public:
    MyClass(int s) : secret(s) {}

    // 声明友元函数
    friend void showSecret(const MyClass& obj);
};

// 定义友元函数（不是类内成员函数）
void showSecret(const MyClass& obj) {
    // 可以访问 MyClass 的私有成员
    std::cout << "Secret is: " << obj.secret << std::endl;
}

```



## 7. 运算符重载

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

### 示例

#### 1.作为成员函数重载

单目运算符作为类成员函数重载时没有型参（除了后置自增（自减）有一个整型参数：[详细点击](http://www.jb51.net/article/72424.htm)），双目运算符作为类成员函数重载时只有一个型参，作为运算符的右操作数，其左操作数就是本对象自己，也就是this。

```cpp
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    // 成员函数运算符重载：+
    Point operator+(const Point& other) const {     //  const修饰成员函数:承诺不修改成员变量
        return Point(x + other.x, y + other.y);
    }
};
```

#### 2.作为友元函数重载

作为友元函数进行重载，那么它就不存在this指针了，所以需要定义两个参数来运算（对于双目运算符）

```cpp
class Person{
private:
    string name;
    int age;
public:
    Person(const char* name, int age):name(name),age(age){}
     friend bool operator<(const Person& a,const Person& b);

};
bool operator<(const Person& a,const Person& b)
{
...
}
```



## 8. 函数指针

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



## 9. 成员函数指针

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



## 10. 模版  Template

模板（Template）是 C++ 中支持泛型编程的强大机制，可以编写适用于任意类型的代码，在编译期自动生成具体类型版本，极大提高了代码复用性和灵活性。

**模板 = “类型的占位符”**，有两种主要形式：

1. **函数模板（Function Template）** — 泛型函数
2. **类模板（Class Template）** — 泛型类（比如 `std::vector` 就是类模板）

### 0.模板的类型参数

- `typename` 和 `class` 都可以用来定义类型参数（没有区别）

```c++
template <class T>
```

- 定义非类型参数

```cpp
template <typename T, int size>
```

### 1.函数模版 Function Template

#### 基本语法

```cpp
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}
```

- `template<typename T>`声明一个类型参数`T`
	
- `T` 可被任何类型替代（int、double、string 等）

#### 使用

```cpp
int a = 3, b = 5;
double x = 3.5, y = 1.2;

cout << maxValue(a, b);    // 自动推导为 maxValue<int>
cout << maxValue(x, y);    // 自动推导为 maxValue<double>
```



### 2.类模板 Class Template

#### 基本语法

```cpp
template <typename T>
class MyVector {
private:
    T data[100];
    int size;

public:
    void push_back(T val) {
        data[size++] = val;
    }
};
```

#### 使用

```cpp
MyVector<int> vi;
vi.push_back(10);

MyVector<string> vs;
vs.push_back("hello");
```



## 11. 引用

### 0.左值&&右值

#### 左值 Lvalue

- **左值**是指表达式结束后，**有持久存储地址**（有名字的变量或对象）。
- 可以理解为“可以取地址的值”。
- 典型的左值包括：
	- 变量（如 `int x`）
	- 数组元素
	- 解引用指针得到的对象（如 `*p`）
	- 函数返回左值引用的结果

**例子**

```c++
int x = 10;    // x 是左值
x = 20;        // 可以作为赋值操作的左边，说明是左值
int* p = &x;   // 可以取地址，说明是左值
```

#### 右值 Rvalue

- **右值**是指**不具备持久存储地址的临时值**，通常是表达式的中间结果或字面量常量。
- 不能取地址，使用完即销毁。
- 常见的右值包括：
	- 字面量（如 `5`, `3.14`）
	- 临时对象（如函数返回的非引用类型）
	- 表达式结果（`x + y`）
	- 将亡值（将要被销毁的右值）

**例子**

```cpp
int x = 10;
int y = x + 5;   // x + 5 是右值，临时结果
int&& r = 20;    // 字面量20是右值，可以绑定到右值引用
```

### 1.左值引用 Lvalue Reference

- 语法：`T&`
- 只能绑定到 **左值**
- 作用：允许通过引用访问或修改已有变量

**例子**

```cpp
int x = 10;
int& ref = x;  // 左值引用，ref绑定到变量x
ref = 20;      // 修改x的值
```



### 2.右值引用 Rvalue Reference

- 语法：`T&&`
- 只能绑定到 **右值**
- 作用：实现移动语义，优化资源管理

**例子**

```cpp
int&& rref = 10;   // 右值引用绑定到字面值10（右值）
```



### 3.万能引用 Universal Reference / Forwarding Reference

- 语法：`T&&`，但出现在 **模板类型推导中**，且形参为**模板类型参数的右值引用**
- 可以同时绑定到 **左值和右值**
- 实现 **完美转发**

**例子**

```cpp
template<typename T>
void func(T&& param);  // param 是万能引用
```



## 12. 参数包扩展符（ellipsis）…

**现代 C++ 的 `...` 是可变模板参数的核心。**

### 1. 函数模板参数包

```cpp
template <typename... Args>
void func(Args... args) {
    
}
```

- `typename... Args`表示Args是一个**模版参数包**
- `Args...`：表示**模板参数包**，可以是任意多个类型。
- `args...`：表示**函数参数包**，个数和 `Args...` 对应。

### 2.`std::forward` 中的完美转发

```cpp
template <typename F, typename... Args>
void wrapper(F&& f, Args&&... args) {
    f(std::forward<Args>(args)...);  // 展开实参包
}
```

- `args...` 是函数参数包。
- `std::forward<Args>(args)...` 使用 `...` **展开每一个参数**并完美转发。
- `...` 是将参数“一个个”地传给函数。



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



## std::forward

### 概念

`std::forward` 是 C++11 中的一个非常重要的标准库函数，通常和 **万能转发** 一起使用

**作用**是根据原始参数的“值类别”（左值或右值），将参数“原样”转发出去。

### 语法

```cpp
std::forward<T>(arg)
```

### 适用情景 右值信息丢失

```cpp
void process(int& x) {
    cout << "处理左值" << endl;
}

void process(int&& x) {
    cout << "处理右值" << endl;
}

// 包装函数（没有用 std::forward）
template<typename T>
void wrapper(T&& arg) {
    process(arg);  // ❌ 这里即使传进来是右值，也被当作左值处理
}

int main() {
    int a = 10;
    wrapper(a);      // 传左值，调用 process(int&) —— 合理 ✅
    wrapper(100);    // 传右值，本应调用 process(int&&)，但却调用了 process(int&) ❌
}
```

- `wrapper(100)` 本来是右值（字面量 `100`）；
- 但由于 `arg` 是一个**具名变量**，即使你用 `T&&` 万能引用接收，**它本身是左值**；
- 所以 `process(arg)` 实际上传入的是一个**左值**，只能调用 `process(int&)`；

**右值的信息就丢失了**。

### 解决方案

```cpp
template<typename T>
void wrapper(T&& arg) {
    func(std::forward<T>(arg));  // 保留原本的值类别 ✅
}

int main() {
    int a = 5;
    wrapper(a);    // 左值 → 左值版本
    wrapper(10);   // 右值 → 右值版本 
}
```



## std::move

### 概念

`std::move(x)` 并不移动任何东西，它只是**把 `x` 转换为右值（准确说是右值引用）**，让你有机会**显式地启用“移动”而非“拷贝”**。

### 拷贝 vs 移动

```cpp
MyData(const MyData& other);        // 拷贝构造：复制资源
MyData(MyData&& other);             // 移动构造：窃取资源
```

- 拷贝构造（左值） → 创建一份新的资源副本
- 移动构造（右值） → 直接“窃取”原对象资源，避免资源复制，提高性能

### 示例

```cpp
MyData a;
MyData b = std::move(a);  // 启动移动构造
```

- `a` 是一个左值，正常情况下会调用拷贝构造；
- `std::move(a)` 把它转换成右值引用 → 于是调用移动构造函数；
- 移动构造中，通常做法是把资源指针从 `a` 转给 `b`，然后把 `a.data = nullptr;`



- 
