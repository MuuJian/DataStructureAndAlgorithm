//
//  list.hpp
//  DataStructureAndAlgorithm
//
//  Created by mumu on 29/11/2020.
//

#ifndef listnode_h
#define listnode_h

#include "header.hpp"

template<typename T>
class ListNode;
template<typename T>
using ListNodePosi = ListNode<T> *;
template<typename T>
class List;

template<typename T>
class ListNode
{
	friend class List<T>;
private:
	T data_;
	ListNodePosi<T> pred_;
	ListNodePosi<T> succ_;
	
public:
	ListNode(){};
	ListNode(T e, ListNodePosi<T> pred = nullptr, ListNodePosi<T> succ = nullptr)
		: data_{e}, pred_{pred}, succ_{succ} {}

	ListNodePosi<T> InsertAsPred(const T& e);
	ListNodePosi<T> InsertAsSucc(const T& e);
};

template<typename T>
ListNodePosi<T> ListNode<T>::InsertAsPred(const T& e)
{
	ListNodePosi<T> x = new ListNode(e, pred_, this);
	pred_ -> succ_ = x;
	this -> pred_ = x;
	return x;
}

template<typename T>
ListNodePosi<T> ListNode<T>::InsertAsSucc(const T& e)
{
	ListNodePosi<T> x = new ListNode(e, this, succ_);
	succ_ -> pred_ = x;
	this -> succ_ = x;
	return x;
}

#endif /* list_h */
