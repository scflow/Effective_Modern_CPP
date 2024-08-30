// CHAPTER 1 Deducing Types
// 顶层const 和 底层const
// 参考资料 《C++ Primer》2.4.3 顶层const

#include <iostream>

int main()
{
    int i = 0, j = 1;
    int *const p1 = &i;         // 不能改变p1的值，这是一个顶层const
    // p1 = &j;                 // 错误: p1 顶层const，无法改变p1的值
    i = 1;                      // i的值允许改变
    const int ci = 42;          // 不能改变ci的值，这是一个顶层const
    // ci++;                    // 错误: 表达式必须是可修改的左值
    const int *p2 = &ci;        // 允许改变p2的值，这是一个底层const
    p2 = &i;                    // 可以修改
    p2 = &ci;                   // 可以修改


    const int *const p3 = p2;   // 靠右的const是顶层const， 靠左的是底层const
    const int &r = ci;          // 用于声明引用的const都是底层const

    // 当执行对象的拷贝操作时，常量是顶层const还是底层const区别明显。其中，顶层const不受什么影响
    i= ci;                      // 正确: 拷贝ci的值，ci是一个顶层const，对此操作无影响
    p2 = p3;                    // 正确: p2和p3指向的对象类型相同，p3顶层const的部分不影响

    // 当执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层const资格，
    //      或者两个对象的数据类型必须能够转换。一般来说，非常量可以转换成常量，反之则不行
    // int *p = p3;             // 错误: "const int *" 类型的值不能用于初始化 "int *" 类型的实体
    // int &r1 = ci;            // 将 "int &" 类型的引用绑定到 "const int" 类型的初始值设定项时，限定符被丢弃
    const int &r2 = i;          // 正确: const int&可以绑定到一个普通int上
    std::cout << "p2: " << p2 << std::endl;
    return 0;
}