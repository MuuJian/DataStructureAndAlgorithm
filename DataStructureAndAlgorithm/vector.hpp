//
//  vector.hpp
//  Data-Structure-And-Algorithm
//
//  Created by mumu on 5/5/20.
//  Copyright © 2020年 mumu. All rights reserved.
//

#ifndef vector_h
#define vector_h


#include<iostream>
#include<initializer_list>


using std::cout;
using std::endl;
using std::initializer_list;


#define DEFAULT_CAPACITY 3
using Rank = std::size_t;


template <typename T>
class vector
{
protected:
	Rank _size; Rank _capacity; T* _elem;
	void CopyForm(T const* A, Rank lo, Rank hi); //复制数组区间
	void Expand(); //扩容
	void Shrink(); //压缩
	
	//排序
	void SelectSort();
	void BubbleSort();
	
	void Merge(Rank lo, Rank mi, Rank hi);
	void MergeSort(Rank lo, Rank hi);
	Rank Partition(Rank lo, Rank hi);
	void QuickSort(Rank lo, Rank hi);
	void HeapSort(Rank lo, Rank hi);
	
public:
	vector(Rank size = 0, T var = 0); //构造函数
	vector(const initializer_list<T>& list); //列表构造函数
	vector(const vector<T>& v); //复制构造
	vector<T>& operator=(const vector<T>& v); //拷贝运算符
	vector(vector<T>&& v) noexcept; //移动构造
	vector<T>& operator=(vector<T>&& v) noexcept; //移动赋值运算符
	~vector(); //析构
	T& operator[](Rank r) const; //下标访问
	
	
	T Remove(Rank r); //删除下标为r的元素
	int Remove(Rank lo, Rank hi); //删除区间
	void Insert(Rank r, T const& e); //插入
	void Insert(T const& e){return Insert(_size, e);} //末尾插入
	Rank Size() const; //规模
	bool Empty() const; //判断为空
	Rank Find(T const& e) const {return Find(e, 0, _size);} //无序查找
	Rank Find(T const& e, Rank lo, Rank hi) const; //无序区间查找
	void Unsort(); //乱序
	int Deduplicate(); //无序去重
	void Traverse(); //遍历
	int Uniquift(); //有序去重
	Rank Search(T const& e) const { return (0 >= _size) ? -1 : Search(e, 0, _size);} //有序查找
	Rank Search(T const& e, Rank lo, Rank hi) const; //有序区间查找
	
	
	void Sort(); //排序
};


template<typename T>
vector<T>::~vector()
{
	cout << "destroy" << endl;
	delete[] _elem;
}


template<typename T>
vector<T>::vector(Rank size, T var)
{
	cout << "constructor" << endl;
	_elem = new T[_capacity = size * 2];
	for(_size = 0; _size < size; ++_size)
	{
		_elem[_size] = var;
	}
}


template<typename T>
vector<T>::vector(const initializer_list<T>& list)
{
	cout << "list construcot" << endl;
	_elem = new T[_capacity = 2 * list.size()];
	_size = 0;
	for(T tmp : list)
	{
		_elem[_size++] = tmp;
	}
}


template<typename T>
vector<T>::vector(vector<T>&& v) noexcept : _elem(v._elem), _size(v._size), _capacity(v._capacity)
{
	cout << "move constructors" << endl;
	v._elem = nullptr;
	v._size = 0;
	v._capacity = 0;
}


template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept
{
	if(this != &v)
	{
		cout << "move assignments" << endl;

		delete[] _elem;
		_elem = v._elem;
		_size = v._size;
		_capacity = v._capacity;
		v._elem = nullptr;
		v._size = 0;
		v._capacity = 0;
	}
	return *this;
}


template<typename T>
vector<T>::vector(const vector<T>& v)
{
	cout << "copy constructor" << endl;
	CopyForm(v._elem, 0, v._size);
}


template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
	cout << "assignment operator" << endl;
	if(_elem) delete[] _elem;
	CopyForm(v._elem, 0, v.Size());
	return *this;
}


