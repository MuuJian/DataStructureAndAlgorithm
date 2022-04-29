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
	void Init() //初始化
    {
        header_ = new ListNode<T>;
        trailer_ = new ListNode<T>;
        header_ -> succ_ = trailer_; header_ -> pred_ = nullptr;
        trailer_ -> succ_ = nullptr; trailer_ -> pred_ = header_;
        size_ = 0;
    }
    
	void Clear() //清除全部节点
    {
        while(0 < size_)
            Remove(header_->succ_);
    }
    
	void CopyNodes(ListNodePosi<T> p, int n) //复制自p项起n个节点
    {
        Init();
        while(n--)
        {
            InsertAsLast(p -> data_);
            p = p -> succ_;
        }
    }

	T Remove(ListNodePosi<T> p)
    {
        p -> succ_ -> pred_ = p -> pred_;
        p -> pred_ -> succ_ = p -> succ_;
        T data = p -> data_;
        delete p;
        --size_;
        return data;
    }
	
public:
	//构造
	List(){ Init();}
    
	List(List const& l)
    {
        CopyNodes(l.First(), l.size_);
    }
    
	List(List const& l, Rank r, int n)
    {
        CopyNodes(l[r], n);
    }

	List(ListNodePosi<T> p, int n)
    {
        CopyNodes(p, n);
    }

	List(const initializer_list<T>& list)
    {
        this -> Init();
        for(const T& a: list)
        {
            this -> InsertAsLast(a);
        }
    }
    
    List(List&& l) noexcept: size_(l.size), header_(l.header_), trailer_(l.trailer_) //移动构造
    {
        l.header_ = nullptr;
        l.trailer_ = nullptr;
        l.size_ = 0;
        return *this;
    }

	List& operator=(const List& v) //拷贝运算符
    {
        if(size_ > 0) Clear();
        CopyNodes(v.First(), v.size_);
        return *this;
    }
    
	List& operator=(List&& l) noexcept //移动赋值运算符
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


	//析构
	~List()
    {
        Clear();
        delete header_;
        delete trailer_;
    }
	
	//可读接口
	Rank Size() const
    {
        return size_;
    }
    
	bool empty() const
    {
        return size_ <= 0;
    }
    
	T& operator[](Rank r) const
    
    {
        ListNodePosi<T> p = First();
        while(0 < r--)
        {
            p = p -> succ_;
        }
        return p -> data_;
    }
	
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
	ListNodePosi<T> Find(const T& e, Rank n, ListNodePosi<T> p) const
    {
        while(0 < n--)
        {
            p = p -> pred_;
            if(e == p -> data_)
                return p;
        }
        return nullptr;
    }
	
	ListNodePosi<T> Search(const T& e) const //有序查找
	{
		return Search(e, size_, trailer_);
	}
	ListNodePosi<T> Search(const T& e, Rank n, ListNodePosi<T> p) const
    {
        while(0 < n--)
        {
            p = p -> pred_;
            if(e >= p -> data_)
                break;
        }
        return p;
    }
	
	//可写
	ListNodePosi<T> InsertAsFirst(const T& e) //插頭
    {
        size_++;
        return header_->InsertAsSucc(e);
    }

	ListNodePosi<T> InsertAsLast(const T& e)  //插尾
    {
        size_++;
        return trailer_->InsertAsPred(e);
    }
    
	ListNodePosi<T> InsertA(ListNodePosi<T> p, const T& e)  //前驅插入
    {
        size_++;
        return p->InsertAsPred(e);
    }
    
	ListNodePosi<T> InsertB(ListNodePosi<T> p, const T& e) //後繼插入
    {
        size_++;
        return p->InsertAsSucc(e);
    }

	int Deduplicate()
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
	
	void Reverse()
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
	
	//遍歷
	void Traverse()
    {
        for(auto p = header_ -> succ_; p != trailer_; p = p -> succ_)
        {
            Print<T>()(p -> data_);
        }
        cout << endl;
    }


};


#endif /* list_h */
