## 1. std::function

std::function 是 C++ 标准库中的一个模板类，用于包装和管理可调用对象（callable objects），包括函数、函数指针、成员函数指针、函数对象、Lambda 表达式等。它提供了一种通用的方式来表示和调用各种不同类型的可调用对象，从而增加了代码的灵活性和可复用性。

### 1. 绑定全局函数

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> operation = add;
    int result = operation(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}

```

### 2. 绑定成员函数

```cpp
#include <iostream>
#include <functional>

class MyClass {
public:
    void greet(const std::string& name) {
        std::cout << "Hello, " << name << "!" << std::endl;
    }
};

int main() {
    MyClass obj;
    auto member_func = std::bind(&MyClass::greet, &obj, "Bob");
    member_func(); // 调用 obj.greet("Bob")
    return 0;
}


```

### 3. 使用Lambda表达式

```cpp
#include <iostream>
#include <functional>

int main() {
    std::function<int(int, int)> operation = [](int a, int b) { return a * b; };
    int result = operation(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}


```

### 4. 部分函数应用

```cpp
#include <iostream>
#include <functional>

int main() {
    std::function<int(int, int)> operation = [](int a, int b) { return a * b; };
    int result = operation(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}

```

### 5. 函数适配器

```cpp
void test05() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int target = 5;

    // 使用 std::count_if 和函数适配器，计算大于 target 的元素个数
    std::function<bool(int)> isGreaterThanTarget = [target](auto &&PH1) {
        return std::less<int>()(std::forward<decltype(PH1)>(PH1), target);
    };
    int count = std::count_if(numbers.begin(), numbers.end(), isGreaterThanTarget);

    std::cout << "Count: " << count << std::endl;
}
```

### 6. 多态行为

```cpp
#include <iostream>
#include <functional>

class Animal {
public:
    virtual void speak() const = 0;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    std::function<void(const Animal&)> talk = [](const Animal& animal) {
        animal.speak();
    };

    Dog dog;
    Cat cat;

    talk(dog); // 输出 "Woof!"
    talk(cat); // 输出 "Meow!"

    return 0;
}

```

### 7. 事件处理

```cpp
#include <iostream>
#include <functional>
#include <vector>

class Event {
public:
    using EventHandler = std::function<void()>;

    void addHandler(const EventHandler& handler) {
        handlers.push_back(handler);
    }

    void fire() {
        for (const auto& handler : handlers) {
            handler();
        }
    }

private:
    std::vector<EventHandler> handlers;
};

int main() {
    Event event;
    event.addHandler([]() { std::cout << "Event handler 1" << std::endl; });
    event.addHandler([]() { std::cout << "Event handler 2" << std::endl; });

    event.fire(); // 触发事件，调用注册的事件处理器

    return 0;
}
```

### 8. 回调函数

```cpp
#include <iostream>
#include <functional>
#include <thread>

void asyncOperation(std::function<void()> callback) {
    // 模拟异步操作
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 完成后调用回调函数
    callback();
}

int main() {
    asyncOperation([]() {
        std::cout << "Async operation completed." << std::endl;
    });

    // 在异步操作完成之前继续执行其他任务

    return 0;
}
```

### 9. 函数组合

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    std::function<int(int, int)> add_func = add;
    std::function<int(int, int)> subtract_func = subtract;

    std::function<int(int, int)> combined_func = [&](int x, int y) {
        return subtract_func(add_func(x, y), y);
    };

    int result = combined_func(5, 3);
    std::cout << "Result: " << result << std::endl; // 输出 "Result: 5"
    return 0;
}
```

### 10. 函数参数化

```cpp
#include <iostream>
#include <functional>

void performOperation(int a, int b, std::function<int(int, int)> operation) {
    int result = operation(a, b);
    std::cout << "Result: " << result << std::endl;
}

int main() {
    std::function<int(int, int)> add_func = [](int x, int y) { return x + y; };
    std::function<int(int, int)> multiply_func = [](int x, int y) { return x * y; };

    performOperation(5, 3, add_func); // 输出 "Result: 8"
    performOperation(5, 3, multiply_func); // 输出 "Result: 15"
    return 0;
}

```

### 11. 函数重载

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> int_add_func = add;
    std::function<double(double, double)> double_add_func = add;

    int result1 = int_add_func(5, 3);
    double result2 = double_add_func(2.5, 3.7);

    std::cout << "Result 1: " << result1 << std::endl; // 输出 "Result 1: 8"
    std::cout << "Result 2: " << result2 << std::endl; // 输出 "Result 2: 6.2"
    return 0;
}
```

### 4. 函数动态调用

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    std::function<int(int, int)> selected_func;

    bool use_addition = true;
    if (use_addition) {
        selected_func = add;
    } else {
        selected_func = subtract;
    }

    int result = selected_func(5, 3); // 动态选择要调用的函数
    std::cout << "Result: " << result << std::endl; // 输出 "Result: 8"
    return 0;
}
```

