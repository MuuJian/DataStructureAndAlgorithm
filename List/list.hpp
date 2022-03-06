//
//  list.hpp
//  DataStructureAndAlgorithm
//
//  Created by mumu on 29/11/2020.
//

#ifndef list_h
#define list_h

#include "listnode.hpp"

template<typename T>
class List
{
private:
	Rank size_ = 0;
	ListNodePosi<T> header_ = nullptr;
	ListNodePosi<T> trailer_ = nullptr;
	
protected:
	void Init(); //初始化
	void Clear(); //清除全部节点
	void CopyNodes(ListNodePosi<T> p, int n); //复制自p项起n个节点
	T Remove(ListNodePosi<T> p);
	
public:
	//构造
	List(){ Init();}
	List(List<T> const& l);
	List(List<T> const& l, Rank r, int n);
	List(ListNodePosi<T> p, int n);
	List(const initializer_list<T>& list);
	List(List<T>&& v) noexcept; //移动构造
	List<T>& operator=(const List<T>& v); //拷贝运算符
	List<T>& operator=(List<T>&& v) noexcept; //移动赋值运算符

	//析构
	~List();
	
	//可读接口
	Rank Size() const{ return size_;}
	bool empty() const { return size_ <= 0;}
	T& operator[](Rank r) const;
	
	ListNodePosi<T> First() const { return header_ -> succ_;}
	ListNodePosi<T>	Last() const { return trailer_ -> pred_;}
	
	bool valid(ListNodePosi<T> p) //是否合法
	{
		return p && (trailer_ != p) && (header_ != p);
	}
	
	ListNodePosi<T> Find(const T& e) const //无序查找从后开始
	{
		return find(e, size_, trailer_);
	}
	ListNodePosi<T> Find(const T& e, Rank n, ListNodePosi<T> p) const;
	
	ListNodePosi<T> Search(const T& e) const //有序查找
	{
		return Search(e, size_, trailer_);
	}
	ListNodePosi<T> Search(const T& e, Rank n, ListNodePosi<T> p) const;
	
	//可写
	ListNodePosi<T> InsertAsFirst(const T& e); //插頭
	ListNodePosi<T> InsertAsLast(const T& e); //插尾
	ListNodePosi<T> InsertA(ListNodePosi<T> p, const T& e); //前驅插入
	ListNodePosi<T> InsertB(ListNodePosi<T> p, const T& e); //後繼插入

	int Deduplicate();
	
	void Reverse();
	
	//遍歷
	void Traverse();

};

template<typename T>
void List<T>::Init()
{
	header_ = new ListNode<T>;
	trailer_ = new ListNode<T>;
	header_ -> succ_ = trailer_; header_ -> pred_ = nullptr;
	trailer_ -> succ_ = nullptr; trailer_ -> pred_ = header_;
	size_ = 0;
}

template<typename T>
void List<T>::CopyNodes(ListNodePosi<T> p, int n)
{
	Init();
	while(n--)
	{
		InsertAsLast(p -> data_);
		p = p -> succ_;
	}
}

template<typename T>
T List<T>::Remove(ListNodePosi<T> p)
{
	p -> succ_ -> pred_ = p -> pred_;
	p -> pred_ -> succ_ = p -> succ_;
	T data = p -> data_;
	delete p;
	--size_;
	return data;
}

template<typename T>
void List<T>::Clear()
{
	while(0 < size_)
		Remove(header_->succ_);
}

template<typename T>
List<T>::List(ListNodePosi<T> p, int n)
{
	CopyNodes(p, n);
}

template<typename T>
List<T>::List(const List<T>& l)
{
	CopyNodes(l.First(), l.size_);
}

template<typename T>
List<T>::List(List<T> const& l, Rank r, int n)
{
	CopyNodes(l[r], n);
}

template<typename T>
List<T>::List(const initializer_list<T>& list)
{
	this -> Init();
	for(const T& a: list)
	{
		this -> InsertAsLast(a);
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& v)
{
	if(size_ > 0) Clear();
	CopyNodes(v.First(), v.size_);
	return *this;
}

template<typename T>
List<T>::List(List<T>&& l) noexcept: size_(l.size), header_(l.header_), trailer_(l.trailer_)
{
	l.header_ = nullptr;
	l.trailer_ = nullptr;
	l.size_ = 0;
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& l) noexcept
{
	if(this != &l)
	{
		Clear();
		delete header_;
		delete trailer_;
		size_ = l.size_;
		header_ = l.header_;
		trailer_ = l.trailer_;
		l.size_ = 0;
		l.header_ = nullptr;
		l.trailer_ = nullptr;
	}
	return *this;
}

template<typename T>
List<T>::~List()
{
	Clear();
	delete header_;
	delete trailer_;
}

template<typename T>
T& List<T>::operator[](Rank r) const
{
	ListNodePosi<T> p = First();
	while(0 < r--)
	{
		p = p -> succ_;
	}
	return p -> data_;
}

template<typename T>
ListNodePosi<T> List<T>::Find(const T& e, Rank n, ListNodePosi<T> p) const
{
	while(0 < n--)
	{
		p = p -> pred_;
		if(e == p -> data_)
			return p;
	}
	return nullptr;
}

template<typename T>
ListNodePosi<T> List<T>::Search(const T& e, Rank n, ListNodePosi<T> p) const
{
	while(0 < n--)
	{
		p = p -> pred_;
		if(e >= p -> data_)
			break;
	}
	return p;
}

template<typename T>
ListNodePosi<T> List<T>::InsertAsFirst(const T &e)
{
	size_++;
	return header_->InsertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::InsertAsLast(const T &e)
{
	size_++;
	return trailer_->InsertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::InsertA(ListNodePosi<T> p, const T &e)
{
	size_++;
	return p->InsertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::InsertB(ListNodePosi<T> p, const T &e)
{
	size_++;
	return p->InsertAsSucc(e);
}

template<typename T>
void List<T>::Reverse()
{
	ListNodePosi<T> prev = header_;
	ListNodePosi<T> curr = header_ -> succ_;
	ListNodePosi<T> next;
	while(curr != nullptr)
	{
		next = curr -> succ_;
		curr -> succ_ = prev;
		prev = curr;
		curr = next;
	}
	
	prev = trailer_;
	curr = trailer_ -> pred_;
	next = nullptr;
	while(curr != nullptr)
	{
		next = curr -> pred_;
		curr -> pred_ = prev;
		prev = curr;
		curr = next;
	}
	header_ -> succ_ = nullptr;
	trailer_ -> pred_ = nullptr;
	swap(header_, trailer_);
}

template<typename T>
int List<T>::Deduplicate()
{
	if(size_ < 2) return 0;
	Rank oldsize = size_;
	ListNodePosi<T> p = First(); int r = 1;
	while(trailer_ != (p -> succ_))
	{
		ListNodePosi<T> q = Find(p -> data_, r, p);
		q ? Remove(q) : ++r;
		p = p -> succ_;
	}
	return static_cast<int>(oldsize - size_);
	
}

template<typename T>
void List<T>::Traverse()
{
	for(auto p = header_ -> succ_; p != trailer_; p = p -> succ_)
	{
		Print<T>()(p -> data_);
	}
	cout << endl;
}

#endif /* list_h */
