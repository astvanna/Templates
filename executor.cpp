#include <iostream>

template<void (*Func)()>
class Executor {
public:
    void run() const {
        Func();
    }
};

void hello() {
    std::cout << "Hello" << std::endl;
}

void bye() {
    std::cout << "Bye!" << std::endl;
}
