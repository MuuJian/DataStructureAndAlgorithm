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
	vector<int> num5{5,5,5,5,5,1,2,3,4,5,8,2,4,5,6,7,9};

	num5.Deduplicate();
	num5.Traverse();
	num5.Sort();
	num5.Traverse();


	return 0;

}
