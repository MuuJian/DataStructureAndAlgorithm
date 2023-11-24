//
//  stack.hpp
//  DataStructureAndAlgorithm
//
//  Created by mu mu on 24/11/2023.
//

#ifndef stack_hpp
#define stack_hpp

#include "header.hpp"
#include "vector_hpp"

template<typename T, typename Container = Vector<T>>
class Stack
{
public:
    
    explicit Stack(const Container& container)
        : container_(container)
    {
        
    }
    
    explicit stack( Container &&container = Container() )
        : container_(std::move(container))
    {
    }
    
    bool Empty() const
    {
        return container_.Empty();
    }
    
    size_type Size() const
    {
        return container_.Size();
    }
    
    reference Top()
    {
        if(container_.Empty())
        {
            return nullptr;
        }
        return container_[container_.Size() - 1];
    }
    
    const_reference Top() const
    {
        return const_cast<stack *>(this)->top();
    }

    void push( const value_type &value )
    {
        auto copy = value;
        push( std::move( copy ) );
    }

    void push( value_type &&value )
    {
        emplace( std::move( value ) );
    }

    template<typename... Args>
    void emplace( Args&&... args )
    {
        container_.emplace_back( std::forward<Args>( args )... );
    }

    void pop()
    {
        if( container_.empty() )
        {
            return;
        }
        container_.pop_back();
    }
     
    void swap( stack &other ) noexcept( noexcept( swap( container_, other.container_ ) ) )
    {
        using std::swap;
        swap( container_, other.container );
    }
    
    
    
    
    
    
private:
    
    Container container_;
}


#endif /* stack_hpp */
