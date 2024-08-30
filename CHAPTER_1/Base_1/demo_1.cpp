/*CHAPTER 1 Deducing Types*/
/*顶层const 和 底层const*/

#include <iostream>

int main()
{
    const int a = 10;
    int b = a;


    /*"const int *" 类型的值不能用于初始化 "int *const" 类型的实体*/
    const int *const p = new int(10);

    // int *p1 = p;
    // int*  const p2 = p;
    const int* p3 = p;

    //int *p4 = &p;

    //const int* r1 = 20;
    //int &r2 = a;
    //int &r3 = r1;

    return 0;
}