## 2. Lambda表达式

Lambda 表达式是 C++11 引入的一项重要特性，允许你在代码中定义匿名函数，这些函数可以像普通函数一样使用。Lambda 表达式通常用于创建临时的、局部的函数对象，以便更灵活地处理一些任务，例如函数传递、算法操作等。

### Lambda 表达式的基本语法

Lambda 表达式的基本语法如下：

```cpp
[capture_clause] (parameter_list) -> return_type {
    // Lambda 函数体
}
```

- `capture_clause`：捕获列表，用于指定在 Lambda 函数中可以访问的外部变量。捕获列表可以为空，也可以包含变量名，如 `[x, y]`，表示捕获变量 `x` 和 `y`。捕获列表还可以使用引用捕获（`[&x, y]`）或按值捕获（`[=]`）的方式。
- `parameter_list`：参数列表，与普通函数的参数列表类似，用于指定 Lambda 函数的参数。
- `return_type`：返回类型，用于指定 Lambda 函数的返回类型。如果省略，编译器会根据函数体的返回语句自动推断返回类型。
- Lambda 函数体：包含实际执行的代码。

### **Lambda 表达式作为函数对象**：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // 使用 Lambda 表达式作为排序函数
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;
    });

    // 使用 Lambda 表达式作为输出函数
    std::for_each(numbers.begin(), numbers.end(), [](int num) {
        std::cout << num << " ";
    });

    return 0;
}
```

在这个示例中，Lambda 表达式被用作排序函数和输出函数，用于对整数向量进行排序和输出。

### **Lambda 表达式与标准库算法**：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // 使用 Lambda 表达式和 std::count_if 统计大于 4 的元素个数
    int count = std::count_if(numbers.begin(), numbers.end(), [](int num) {
        return num > 4;
    });

    std::cout << "Count: " << count << std::endl;

    return 0;
}
```

在这个示例中，Lambda 表达式与 `std::count_if` 算法一起使用，用于统计大于 4 的元素个数。

### **Lambda 表达式作为回调函数**：

```cpp
#include <iostream>
#include <functional>

void performOperation(int a, int b, std::function<void(int, int)> operation) {
    operation(a, b);
}

int main() {
    performOperation(5, 3, [](int x, int y) {
        std::cout << "Sum: " << x + y << std::endl;
    });

    return 0;
}
```

在这个示例中，Lambda 表达式被传递给 `performOperation` 函数，用作回调函数，执行两个整数的求和操作。

### **Lambda 表达式与范围 `for` 循环**：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // 使用 Lambda 表达式和范围 for 循环遍历容器元素
    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}
```

这个示例展示了如何使用 Lambda 表达式和范围 `for` 循环来遍历容器中的元素并输出它们。

### Lambda 表达式捕获外部变量：

```cpp
#include <iostream>

