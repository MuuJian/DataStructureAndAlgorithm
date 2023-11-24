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

template<typename T>
class Vector
{
private:
	size_type size_ = 0;
	size_type capacity_ = 0;
	T* elem_ = nullptr;
	
protected:
	void CopyForm(const T* A, size_type lo, size_type hi)  //复制数组区间
    {
        elem_ = new T[capacity_ = 2 * (hi - lo)];
        size_ = 0;
        while(lo < hi)
            elem_[size_++] = A[lo++];
    }
    
	void Expand() //扩容
    {
        if(size_ < capacity_) return;
        if(capacity_ < DEFAULTcapacity_) capacity_ = DEFAULTcapacity_;
        T* _oldelem = elem_;
        elem_ = new T[capacity_ <<= 1];
        for(int i = 0; i < size_; ++i)
            elem_[i] = _oldelem[i];
        delete[] _oldelem;
    }

	void Shrink() //压缩
    {
        if(capacity_ < DEFAULTcapacity_ << 1) return;
        if(size_ << 2 > capacity_) return;
        T* _oldelem = elem_;
        elem_ = new T[capacity_ >>= 1];
        for(int i = 0; i < size_; ++i)
            elem_[i] = _oldelem[i];
        delete[] _oldelem;
    }
    
	T Remove(size_type r) //删除下标为r的元素
    {
        T e = elem_[r];
        Remove(r, r + 1);
        return e;
    }

	int Remove(size_type lo, size_type hi) //删除区间
    {
        if(lo == hi) return 0;
        while(hi < size_) elem_[lo++] = elem_[hi++];
        size_ = lo;
        Shrink();
        return static_cast<int>(hi - lo);
    }
    
	//排序
	void SelectSort()
    {
        size_type min = 0;
        cout << "Seletct" << endl;
        for(size_type i = 0; i < size_ - 1; ++i)
        {
            min = i;
            for(size_type j = i + 1; j < size_; ++j)
            {
                if(elem_[min] > elem_[j])
                    min = j;
            }
            swap(elem_[i], elem_[min]);
        }
    }

	void BubbleSort()
    {
        cout << "bubble" << endl;
        for(size_type i = 0; i < size_; ++i)
        {
            for(size_type j = i + 1; j < size_; ++j)
            {
                if(elem_[i] > elem_[j])
                    swap(elem_[i], elem_[j]);
            }
        }
    }
    
	void InsertionSort()
    {
        size_type i, j;
        int key;
        cout << "InsertionSort" << endl;
        for(i = 1; i < size_; ++i)
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
	
	/*
	void Merge(size_type lo, size_type mi, size_type hi);
	void MergeSort(size_type lo, size_type hi);
	size_type Partition(size_type lo, size_type hi);
	void QuickSort(size_type lo, size_type hi);
	void HeapSort(size_type lo, size_type hi);
	*/
	
public:
    Vector() = default;
    
    explicit Vector(size_type size, T var = 0)  //构造函数
    {
        cout << "constructor" << endl;
        elem_ = new T[capacity_ = size * 2];
        for(size_ = 0; size_ < size; ++size_)
        {
            elem_[size_] = var;
        }
    }

	Vector(const initializer_list<T>& list)  //列表构造函数
    {
        cout << "initializer_list construcot" << endl;
        elem_ = new T[capacity_ = 2 * list.size()];
        size_ = 0;
        for(const T& tmp : list)
        {
            elem_[size_++] = tmp;
        }
    }
    
	Vector(const Vector& v)  //复制构造
    {
        cout << "copy constructor" << endl;
        CopyForm(v.elem_, 0, v.size_);
    }

	Vector& operator=(const Vector& v) //拷贝运算符
    {
        cout << "assignment operator" << endl;
        if(elem_) delete[] elem_;
        CopyForm(v.elem_, 0, v.Size());
        return *this;
    }
    
    Vector(Vector&& v) noexcept : elem_(v.elem_), size_(v.size_), capacity_(v.capacity_) //移动构造
    {
        cout << "move constructors" << endl;
        v.elem_ = nullptr;
        v.size_ = 0;
        v.capacity_ = 0;
    }
    
	Vector& operator=(Vector&& v) noexcept //移动赋值运算符
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

	~Vector()  //析构
    {
        cout << "destroy" << endl;
        delete[] elem_;
    }
    
	T& operator[](size_type r) const //下标访问
    {
        return elem_[r];
    }

	void Insert(size_type r, const T& e) //插入
    {
        Expand();
        for(size_type i = size_; i > r; --i)
            elem_[i] = elem_[i - 1];
        elem_[r] = e;
        ++size_;
    }
	void Insert(const T& e) //末尾插入
    {
        return Insert(size_, e);
    }
	
	size_type Size() const //规模
    {
        return size_;
    }
    
	bool Empty() const //判断为空
    {
        return size_ <= 0;
    }
	
	int Deduplicate() //无序去重
    {
        size_type oldsize = size_;
        size_type i  = 1;
        while(i < size_)
        {
            (Find(elem_[i], 0, i) == i) ? ++i : Remove(i);
        }
        return static_cast<int>(oldsize - size_);
    }
    
	int Uniquift() //有序去重
    {
        size_type i = 0, j = 0;
        while(++j < size_)
        {
            if(elem_[i] != elem_[j])
                elem_[++i] = elem_[j];
        }
        size_ = ++i; Shrink();
        return static_cast<int>(j - i);
    }
    
    void Unsort() //乱序
    {
        for(size_type i = size_; i > 0; --i)
            std::swap(elem_[i - 1], elem_[rand() % i]);
    }

	template<typename VST = Print<T> >
	void Traverse(const VST& visit = VST()) //遍历
    {
        for(int i = 0; i < size_; i++ )
            visit(elem_[i]);
    }
	
	size_type Search(const T& e) const { return (0 >= size_) ? -1 : Search(e, 0, size_);} //有序查找
	size_type Search(const T& e, size_type lo, size_type hi) const //有序区间查找
    {
        while(lo < hi)
        {
            size_type mi = lo + (hi - lo) / 2;
            if(e < elem_[mi])
                hi = mi;
            else if(e > elem_[mi])
                lo = mi + 1;
            else
                return mi;
        }
        return -1;
    }
    
    size_type Find(const T& e) const //无序查找
    {
        return Find(e, 0, size_);
    }
    size_type Find(const T& e, size_type lo, size_type hi) const //无序区间查找
    {
        while((lo < hi) && e != elem_[lo])
            ++lo;
        return lo;
    }
	
	void Sort() //排序
    {
        srand(static_cast<unsigned int>(time(nullptr)));
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
    
};


#endif /* vector_hpp */
