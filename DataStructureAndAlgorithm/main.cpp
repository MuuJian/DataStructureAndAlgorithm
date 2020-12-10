//
//  main.cpp
//  DataStructureAndAlgorithm
//
//  Created by mumu on 29/11/2020.
//

#include <iostream>
#include "header.hpp"
#include "list.hpp"
#include "vector.hpp"

int main()
{
	List<int> l{1,2,3,4,5,6,7,8};
	l.Traverse();
	l.Reverse();
	l.Traverse();
	return 0;

}