template<typename T>
void vector<T>::CopyForm(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while(lo < hi)
		_elem[_size++] = A[lo++];
}


template<typename T>
void vector<T>::Expand()
{
	if(_size < _capacity) return;
	if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* _oldelem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; ++i)
		_elem[i] = _oldelem[i];
	delete[] _oldelem;
}


template<typename T>
void vector<T>::Shrink()
{
	if(_capacity < DEFAULT_CAPACITY << 1) return;
	if(_size << 2 > _capacity) return;
	T* _oldelem = _elem;
	_elem = new T[_capacity >>= 1];
	for(int i = 0; i < _size; ++i)
		_elem[i] = _oldelem[i];
	delete[] _oldelem;
}


template<typename T>
void vector<T>::Unsort()
{
	for(Rank i = _size; i > 0; --i)
		std::swap(_elem[i - 1], _elem[rand() % i]);
}


template<typename T>
void vector<T>::Insert(Rank r, T const&e)
{
	if(r > _size) return;
	Expand();
	for(Rank i = _size; i > r; --i)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	++_size;
}


template<typename T>
int vector<T>::Remove(Rank lo, Rank hi)
{
	if(lo == hi) return 0;
	while(hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	Shrink();
	return static_cast<int>(hi - lo);
}


template<typename T>
T vector<T>::Remove(Rank r)
{
	T e = _elem[r];
	Remove(r, r + 1);
	return e;
}


template<typename T>
Rank vector<T>::Find(T const&e, Rank lo, Rank hi) const
{
	while(lo < hi && e != _elem[lo])
	{
		++lo;
	}
	return lo;
}


template<typename T>
Rank vector<T>::Search(T const&e, Rank lo, Rank hi) const
{
	while(lo < hi)
	{
		Rank mi = lo + (hi - lo) / 2;
		if(e < _elem[mi])
			hi = mi;
		else if(e > _elem[mi])
			lo = mi + 1;
		else
			return mi;
	}
	return -1;
}


template<typename T>
Rank vector<T>::Size() const
{
	return _size;
}


template<typename T>
int vector<T>::Deduplicate()
{
	Rank oldsize = _size;
	Rank i  = 1;
	while(i < _size)
	{
		Find(_elem[i], 0, i) ? ++i : Remove(i);
	}
	return static_cast<int>(oldsize - _size);
}


template<typename T>
int vector<T>::Uniquift()
{
	Rank i = 0, j = 0;
	while(++j < _size)
	{
		if(_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i; Shrink();
	return j - i;
}


template<typename T>
T& vector<T>::operator[](Rank r) const
{
	return _elem[r];
}


template<typename T>
bool vector<T>::Empty() const
{
	return _size == 0 ? true : false;
}


template<typename T>
class Print
{
public:
	void operator()(T& var)
	{
		cout << var << " ";
	}
};


template <typename T>
void vector<T>::Traverse ()
{
	if(!Empty())
	{
		for ( int i = 0; i < _size; i++ )
			Print<T>()(_elem[i]);
		cout << endl;
	}
	else
	{
		cout << "Empty" << endl;
	}
}


template<typename T>
void vector<T>::Sort()
{
	switch(rand() % 2)
	{
		case 1:
			SelectSort();
			break;
		case 2:
			BubbleSort();
			break;
	}

}

template<typename T>
void vector<T>::SelectSort()
{
	Rank min = 0;
	for(Rank i = 0; i < _size; ++i)
	{
		min = i;
		for(Rank j = i + 1; j < _size; ++j)
		{
			if(_elem[min] > _elem[j])
				min = j;
		}
		std::swap(_elem[i], _elem[min]);
	}
}


template<typename T>
void vector<T>::BubbleSort()
{
	for(Rank i = 0; i < _size; ++i)
	{
		bool sorted = true;
		for(Rank j = i + 1; j < _size; ++j)
		{
			if(_elem[j] < _elem[i])
			{
				sorted = false;
				std::swap(_elem[j], _elem[i]);
			}
		}
		if(sorted == true)
			return;
	}
}

#endif /* vector_hpp */
