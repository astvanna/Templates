#include <iostream>

void print_reverse() {
    std::cout << std::endl;
}

template<typename T, typename... Types>
void print_reverse(T first, Types... types) {
    print_reverse(types...);
    std::cout << first << " ";
}

int main() {
    print_reverse('a', 9, 'b', 8, 'c', 7);
    std::cout << std::endl;
}

