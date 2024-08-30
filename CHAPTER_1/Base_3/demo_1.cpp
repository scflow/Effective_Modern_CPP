// CHAPTER 1 Deducing Types
// 数组指针

#include <iostream>


int main()
{
    int array[5] = {0, 0, 0, 0, 0};
    int *ptr = array;
    int (*ptr2)[5] = { };
    return 0;
}