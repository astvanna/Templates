#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

template <typename T>
void printSeparator(const T& separator) { 
    std::cout << std::endl;
}

template <typename T>
std::string uppercase(const T& arg) {
    std::string str = arg;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

template <typename T>
std::string compress(const T& arg) {
    std::string str;
    for (int i = 0; i < arg.size(); ++i) {
        if (arg[i] != ' ') {
            str += arg[i];
        }
    }
    return str;
}

template <typename T1, typename T, typename ...Types>
void printSeparator(const T1& separator, const T& firstArg, const Types&... args) {
    std::cout << firstArg;
    if (sizeof...(args) > 0) {
        std::cout << separator;
    }d printSeparator(separator, args...);
}

template <typename T, typename ...Types>
void printUpper(const T& separator, const Types&... args) {d printSeparator(separator, uppercase(static_cast<std::string>(args))...);
}

template <typename... Types>
void printCompressed(const Types&... args) {d printSeparator("", compress(static_cast<std::string>(args))...);
}

int main() {
    printSeparator(", ", "apple", "banana", "cherry");  // → apple, banana, cherry
    printUpper(", ", "hello", "world");  // → HELLO, WORLD
    printCompressed("  this   is    compressed  ");  // → thisiscompressed
    return 0;
}
