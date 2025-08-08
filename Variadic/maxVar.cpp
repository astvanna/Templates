#include <iostream>

// double max_variadic() {
//     return 0.0;
// }

// template<typename T>
// T max_variadic(T single) {
//     return single;
// }

// template<typename T1, typename T2, typename... Args>
// auto max_variadic(T1 a, T2 b, Args... args) {
//     auto max1 = a > b ? a : b;
//     return max_variadic(max1, args...);
// }


auto max_variadic() {
    return 0.0;
}

template<typename T, typename... Types>
auto max_variadic(T first, Types... args) {
    using Common = typename std::common_type<T, Types...>::type;
    Common val = first;
    ((val = (val > args ? val : args)), ...);
    return val;
}


int main() {
    std::cout << max_variadic(1, 2.3, 4.5, 4, 'a') << std::endl;
    std::cout << max_variadic(12) << std::endl;
    std::cout << max_variadic() << std::endl;
    return 0;
}