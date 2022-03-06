//
//  UniquePtr.hpp
//  DataStructureAndAlgorithm
//
//  Created by mumu on 6/3/2022.
//

#ifndef UniquePtr_h
#define UniquePtr_h

class Delete{
public:
    template<typename T>
    void operator()(T* ptr) const
    {
        delete ptr;
    }
};

template<typename T, typename D = Delete>
class UniquePtr{
public:
    UniquePtr(T* ptr = nullptr,const D& d = Delete()): ptr_(ptr), del_(d)
    {
    }
    ~UniquePtr() { del_(ptr_);}
    
    UniquePtr(const UniquePtr&) = delete;
    
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    UniquePtr(UniquePtr&& u) noexcept : ptr_(u.ptr_), del_(std::move(u.del_))
    {
        u.ptr_ = nullptr;
    }
    
    UniquePtr& operator=(UniquePtr&& u) noexcept
    {
        if(this != &u)
        {
            reset(u.ptr_);
            del_ = std::move(u.del_);
            u.ptr_ = nullptr;
        }
        return *this;
    }
    
    UniquePtr& operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }
    
    void reset(T* ptr = nullptr) noexcept
    {
        T* old_ptr = ptr_;
        ptr_ = ptr;
        if(old_ptr != nullptr)
        {
            get_deleter()(old_ptr);
        }
    }
    
    T* release() noexcept
    {
        T* ret = ptr_;
        ptr_ = nullptr;
        return ret;
    }
    
    void swap(UniquePtr& other) noexcept
    {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(del_, other.del_);
    }

    T* get() const noexcept { return ptr_; }
    D& get_deleter() noexcept { return del_; }
    const D& get_deleter() const noexcept { return del_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }
    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }

private:
    T* ptr_ = nullptr;
    D del_;
};

#endif /* UniquePtr_h */