int main() {
    int x = 5;

    auto lambda = [x]() {
        std::cout << "Captured variable x: " << x << std::endl;
    };

    lambda();

    return 0;
}
```



## 3. std::move

函数模板原型

```cpp
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }

```

1. `template<typename _Tp>`：这是一个函数模板声明，声明了一个名为 `_Tp` 的模板参数，表示 `move` 函数可以接受任意类型的参数。
2. `_GLIBCXX_NODISCARD`：这是一个宏，用于指示函数的返回值不应该被忽略。这意味着，调用 `std::move` 的返回值应该被使用，不应该被丢弃。
3. `constexpr`：这是一个关键字，表示 `move` 函数可以在编译时求值，这通常用于优化和静态分析。
4. `typename std::remove_reference<_Tp>::type&&`：这部分是 `move` 函数的返回类型。它使用 `std::remove_reference` 模板元函数来移除 `_Tp` 类型的引用，然后通过 `&&` 表示返回一个右值引用。
   - `std::remove_reference<_Tp>` 用于确定 `_Tp` 的非引用类型。
   - `typename` 告诉编译器后面的表达式是一个类型。
   - `&&` 表示返回一个右值引用。
5. `move(_Tp&& __t) noexcept`：这是 `move` 函数的函数签名和定义。
   - `move` 是函数的名称。
   - `_Tp&& __t` 是函数的参数，表示一个通用引用，可以接受左值或右值。
   - `noexcept` 表示函数不会引发异常。
6. `{ return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }`：这是 `move` 函数的实际实现。
   - `static_cast` 用于将参数 `__t` 强制转换为右值引用类型。
   - `typename std::remove_reference<_Tp>::type&&` 是要返回的类型，表示参数类型的非引用版本的右值引用。

## 4. std::forward

```cpp
/**
* Forward an lvalue.
* Returns

* The parameter cast to the specified type.
* This function is used to implement "perfect forwarding".
**/
template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    { return static_cast<_Tp&&>(__t); }

  /**
   *  @brief  Forward an rvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value,
	  "std::forward must not be used to convert an rvalue to an lvalue");
      return static_cast<_Tp&&>(__t);
    }
```

```cpp
#include <iostream>
#include <utility>

// 下游函数，用于处理参数
void process(int& i) {
    std::cout << "Lvalue reference: " << i << std::endl;
}

void process(int&& i) {
    std::cout << "Rvalue reference: " << i << std::endl;
}

// 完美转发函数模板
template <typename T>
void forward_example(T&& arg) {
    // 在这里使用 std::forward，完美转发参数给下游函数
    process(std::forward<T>(arg));
}

int main() {
    int x = 42;

    // 测试完美转发
    forward_example(x);        // 传递左值
    forward_example(100);      // 传递右值
    forward_example(std::move(x)); // 传递右值

    return 0;
}

```

## 5. 自动类型推导

### 1. auto

1. **基本用法**：

   - `auto`关键字通常与变量声明一起使用，编译器根据初始化表达式的类型来确定变量的类型。
   - 例如，`auto x = 42;`，编译器会自动将`x`的类型推断为整数(int)，因为初始化表达式是整数。

2. **容器迭代器的使用**：

   - `auto`常用于简化容器的迭代。例如，使用`auto`可以避免手动指定容器迭代器的类型。

   - ```cpp
     std::vector<int> numbers = {1, 2, 3, 4, 5};
     for (auto it = numbers.begin(); it != numbers.end(); ++it) {
         // 使用*it访问容器元素
         std::cout << *it << " ";
     }
     ```

   - 这种用法使代码更加简洁，无需担心容器元素的具体类型。

3. **与范围-based for 循环结合**：

   - `auto`与范围-based for 循环结合使用，使迭代更加方便。

   - ```cpp
     for (auto num : numbers) {
         std::cout << num << " ";
     }
     ```

   - 在这种情况下，`auto`自动推断`num`的类型为容器中元素的类型。

4. **模板编程和泛型编程**：

   - `auto`对于泛型编程非常有用，因为它允许编写更通用的代码，不需要提前知道变量的确切类型。
   - 在泛型函数或类中，使用`auto`可以处理不同类型的参数或数据。

### 2. decltype

1. **基本用法**：
   - `decltype` 用于获取表达式的类型，其语法为 `decltype(expression)`，其中 `expression` 是待获取类型的表达式。
   - 例如，如果有一个变量 `x`，你可以使用 `decltype(x)` 来获取 `x` 的类型，即使 `x` 还未被初始化。
2. **表达式类型推导**：
   - `decltype` 最常见的用途是在泛型函数或模板中，以便根据函数参数或表达式的类型进行编译时类型推导。
   - 例如，考虑一个泛型函数 `template<typename T, typename U> auto add(T a, U b) -> decltype(a + b) { return a + b; }`。这里的 `decltype(a + b)` 确保返回值的类型与 `a` 和 `b` 相加后的类型一致。
3. **引用和 cv 限定符的处理**：
   - `decltype` 会保留表达式的引用性质和 const/volatile 限定符。例如，`int x = 42; const int& y = x;`，`decltype(y)` 的类型将是 `const int&`。
4. **复杂表达式的类型获取**：
   - `decltype` 可以用于获取复杂表达式的类型，例如函数调用、成员访问、数组索引等。
   - 例如，`decltype(std::vector<int>().size())` 可以获取一个临时 `std::vector<int>` 对象的 `size()` 函数的返回类型。

### 3. 拖尾返回类型、auto 与 decltype 配合


拖尾返回类型（Trailing Return Type）结合 `auto` 和 `decltype` 是 C++11 引入的一项强大特性，它允许你在函数声明中使用 `auto` 和 `decltype` 来推断函数的返回类型。这在编写泛型函数、函数模板和复杂表达式的返回类型不确定时非常有用。

下面是关于拖尾返回类型、`auto` 和 `decltype` 配合使用的详解：

1. **拖尾返回类型的语法**：
   - 拖尾返回类型的语法是在函数声明时使用 `auto` 或 `decltype` 来指定返回类型，通常出现在函数参数列表后面的 `->` 后面。
   - 例如，`auto func(int x, double y) -> decltype(x + y) { return x + y; }` 中的 `-> decltype(x + y)` 指定了函数 `func` 的返回类型为 `x + y` 表达式的类型。
2. **用途示例**：
   - 拖尾返回类型与泛型编程结合使用非常有用，因为你可以在不知道具体参数类型的情况下推断返回类型。
   - 例如，一个计算数组元素之和的泛型函数可以这样定义：`template <typename T> auto sum(const T& arr) -> decltype(arr[0] + arr[0]) { /* 计算并返回和 */ }`。
3. **`auto` 和 `decltype` 结合**：
   - 拖尾返回类型通常与 `auto` 和 `decltype` 结合使用，以获取复杂表达式的返回类型。
   - 例如，`auto` 用于简化函数定义，而 `decltype` 用于获取表达式的返回类型。
   - `auto add(int x, double y) -> decltype(x + y) { return x + y; }`
4. **可读性与代码简化**：
   - 拖尾返回类型、`auto` 和 `decltype` 的使用可以提高代码的可读性和可维护性，因为它们允许你在函数声明中明确指定返回类型，而不必将类型信息放在函数体内

```cpp
`auto func(int x, double y) -> decltype(x + y) { return x + y; }` 
```

## 6. constexpr

constexpr是c++11新添加的特征，目的是将运算尽量放在编译阶段，而不是运行阶段。这个从字面上也好理解，const是常量的意思，也就是后面不会发生改变，因此当然可以将计算的过程放在编译过程。constexpr可以修饰函数、结构体。

## 7. 变量模板variable template

C++14 允许通过变量模板定义一族变量。

```cpp
template<typename T> // variable template
const T pi = T(3.14159265);

