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
class list
{
private:
	int size_;
	ListNodePosi<T> header_;
	ListNodePosi<T> trailer_;
	
protected:
	void Init(); //初始化
	int Clear(); //清除全部节点
	void CopyNodes(ListNodePosi<T> p, int n); //复制自p项起n个节点

public:
	
	//构造
	list(){ Init();}
	list(list<T> const& L);
	list(list<T> const& L, Rank r, int n);
	list(ListNodePosi<T> p, int n);
	//构造重载
	/*
	 list<T>& operator=(const list<T>& v); //拷贝运算符
	 list(list<T>&& v) noexcept; //移动构造
	 list<T>& operator=(list<T>&& v) noexcept; //移动赋值运算符
	 */
	
	//析构
	~list();
	
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
	int disordered() const; //是否有序
	
	ListNodePosi<T> Find(const T& e) const //无序查找从后开始
	{
		return find(e, size_, trailer_);
	}
	ListNodePosi<T> Find(const T& e,int n, ListNodePosi<T> p) const;
	
	ListNodePosi<T> Search(const T& e) const //有序查找
	{
		return Search(e, size_, trailer_);
	}
	ListNodePosi<T> Search(const T& e, int n, ListNodePosi<T> p) const;
	
	ListNodePosi<T> Max() const;
	ListNodePosi<T> Min() const;
	
	//可写
};


#endif /* list_h */
