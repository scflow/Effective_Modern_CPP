// 条款三：理解decltype
// Item 3: Understand decltype
// 参考链接: https://cntransgroup.github.io/EffectiveModernCppChinese/1.DeducingTypes/item3.html

#include <iostream>
#include <deque>

const int i = 0;                //decltype(i)是const int

class Widget
{

};

bool f(const Widget& w)
{
    return false;
}        //decltype(w)是const Widget&
                                //decltype(f)是bool(const Widget&)

struct Point{
    int x,y;                    //decltype(Point::x)是int
};                              //decltype(Point::y)是int


template<typename T>            //std::vector的简化版本
class vector{
public:
    T& operator[](std::size_t index){};
};

template<typename Container, typename Index>    //可以工作，
auto authAndAccess(Container& c, Index i)       //但是需要改良
    ->decltype(c[i])
{
    authenticateUser();
    return c[i];
}

template<typename Container, typename Index>    //C++14版本，
decltype(auto)                                  //可以工作，
authAndAccess1(Container& c, Index i)            //但是还需要
{                                               //改良
    authenticateUser();
    return c[i];
}


int main()
{
    Widget w;                       //decltype(w)是Widget
    if(f(w))                      //decltype(f(w))是bool
    vector<int> v;                  //decltype(v)是vector<int>
    // v[0] = 0;
    // if(v[0] == 0)                //decltype(v[0])是int&
    std::deque<int> d;
    // authAndAccess1(d, 5) = 10;               //认证用户，返回d[5]，
                                        //然后把10赋值给它
                                        //无法通过编译器！

    return 0;
}