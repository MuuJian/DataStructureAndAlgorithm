//
//  SharedPtr.h
//  DataStructureAndAlgorithm
//
//  Created by mumu on 6/3/2022.
//

#ifndef SharedPtr_h
#define SharedPtr_h

template<typename T>
class SharedPtr
{
public:
    using DelFuncPtr = void(*)(T*); //    typedef void (*DelFuncPtr)(T*);
    SharedPtr(T* ptr = nullptr, DelFuncPtr del = nullptr):
        ptr_(ptr), count_ptr_(new size_t(ptr != nullptr)), del_(del)
    {
    }
    
    void destroy()
    {
        if(!ptr_) return;
        if((--*count_ptr_) == 0)
        {
            del_ ? del_(ptr_) : delete ptr_;
            delete count_ptr_;
        }
        ptr_    = nullptr;
        count_ptr_ = nullptr;
    }
    
    ~SharedPtr()
    {
        destroy();
    }
    
    SharedPtr(const SharedPtr& sp): ptr_(sp.ptr_), count_ptr_(sp.count_ptr_), del_(sp.del_)
    {
        ++(*count_ptr_);
    }
    
    SharedPtr& operator=(const SharedPtr& sp)
    {
        if(this != &sp)
        {
            destroy();
            ptr_ = sp.ptr_;
            count_ptr_ = sp.count_ptr_;
            del_ = sp.del_;
            ++(*count_ptr_);
        }
        return *this;
    }
    
    SharedPtr(SharedPtr&& sp) noexcept: ptr_(sp.ptr_), count_ptr_(sp.count_ptr_), del_(sp.del_)
    {
        sp.ptr_ = nullptr;
        sp.count_ptr_ = nullptr;
        sp.del_ = nullptr;
    }
    
    SharedPtr& operator=(SharedPtr&& sp) noexcept
    {
        if(this != &sp)
        {
            destroy();
            ptr_ = sp.ptr_;
            count_ptr_ = sp.count_ptr_;
            del_ = sp.del_;
            sp.ptr_ = nullptr;
            sp.count_ptr_ = nullptr;
            sp.del_ = nullptr;
        }
        return *this;
    }
    
    void reset(T* ptr = nullptr, DelFuncPtr del = nullptr)
    {
        SharedPtr tmp(ptr, del);
        swap(tmp);
    }
    
    void swap(SharedPtr& sp)
    {
        using std::swap;
        swap(ptr_, sp.ptr_);
        swap(count_ptr_, sp.count_ptr_);
        swap(del_, sp.del_);
    }
    
    T* get() const noexcept { return ptr_; }
    T& operator*() const noexcept { return *get(); }
    T* operator->() const noexcept { return get(); }
    size_t use_count() const noexcept { return *count_ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }
    
private:
    T* ptr_ = nullptr;
    size_t* count_ptr_ = nullptr;
    DelFuncPtr del_ = nullptr;
};

#endif /* SharedPtr_h */