template<typename T> // function template
T circleArea(T r){
    return pi<T> * r * r; // variable template instantiation
}
```

## 8. 聚合初始化（aggregate initialization）

聚合初始化是 C++11 中列表初始化的一种形式。

首先，聚合体是下列类型之一：

- 数组类型
- 满足一下条件的类类型（常为struct）
  - 没有私有或受保护的非静态数据成员（在类中声明的非 `static` 数据成员）
  - 没有用户提供的构造函数
  - 没有虚成员函数

你可以像这样进行聚合初始化

```cpp
struct node{
    int a, b;
    int c[3];
    int d;
};
node nd = {2, 3, 5, 6, 3, 4};
```

这样初始化过后

```cpp
a = 2;
b = 3;
c = {5, 6, 3};
d = 4;
```

可以发现聚合初始化是按照地址顺序依次进行的，所以对于类中的数组成员可以很方便的进行初始化，当然这也意味着聚合初始化无法直接指定一些成员进行初始化。

> 在 C++20 中允许进行指派初始化器的聚合初始化，即可以指定成员进行初始化

另一个很重要的特性，聚合初始化是递归进行的，也就是说其允许嵌套

```cpp
struct A{
    struct B{
        int a;
        int b;
        int c;
    };
    B d;
    int e;
    vector<int> f;
};
```

这样一个结构体我们仍然可以使用聚合初始化

```cpp
A a = {{1, 2, 3}, 4, {5, 6}};
```

初始化结果如下

```cpp
d.a = 1;
d.b = 2;
d.c = 3;
e = 4;
f = {5, 6};
```

在 C++11 中，聚合初始化要求类成员没有默认初始化器（`int a = 10`），但在 C++14 中允许我们这么做，所以另外很重要的一点是，当聚合初始化与默认初始化器结合时，到底会产生怎么样的结果。

举个例子说明

```cpp
struct A {
    struct B {
        int a = 21;
        int b;
        int c = 22;
        int d;
        int e = 23;
    };
    B b1  = { 11, 12 };
    B b2  = { 11, 12, 13 };
    int x;
};
```

接下来进行聚合初始化

```cpp
A a = { { 1, 2, 3, 4 }, { 1 }, 5 };
```

你会得到这样的结果

```cpp
b1.a = 1;
b1.b = 2;
b1.c = 3;
b1.d = 4;
b1.e = 23;
b2.a = 1;
b2.b = 0;
b2.c = 22;
b2.d = 0;
b2.e = 23;
x = 5;
```

你会发现，`b2`的初始化好像失效了，否则我们应该得到这样的结果

```cpp
b2.a = 1;
b2.b = 12;
b2.c = 13;
b2.d = 0;
b2.e = 23;
```

初始化器提供的值比类成员少时，根据 N3605，C++14 会采用如下策略

- 从成员的默认初始化器进行初始化
- 如果没有默认初始化器，用一个空初始化器列表进行初始化

那么，我们在对 `a` 进行聚合初始化时， 实际上为 `b2` 提供了值 `{1}`，所以 `b2` 的初始化器**完全失效**，接下来，`b2.a` 从聚合初始化中的到了值，其他成员没有得到值，所以隐式的按照 N3605 进行初始化。

这正是我们得到的结果。

## 9. 基于范围的 for 循环（range-based for loop）

C++11 规定了基于范围的 `for` 循环，其在一个范围上执行 `for` 循环，是传统 `for` 循环一个更加可读的等价版本，OI 中常用于图遍历。

其语法如下

```cpp
[属性-可选]
for(范围声明: 范围表达式){
    循环语句
}
```

> 属性：属性说明符序列，不在 Blog 中进行说明，几乎不会用到。

- 范围声明：一个具名变量的声明，类型为范围表达式中元素的类型或其引用，一般使用 `auto` 对其类型进行推导。
- 范围表达式：一个序列（数组，或是定义了 `begin` 和 `end` 的对象，如 `vector`），或是一个花括号列表初始化器（如 `{1, 2, 3, 4, 5}`）。
- 循环语句：常规函数体。

基于范围的 `for` 循环可以用这样的常规 `for` 循环替代

```cpp
for(auto __begin = 首表达式, __end = 尾表达式; __begin != __end; __begin++){
    范围声明 = *__begin;
    循环语句
}
```

其中，对于数组 `a[]`，其首表达式为 `a`，尾表达式为 `(a + __bound)`，`__bound` 为数组长度，我们要求数组是有确定长度的。

对于定义了 `begin` 和 `end` 的对象 `b`，其首表达式为 `b.begin()`，尾表达式为 `b.end()`。

否则，通过实参依赖查找进行查找。

一些实际使用的例子

```cpp
vector<int> g[10005];
for(auto v: g[u]){
    /* something here */
}

