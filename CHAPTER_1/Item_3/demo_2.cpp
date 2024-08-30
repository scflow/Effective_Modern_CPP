// 条款三：理解decltype
// 类型处理
// 参考链接: https://blog.csdn.net/u014609638/article/details/107052539

#include <iostream>


// 声明了一个函数类型
using FuncType = int(int &, int);
// typedef int FuncType(int &, int);
// using PFuncType = int (*)(int &, int);
typedef int (*PFuncType)(int &, int);

// 下面的函数就是上面的类型
int add_to(int &des, int ori) {
    return des += ori;
}
int minus_to(int &des, int ori) {
    return des -= ori;
}
int multiply_to(int &des, int ori) {
    return des *= ori;
}
int divide_to(int &res, int ori) {
    return res /= ori;
}

int main() 
{
    // 注意：decltype和auto不会自动的获得函数指针类型，都需要添加*。
    FuncType *pf0 = add_to;
    auto *pf1 = minus_to;
    decltype(multiply_to) *pf2 = multiply_to;
    PFuncType pf3 = divide_to;

    int a = 4;

    // 通过函数指针调用
    std::cout << "pf0(a, 2): " << pf0(a, 2) << std::endl;  // 6
    std::cout << "pf1(a, 3): " << pf1(a, 3) << std::endl;  // 3
    std::cout << "pf2(a, 4): " << pf2(a, 4) << std::endl;  // 12
    std::cout << "pf3(a, 3): " << pf3(a, 3) << std::endl;  // 4
}
