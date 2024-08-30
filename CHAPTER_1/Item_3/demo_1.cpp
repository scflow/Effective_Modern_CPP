// 条款三：理解decltype
// 函数指针
// 参考链接: https://blog.csdn.net/u014609638/article/details/107052539

#include <iostream>
bool shorter(const std::string &, const std::string &);
bool (*pf)(const std::string &, const std::string &) = shorter;

void callCompare(bool pf(const std::string &, const std::string &), int count);

// bool (*)(const std::string &, const std::string &) retFunc(int);
// [    bool (*)(const std::string &, const std::string &)  ] // 返回值 函数指针
// [    retFunc                                             ] // 函数名
// [    (int)                                               ] // 参数 int
// 错误
bool (*retFunc(int))(const std::string &, const std::string &);
// 必须把指针*放在retFunc的左边。
// ①从标识符开始，向右看到了参数列表，因此retFunc是一个函数。
// ②右括号，不能向右了，向左，看到了指针*，因此返回的是一个指针。
// ③看到左括号，向外，继续向右，看到参数列表，因此返回的是函数指针。
// ④再向左，看到了bool，可以确定了返回的函数指针的类型。

int main()
{
    pf("hello", "goodbye");
    (*pf)("hello", "goodbye");
    callCompare(shorter, 1);
    return 0;
}

bool shorter(const std::string &, const std::string &)
{
    std::cout << "bool shorter(const std::__cxx11::string &, const std::__cxx11::string &)" << std::endl;
    return false;
}

void callCompare(bool pf(const std::string &, const std::string &), int count)
{
    std::cout << "void callCompare(bool (*pf)(const std::__cxx11::string &, const std::__cxx11::string &), int count)" << std::endl;
}
bool (*retFunc(int))(const std::string &, const std::string &)
{
    std::cout << "bool (*retFunc(int))(const std::string &, const std::string &)" << std::endl;
    return false;
}