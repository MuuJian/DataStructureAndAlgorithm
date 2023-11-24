//
//  Header.h
//  DataStructureAndAlgorithm
//
//  Created by mumu on 30/11/2020.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

#define DEFAULTcapacity_ 3

using std::cout;
using std::endl;
using std::initializer_list;
using std::srand;
using std::rand;
using std::time;
using std::swap;
using std::vector;
using std::string;

using size_type = std::size_t;

template<typename T>
class Print
{
public:
	void operator()(T& var) const
	{
		cout << var << " ";
	}
    
    ~Print()
    {
        cout << endl;
    }
};

#endif /* Header_h */