int a[] = {1, 2, 3, 4, 5};
for(auto &x: a){
   	x++;
    std::cout << x << ' ';
}
// after - a: {2, 3, 4, 5, 6}

for(auto x: {1, 3, 5, 7}){
    std::cout << x << ' ';
}
```

## 10. 变参数模板（variadic template）

可变参数模板是C++11引入的一个功能，允许你编写可以接受任意数量和类型参数的通用模板函数或类模板。这个功能对于编写通用、灵活的代码非常有用。以下是可变参数模板的基本用法和示例：

```cpp
template <typename... Args>
void PrintArgs(Args... args) {
    int dummy[] = { (std::cout << args << " ", 0)... };
    std::cout << std::endl;
}

int main() {
    PrintArgs(1, 2, 3, "Hello", 4.5);
    return 0;
}
```

在上面的例子中，`PrintArgs` 是一个可变参数模板函数，它可以接受任意数量的参数。在函数体内，我们使用了折叠表达式 `(std::cout << args << " ", 0)...` 来处理参数，将参数打印到标准输出。`...(expression)` 表示展开参数包，`(expression)` 是对每个参数执行的操作。







## 11. 折叠表达式

C++11引入了折叠表达式（fold expression）的特性，它是一种语法形式，允许对参数包（parameter pack）中的参数执行操作，然后将结果整合成一个值。折叠表达式非常有用，可以用于编写更加通用、灵活的代码。以下是折叠表达式的详细解释：

### 折叠表达式的语法

折叠表达式的基本语法形式如下：

```
cppCopy code
(操作符 ... )
```

其中，操作符可以是二元操作符、逗号操作符等。折叠表达式分为两种类型：

1. **左折叠表达式（Left Fold Expression）**：操作符出现在左边。示例：`(操作符 ... 参数包)`。
2. **右折叠表达式（Right Fold Expression）**：操作符出现在右边。示例：`(参数包 ... 操作符)`。

### 折叠表达式的用途

折叠表达式通常用于对参数包中的每个参数执行相同的操作，然后将结果整合到一个值中。这对于各种编程任务非常有用，例如：

- 执行二元操作符，如求和、求积等。
- 实现可变参数的打印函数或格式化函数。
- 生成字符串，如将参数连接成一个字符串。

### 示例

以下是一些折叠表达式的示例，以便更好地理解它们的用法：

#### 示例1：求和

```cpp
template <typename... Args>
int Sum(Args... args) {
    return (args + ...); // 左折叠表达式，对参数包中的每个参数执行加法操作
}

