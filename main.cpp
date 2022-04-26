#include<iostream>
#include<string>
#include"list.hpp"
using std::cout;
using std::endl;

class Test
{
public:
    int* i = new int();
    Test() {}
    const Test& operator()() const
    {
        return *this;
    }
    explicit Test(const Test& test)
    {
        this -> i = test.i;
    }

};

int main()
{
    
    Test c;
    *(c.i) = 1;
    Test b(c());
    cout << *(b.i) << *(c.i) << endl;
    

}
