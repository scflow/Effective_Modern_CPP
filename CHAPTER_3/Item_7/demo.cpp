#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <atomic>

class Widget
{
    public:
        Widget()
        {
            std::cout<<"Widget() init"<<std::endl;
        };
        Widget(int i)
        {
            std::cout<<"Widget(int i) init"<<std::endl;
        };
        Widget(int i, bool b) //构造函数未声明
        {
            std::cout<<"Widget(int i, bool b) init"<<std::endl;
        };     
        // Widget(int i, double d)//std::initializer_list这个形参 
        // {
        //     std::cout<<"Widget(int i, double d) init"<<std::endl;
        // };   
        // Widget(std::initializer_list<long double> il)  //新添加的
        // {
        //     std::cout<<"Widget(std::initializer_list<long double> il) init"<<std::endl;
        // };    
        operator float() const//转换为float
        {

        };
        Widget(std::initializer_list<bool> il)   //现在元素类型为bool   
        {
            std::cout<<"Widget(std::initializer_list<bool> il)"<<std::endl;
        };                            
    private:
        int x{ 0 };                 //没问题，x初始值为0
        int y = 0;                  //也可以
        //int z(0);                   //错误！
};


int main()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    /*不可拷贝的对象（例如std::atomic——见Item40）可以使用花括号初始化或者圆括号初始化，但是不能使用"="初始化*/
    std::atomic<int> ai1{ 0 };      //没问题
    std::atomic<int> ai2(0);        //没问题
    //std::atomic<int> ai3 = 0;       //错误！

    Widget w1;              //调用默认构造函数

    Widget w2 = w1;         //不是赋值运算，调用拷贝构造函数

    w1 = w2;                //是赋值运算，调用拷贝赋值运算符（copy operator=）

    int x(0);               //使用圆括号初始化
    int y = 0;              //使用"="初始化
    int z = { 0 };             //使用花括号初始化

    std::vector<int> v{ 1, 3, 5 };  //v初始内容为1,3,5

    /*括号表达式还有一个少见的特性，即它不允许内置类型间隐式的变窄转换（narrowing conversion）。
    如果一个使用了括号初始化的表达式的值，不能保证由被初始化的对象的类型来表示，代码就不会通过编译*/
    /*narrowing conversion of '((x1 + y1) + z1)' from 'double' to 'int' inside { } [-Wnarrowing]*/
    double x1, y1, z1;
    x1 = 1;
    y1 = 2;
    z1 = 3;
    //int sum1{ x1 + y1 + z1 };          //错误！double的和可能不能表示为int

    /*使用圆括号和"="的初始化不检查是否转换为变窄转换，因为由于历史遗留问题它们必须要兼容老旧代码*/
    int sum2(x + y +z);             //可以（表达式的值被截为int）
    int sum3 = x + y + z;           //同上

    Widget w11(10);                  //使用实参10调用Widget的一个构造函数
    // Widget w12();                    //最令人头疼的解析！声明一个函数w2，返回Widget
    Widget w13{};                    //调用没有参数的构造函数构造对象


    Widget w21(10, true);            //调用第一个构造函数
    // Widget w22{10, true};            //也调用第一个构造函数
    // Widget w23(10, 5.0);             //调用第二个构造函数
    // Widget w24{10, 5.0};             //也调用第二个构造函数

    Widget w31(10, true);    //使用圆括号初始化，同之前一样
                        //调用第一个构造函数

    // Widget w32{10, true};    //使用花括号初始化，但是现在
                            //调用带std::initializer_list的构造函数
                            //(10 和 true 转化为long double)

    // Widget w33(10, 5.0);     //使用圆括号初始化，同之前一样
                            //调用第二个构造函数 

    // Widget w34{10, 5.0};     //使用花括号初始化，但是现在
                            //调用带std::initializer_list的构造函数
                            //(10 和 5.0 转化为long double)

    std::cout << "当前时间是: " << std::asctime(now_tm);
    std::cout<<"Item 7"<<std::endl;
    return 0;
}