int result = Sum(1, 2, 3, 4);
// result = (1 + 2) + (3 + 4) = 10
```

#### 示例2：打印参数

```cpp
template <typename... Args>
void PrintArgs(Args... args) {
    (std::cout << ... << args); // 左折叠表达式，将参数连接起来并输出
}

PrintArgs("Hello, ", 42, ", World!"); // 输出：Hello, 42, World!
```

#### 示例3：生成逗号分隔的字符串

```cpp
template <typename... Args>
std::string JoinArgs(Args... args) {
    return (std::to_string(args) + ... + ", "); // 左折叠表达式，生成逗号分隔的字符串
}

std::string result = JoinArgs(1, 2, 3, 4);
// result = "1, 2, 3, 4, "
```

#### 示例4：右折叠表达式

```cpp
template <typename... Args>
int Product(Args... args) {
    return (... * args); // 右折叠表达式，对参数包中的每个参数执行乘法操作
}

int result = Product(1, 2, 3, 4);
// result = 1 * (2 * (3 * 4)) = 24
```

折叠表达式可以帮助简化代码，特别是在处理可变数量参数的情况下，它们在元编程和泛型编程中非常有用。



## 12. 协程

### 协程的关键概念：

1. **协程函数**：一个协程函数是一个使用关键字`co_return`、`co_await`、`co_yield`等来定义的函数。它可以在执行过程中被暂停和恢复，而不会丢失其局部状态。
2. **协程的状态**：一个协程可以处于以下几种状态之一：
   - **暂停状态**：协程执行到某个暂停点时会被暂停，等待后续的操作。
   - **运行状态**：协程正在主动执行中。
   - **完成状态**：协程执行完毕，无法再继续执行。
3. **协程的 Promise 类型**：协程函数的返回值类型通常是协程的 Promise 类型，它定义了协程的行为和状态管理。Promise 类型必须包括一些特定函数，如`get_return_object`、`initial_suspend`、`final_suspend`等，用于协程的初始化、暂停和完成处理。

### 协程的基本语法：

#### 1. 定义协程函数：

```cpp
#include <coroutine>

