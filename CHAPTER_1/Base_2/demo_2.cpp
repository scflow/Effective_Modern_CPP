// CHAPTER 1 Deducing Types
// 详解 C++ 左值、右值、左值引用以及右值引用
// 参考链接: https://blog.csdn.net/m0_59938453/article/details/125858335

#include <iostream>
#include <string>


// 3.完美转发（Perfect forwarding）
// 确定类型的 && 表示右值引用（比如：int&& ，string&&）
// 但函数模板中的 && 不表示右值引用，而是万能引用，模板类型必须通过推断才能确定，
//      其接收左值后会被推导为左值引用，接收右值后会被推导为右值引用。
template<typename T>
class A
{
	void func(T&& t){};  // 模板实例化时T的类型已经确定，调用函数时T是一个确定类型，所以这里是右值引用
};

template<typename T>
void f(T&& t)  // 万能引用
{
	//...
}

template<typename T>
void f1(T&& t)  // 万能引用
{
	Func(t);  // 根据参数t的类型去匹配合适的重载函数
}

template<typename T>
void PerfectForward(T&& t)  // 万能引用
{
	Func(std::forward<T>(t));  // 根据参数t的类型去匹配合适的重载函数
}

std::string to_string(int value)
{
    std::string str;
    while(value)
    {
        int val = value % 10;
        str += ('0' + val);
        value /= 10;
    }
    reverse(str.begin(), str.end());

    return str;
}

void Func(int& x) 
{	
    std::cout << "左值引用" << std::endl; 
}

void Func(const int& x) 
{ 
    std::cout << "const左值引用" << std::endl; 
}

void Func(int&& x) 
{ 
    std::cout << "右值引用" << std::endl; 
}

void Func(const int&& x) 
{ 
    std::cout << "const右值引用" << std::endl; 
}

int main()
{
	int a = 5;  // 左值
	f(a);  // 传参后万能引用被推导为左值引用

	const std::string s("hello");  // const左值
	f(s);  // 传参后万能引用被推导为const左值引用

	f(to_string(1234));  // to_string函数会返回一个string临时对象，是右值，传参后万能引用被推导为右值引用
	
	const double d = 1.1;
	f(std::move(d));  // const左值被move后变成const右值，传参后万能引用被推导为const右值引用


    int a1 = 4;  // 左值
	f1(a1);

	const int b1 = 8;  // const左值
	f1(b1);

	// 实际运行结果
	// f1(10);				// 左值引用
	// f1(std::move(c));	// const左值引用
	// 具体解释：右值引用失去了右值的属性
	//	f(10);
	// 		10是右值，传参后万能引用被推导为右值引用，但该右值引用变量其实是左值，
	// 				因此实际调用的函数是void Func(int& x)。
	//	f(std::move(c));
	// 		const左值被move后变成const右值，传参后万能引用被推导为const右值引用，
	// 		但该const右值引用变量其实是const左值，因此实际调用的函数是void Func(const int& x)。
	f1(10); // 10是右值

	const int c = 13;
	f1(std::move(c));  // const左值被move后变成const右值


	// 实现完美转发需要用到万能引用和 std::forward
	int a2 = 4;  // 左值
	PerfectForward(a2);

	const int b2 = 8;  // const左值
	PerfectForward(b2);

	PerfectForward(10); // 10是右值

	const int c2 = 13;
	PerfectForward(std::move(c2));  // const左值被move后变成const右值


	return 0;
}
