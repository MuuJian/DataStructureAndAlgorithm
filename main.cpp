#include<iostream>
#include "SharedPtr.hpp"

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

int main()
{
    std::cout << "SharedPtr constructor with no managed object\n";
    {
        SharedPtr<Foo> sh1;
    }
    
    std::cout << "SharedPtr constructor with object\n";
    {
        SharedPtr<Foo> sh2(new Foo);
        std::cout << sh2.use_count() << '\n';
        SharedPtr<Foo> sh3(sh2);
        std::cout << sh3.use_count() << '\n';
        SharedPtr<Foo> sh4;
        sh4 = std::move(sh3);
        std::cout << sh4.use_count() << '\n';
    }
    
    std::cout << "SharedPtr constructor with deleter\n";
    {
        SharedPtr<Foo> sh5(new Foo, [](Foo* p) {
            std::cout << "Call delete from lambda...\n";
            delete p;
        });
    }

    {
        SharedPtr<Fooo> sptr(new Fooo(1));
        std::cout << "The first Fooo's bar is " << sptr->GetBar() << "\n";
        sptr.reset(new Fooo);
        std::cout << "The second Fooo's bar is " << sptr->GetBar() << "\n";
    }





}
