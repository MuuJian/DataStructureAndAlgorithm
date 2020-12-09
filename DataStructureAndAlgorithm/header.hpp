//
//  Header.h
//  DataStructureAndAlgorithm
//
//  Created by mumu on 30/11/2020.
//

#ifndef Header_h
#define Header_h

#include<iostream>
#include<initializer_list>

using std::cout;
using std::endl;
using std::initializer_list;
using std::srand;
using std::rand;
using std::time;
using std::swap;

using Rank = std::size_t;

#define DEFAULTcapacity_ 3

template<typename T>
class Print
{
public:
	void operator()(T& var)
	{
		cout << var << " ";
	}
};



#endif /* Header_h */
