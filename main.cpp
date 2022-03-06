#include<iostream>
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"
#include "DebugDelete.hpp"

struct Foo {
    Foo() { std::cout << "Foo()\n"; }
    ~Foo() { std::cout << "~Foo()\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
};

struct Fooo {
    Fooo(int n = 0) noexcept : bar(n) { std::cout << "Fooo: constructor, bar = " << bar << '\n'; }
    ~Fooo() { std::cout << "Fooo: destructor, bar = " << bar << '\n'; }
    int GetBar() const noexcept { return bar; }

private:
    int bar;
};

struct D {
    void bar() { std::cout << "Call deleter D::bar()...\n"; }
    void operator()(Foo* p) const
    {
        std::cout << "Call delete from function object...\n";
        delete p;
    }
};

int main()
{
    {
        std::cout << "======================\nUniquePtr constructor:\n";
        UniquePtr<Foo> up5b(new Foo());
        UniquePtr<Foo> up7(new Foo());
        up7 = std::move(up5b);
        Foo* fp = up7.release();
        assert(up7.get() == nullptr);
        delete fp;

    
    }
}