// 协程的返回类型是协程的 Promise 类型
generator<int> generate_numbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i; // 使用 co_yield 生成值
    }
}
```

#### 2. 协程的 Promise 类型：

```cpp
struct generator {
    struct promise_type {
        // 初始化协程的 Promise 对象
        generator get_return_object() {
            return generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 协程启动时调用
        std::suspend_never initial_suspend() {
            return {};
        }

        // 协程暂停时调用
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        // 协程完成时调用
        std::suspend_always final_suspend() noexcept {
            return {};
        }

        // 错误处理
        void unhandled_exception() {
            std::terminate();
        }

        int current_value;
    };

    std::coroutine_handle<promise_type> coroutine;

    explicit generator(std::coroutine_handle<promise_type> coro) : coroutine(coro) {}

    ~generator() {
        if (coroutine) {
            coroutine.destroy();
        }
    }

    bool move_next() {
        if (!coroutine.done()) {
            coroutine.resume();
        }
        return !coroutine.done();
    }

    int current_value() {
        return coroutine.promise().current_value;
    }
};
```

#### 3. 使用协程：

```cpp
int main() {
    generator gen = generate_numbers(1, 5);

    while (gen.move_next()) {
        std::cout << gen.current_value() << " ";
    }

    return 0;
}
```

在这个例子中，`generate_numbers` 是一个协程函数，它生成了一个范围内的数字序列，并且在每次使用 `co_yield` 语句时暂停。我们还定义了协程的 Promise 类型，其中包括了初始化、暂停、完成和错误处理等函数。

在 `main` 函数中，我们创建了一个 `generator` 实例并使用 `move_next` 函数来逐个获取生成的值，然后输出到控制台。

### 协程的优点：

1. **可读性和可维护性**：协程可以使异步代码看起来更像同步代码，提高了代码的可读性和可维护性。
2. **避免回调地狱**：协程可以避免回调函数的嵌套，减少了回调地狱（Callback Hell）的问题。
3. **更自然的控制流**：协程提供了一种更自然的控制流方式，使得代码逻辑更清晰。
4. **高效的资源管理**：协程的 Promise 类型允许有效地管理协程的状态和资源。
