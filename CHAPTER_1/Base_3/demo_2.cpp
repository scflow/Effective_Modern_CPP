// CHAPTER 1 Deducing Types
// 函数指针

#include <iostream>
#include <string>


bool lengthCompare(const std::string &, const std::string &) //比较两个string对象的长度
{
    return false;
}

std::string::size_type sumLength(const std::string &str1, const std::string &str2)
{
    return str1.size() + str2.size();
}

bool cstringCompare(const char*, const char*)
{
    return false;
}

void ff(int*)
{

}

void ff(unsigned int)
{

}

int main()
{
    bool (*pf) (const std::string &, const std::string &);
    pf = lengthCompare;             // pf指向名为lengthCompare的函数
    pf = &lengthCompare;            // 等价的赋值语句；取地址符是可选的

    // 下面三个是等价的
    bool b1 = pf("hello", "goodbye");
    bool b2 = (*pf)("hello", "goodbye");
    bool b3 = lengthCompare("hello", "goodbye");

    pf = 0;
    // pf = sumLength;              // 错误: 返回类型不匹配
    // pf = cstringCompare;         // 错误: 形参类型不匹配

    void (*pf1)(unsigned int) = ff; // pf1指向void ff(unsigned int)
    // void (*pf2)(int) = ff;       // 错误: 没有任何一个ff与该形参列表匹配
    // double (*pf3)(int*) = ff;    // 错误: ff和pf3的返回类型不匹配

    void useBigger(const std::string &s1, const std::string &s2,
                   bool (*pf) (const std::string &, const std::string &));

    typedef bool Func(const std::string &, const std::string &);
    typedef decltype(lengthCompare) Func2;          // 等价类型

    // 返回指向函数的指针
    using F = int(int*, int);               // F是函数类型，不是指针
    using PF = int(*)(int*, int);           // PF是指针类型

    PF f1(int);
    // F f2(int);

    return 0;
}
