#include<iostream>
#include<vector>
using std::cout;
using std::endl;

template<class T, class U>
decltype(*(T*)(0) * *(U*)(0)) mul(T x, U y)
{
    return x * y;
}

int main()
{
    cout << mul(1, 2);
}

