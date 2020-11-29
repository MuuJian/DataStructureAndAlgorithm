//
//  main.cpp
//  DataStructureAndAlgorithm
//
//  Created by mumu on 29/11/2020.
//

#include <iostream>
#include "vector.hpp"
using std::cout;

int main()
{
	vector<int> num; //constructor
	vector<int> num2{1,2,3,4,5}; //list constructor
	num = num2; //assignment operator
	vector<int> num3 = num2; //copy constructor
	num3 = {1,2,3};//move operator  list constructor
	vector<int> num4 = std::move(num3);//move constructor
	num2.Insert(5,6);
	num2.Traverse();
	num2.Remove(3,4);
	num2.Traverse();
	cout << num2.Find(5) << endl;
	vector<int> num5{5,5,5,5,5,1,2,3,4,5,12,2,4,5,6,7,9};
	num5.Deduplicate();
	num5.Traverse();
	cout << num2.Search(3) << endl;
	num5.Sort();
	num5.Traverse();

}
