//
//  vector.hpp
//  Data-Structure-And-Algorithm
//
//  Created by mumu on 5/5/20.
//  Copyright © 2020年 mumu. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include "header.hpp"

template <typename T>
class vector
{
private:
	Rank size_; Rank capacity_; T* elem_;
	void CopyForm(T const* A, Rank lo, Rank hi); //复制数组区间
	void Expand(); //扩容
	void Shrink(); //压缩
	
	//排序
	void SelectSort();
	void BubbleSort();
	void InsertionSort();
	
	/*
	void Merge(Rank lo, Rank mi, Rank hi);
	void MergeSort(Rank lo, Rank hi);
	Rank Partition(Rank lo, Rank hi);
	void QuickSort(Rank lo, Rank hi);
	void HeapSort(Rank lo, Rank hi);
	*/
	
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
	void Insert(Rank r, const T& e); //插入
	void Insert(const T& e){return Insert(size_, e);} //末尾插入
	Rank Size() const; //规模
	bool Empty() const; //判断为空
	Rank Find(const T& e) const {return Find(e, 0, size_);} //无序查找
	Rank Find(const T& e, Rank lo, Rank hi) const; //无序区间查找
	void Unsort(); //乱序
	int Deduplicate(); //无序去重
	void Traverse(); //遍历
	int Uniquift(); //有序去重
	Rank Search(const T& e) const { return (0 >= size_) ? -1 : Search(e, 0, size_);} //有序查找
	Rank Search(const T& e, Rank lo, Rank hi) const; //有序区间查找
	
	
	void Sort(); //排序
};


template<typename T>
vector<T>::~vector()
{
	cout << "destroy" << endl;
	delete[] elem_;
}


template<typename T>
vector<T>::vector(Rank size, T var)
{
	cout << "constructor" << endl;
	elem_ = new T[capacity_ = size * 2];
	for(size_ = 0; size_ < size; ++size_)
	{
		elem_[size_] = var;
	}
}


template<typename T>
vector<T>::vector(const initializer_list<T>& list)
{
	cout << "list construcot" << endl;
	elem_ = new T[capacity_ = 2 * list.size()];
	size_ = 0;
	for(T tmp : list)
	{
		elem_[size_++] = tmp;
	}
}


template<typename T>
vector<T>::vector(vector<T>&& v) noexcept : elem_(v.elem_), size_(v.size_), capacity_(v.capacity_)
{
	cout << "move constructors" << endl;
	v.elem_ = nullptr;
	v.size_ = 0;
	v.capacity_ = 0;
}


template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept
{
	if(this != &v)
	{
		cout << "move assignments" << endl;

		delete[] elem_;
		elem_ = v.elem_;
		size_ = v.size_;
		capacity_ = v.capacity_;
		v.elem_ = nullptr;
		v.size_ = 0;
		v.capacity_ = 0;
	}
	return *this;
}


template<typename T>
vector<T>::vector(const vector<T>& v)
{
	cout << "copy constructor" << endl;
	CopyForm(v.elem_, 0, v.size_);
}


template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
	cout << "assignment operator" << endl;
	if(elem_) delete[] elem_;
	CopyForm(v.elem_, 0, v.Size());
	return *this;
}


template<typename T>
void vector<T>::CopyForm(T const* A, Rank lo, Rank hi)
{
	elem_ = new T[capacity_ = 2 * (hi - lo)];
	size_ = 0;
	while(lo < hi)
		elem_[size_++] = A[lo++];
}


template<typename T>
void vector<T>::Expand()
{
	if(size_ < capacity_) return;
	if(capacity_ < DEFAULTcapacity_) capacity_ = DEFAULTcapacity_;
	T* _oldelem = elem_;
	elem_ = new T[capacity_ <<= 1];
	for(int i = 0; i < size_; ++i)
		elem_[i] = _oldelem[i];
	delete[] _oldelem;
}


