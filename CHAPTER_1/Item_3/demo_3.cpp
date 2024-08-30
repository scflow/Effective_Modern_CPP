// 条款三：理解decltype
// 【深度C++】之“decltype”
//  参考链接: https://blog.csdn.net/u014609638/article/details/106987131?ops_request_misc=%257B%2522request%255Fid%2522%253A%25226023D434-13CF-40D3-A9A3-1A86BEFD28F6%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=6023D434-13CF-40D3-A9A3-1A86BEFD28F6&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~hot_rank-1-106987131-null-null.142^v100^pc_search_result_base5&utm_term=decltype&spm=1018.2226.3001.4187

#include <iostream>

// 1.工作原理
// 2.decltype + 变量 var
// 3.decltype + 表达式 expr
// 4.decltype + 函数名 func_name

// 声明了一个函数类型
using FuncType = int(int &, int);

// 下面的函数就是上面的类型
int add_to(int &des, int ori)
{
    return 0;
}

int main()
{
    // 1. 工作原理
    //  decltype并不会实际计算表达式的值，编译器分析表达式并得到它的类型。
    //  函数调用也算一种表达式，因此不必担心在使用decltype时真正的执行了函数，正如前例中的f()。


    // 2. decltype + 变量
    //  ①当使用decltype(var)的形式时，decltype会直接返回变量的类型（包括顶层const和引用），不会返回变量作为表达式的类型。
    const int ci = 0, &cj = ci;
    // x的类型是const int
    decltype(ci) x = 0;
    // y的类型是const int &
    decltype(cj) y = x;
    // decltype加数组，不负责把数组转换成对应的指针，所以其结果仍然是个数组
    int array1[10];
    decltype(array1) array2;


    // 3. decltype + 表达式
    // ②当使用decltype(expr)的形式时，decltype会返回表达式结果对应的类型。
    // decltype(expr)的结果根据expr的结果不同而不同：
    //      expr返回左值，得到该类型的左值引用；expr返回右值，得到该类型。
    int i = 42, *p = &i, &r = i;
    // r + 0是一个表达式
    // 算术表达式返回右值
    // b是一个int类型
    decltype(r + 0) b;
    // c是一个int &
    // 解引用运算符*作用于指针类型，得到了p指向的对象的左值（*p = 2很正确），
    //      p是指向int的指针，因此decltype(*p)得到的类型是int &
    decltype(*p) c = i;
    // 但是decltype单独作用于对象，没有使用对象的表达式的属性，而是直接获得了变量的类型。
    // 要想获得变量作为表达式的类型，可以加一个括号
    decltype((i)) ri = i;
    decltype((p)) temp = p;
    // decltype作用的是表达式，(p)得到的是p的左值，所以temp一定是一个引用；
    //      p是指向int类型的指针，因此decltype得到的是指向int类型的指针的引用。


    // 4. decltype + 函数
    // C++中通过函数的返回值和形参列表，定义了一种名为函数类型的东西。它的作用主要是为了定义函数指针。
    // 声明了一个FuncType类型的指针
    // 并使用函数add_to初始化
    FuncType *pf = add_to;
    int a = 4;
    // 通过函数指针调用add_to
    pf(a, 2);
    decltype(add_to) *pf1 = add_to;
    pf1(a, 2);


    // 5. 总结
    // decltype是为了解决复杂的类型声明而使用的关键字，称作decltype类型说明符。
    // decltype可以作用于变量、表达式及函数名。①作用于变量直接得到变量的类型；
    //      ②作用于表达式，结果是左值的表达式得到类型的引用，结果是右值的表达式得到类型；③作用于函数名会得到函数类型，不会自动转换成指针。
    // decltype不会去真的求解表达式的值，可以放心使用。

    std::cout << "Finish" << std::endl;
    return 0;
}