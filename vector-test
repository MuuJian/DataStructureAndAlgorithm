#include<iostream>
#include<string>
#include"vector.hpp"
using std::cout;
using std::endl;


int main()
{
    Vector<int> num; //constructor
    Vector<int> num2{1,2,3,4,5}; //list constructor
    num = num2; //assignment operator
    Vector<int> num3 = num2; //copy constructor
    num3 = {1,2,3};//move operator  list constructor
    Vector<int> num4 = std::move(num3);//move constructor
    num2.Insert(5,6);
    num2.Traverse();
    cout << num2.Find(5) << endl;
    cout << num2.Search(3) << endl;
    Vector<int> num5{5,5,5,5,5,1,2,3,4,5,8,2,4,5,6,7,9};
    num5.Deduplicate();
    num5.Traverse();
    num5.Sort();
    num5.Traverse();


}