template<typename T>
void vector<T>::Shrink()
{
	if(capacity_ < DEFAULTcapacity_ << 1) return;
	if(size_ << 2 > capacity_) return;
	T* _oldelem = elem_;
	elem_ = new T[capacity_ >>= 1];
	for(int i = 0; i < size_; ++i)
		elem_[i] = _oldelem[i];
	delete[] _oldelem;
}


template<typename T>
void vector<T>::Unsort()
{
	for(Rank i = size_; i > 0; --i)
		std::swap(elem_[i - 1], elem_[rand() % i]);
}


template<typename T>
void vector<T>::Insert(Rank r, const T&e)
{
	if(r > size_) return;
	Expand();
	for(Rank i = size_; i > r; --i)
		elem_[i] = elem_[i - 1];
	elem_[r] = e;
	++size_;
}


template<typename T>
int vector<T>::Remove(Rank lo, Rank hi)
{
	if(lo == hi) return 0;
	while(hi < size_) elem_[lo++] = elem_[hi++];
	size_ = lo;
	Shrink();
	return static_cast<int>(hi - lo);
}


template<typename T>
T vector<T>::Remove(Rank r)
{
	T e = elem_[r];
	Remove(r, r + 1);
	return e;
}


template<typename T>
Rank vector<T>::Find(const T&e, Rank lo, Rank hi) const
{
	while(hi > lo && e != elem_[hi])
	{
		--hi;
	}
	return hi;
}


template<typename T>
Rank vector<T>::Search(const T&e, Rank lo, Rank hi) const
{
	while(lo < hi)
	{
		Rank mi = lo + (hi - lo) / 2;
		if(e < elem_[mi])
			hi = mi;
		else if(e > elem_[mi])
			lo = mi + 1;
		else
			return mi;
	}
	return -1;
}


template<typename T>
Rank vector<T>::Size() const
{
	return size_;
}


template<typename T>
int vector<T>::Deduplicate()
{
	Rank oldsize = size_;
	Rank i  = 1;
	while(i < size_)
	{
		(Find(elem_[i], 0, i) < 0) ? ++i : Remove(i);
	}
	return static_cast<int>(oldsize - size_);
}


template<typename T>
int vector<T>::Uniquift()
{
	Rank i = 0, j = 0;
	while(++j < size_)
	{
		if(elem_[i] != elem_[j])
			elem_[++i] = elem_[j];
	}
	size_ = ++i; Shrink();
	return j - i;
}


template<typename T>
T& vector<T>::operator[](Rank r) const
{
	return elem_[r];
}


template<typename T>
bool vector<T>::Empty() const
{
	return size_ == 0 ? true : false;
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
		for ( int i = 0; i < size_; i++ )
			Print<T>()(elem_[i]);
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
	srand(time(nullptr));
	switch(rand() % 3)
	{
		case 0:
			SelectSort();
			break;
		case 1:
			BubbleSort();
			break;
		case 2:
			InsertionSort();
			break;
	}
}

template<typename T>
void vector<T>::InsertionSort()
{
	Rank i, j;
	int key;
	cout << "InsertionSort" << endl;
	for(i = 1; i < size_ - 1; ++i)
	{
		key = elem_[i];
		j = i - 1;
		while((j >= 0) && (elem_[j] > elem_[i]))
		{
			elem_[i] = elem_[j];
			--j;
		}
		elem_[j + 1] = key;
	}
}

template<typename T>
void vector<T>::SelectSort()
{
	Rank min = 0;
	cout << "Seletct" << endl;
	for(Rank i = 0; i < size_ - 1; ++i)
	{
		min = i;
		for(Rank j = i + 1; j < size_; ++j)
		{
			if(elem_[min] > elem_[j])
				min = j;
		}
		std::swap(elem_[i], elem_[min]);
	}
}


template<typename T>
void vector<T>::BubbleSort()
{
	cout << "Bubble" << endl;
	for(Rank i = 0; i < size_; ++i)
	{
		bool sorted = true;
		for(Rank j = i + 1; j < size_; ++j)
		{
			if(elem_[j] < elem_[i])
			{
				sorted = false;
				std::swap(elem_[j], elem_[i]);
			}
		}
		if(sorted == true)
			return;
	}
}

#endif /* vector_hpp */
