// CHAPTER 1 Deducing Types
// 详解 C++ 左值、右值、左值引用以及右值引用
// 参考链接: https://blog.csdn.net/m0_59938453/article/details/125858335

#include <iostream>
#include <vector>


int main()
{
    // 一、左值和右值
    // 1.左值 左值是一个表示数据的表达式
    // 以下的a、p、*p、b都是左值
    int a = 3;
    int* p = &a;
    *p;
    const int b = 2;

    // 2.右值 不可以取地址的对象就是右值
    double x = 1.3, y = 3.8;
    // 以下几个都是常见的右值
    10;                 // 字面常量
    // x + y;           // 表达式返回值，不报错，但是有警告，所以注释了
    fmin(x, y);        // 传值返回函数的返回值


    // 二、左值引用和右值引用
    // 1.左值引用 左值引用就是对左值的引用，给左值取别名。
    // 以下几个是对上面左值的左值引用
    int& ra = a;
    int*& rp = p;
    int& r = *p;
    const int& rb = b;

    // 2.右值引用 右值引用就是对右值的引用，给右值取别名。
    // 以下几个是对上面右值的右值引用
    int&& rr1 = 10;
    // 右值引用变量其实是左值，可以对它取地址和赋值（const右值引用变量可以取地址但不可以赋值，因为 const 在起作用）。
    //      当然，取地址是指取变量空间的地址（右值是不能取地址的）。
    rr1 += 1;
    double&& rr2 = x + y;
    double&& rr3 = fmin(x, y);

    // 3.对比与总结
    // 左值引用总结：
    // 左值引用只能引用左值，不能直接引用右值。但是const左值引用既可以引用左值，也可以引用右值。

    // 1.左值引用只能引用左值
    int t = 8;
    int& rt1 = t;

    // int& rt2 = 8;  // 编译报错，因为8是右值，不能直接引用右值


    // 2.但是const左值引用既可以引用左值
    const int& rt3 = t;

    const int& rt4 = 8;  // 也可以引用右值
    const double& r1 = x + y;
    const double& r2 = fmin(x, y);
    // C++98标准中相关接口const左值引用引用右值的例子
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // 右值引用总结：
    // 右值引用只能引用右值，不能直接引用左值。但是右值引用可以引用被move的左值。
    // move，本文指std::move（C++11），作用是将一个左值强制转化为右值，以实现移动语义。
    //      左值被 move 后变为右值，于是右值引用可以引用。
    // 1.右值引用只能引用右值
    int&& rr4 = 10;
    double&& rr5 = x + y;
    const double&& rr6 = x + y;

    int t1 = 10;
    //int&& rrt = t;  // 编译报错，不能直接引用左值


    // 2.但是右值引用可以引用被move的左值
    int&& rrt = std::move(t);
    int*&& rr7 = std::move(p);
    int&& rr8 = std::move(*p);
    const int&& rr9 = std::move(b);

    return 0;
}