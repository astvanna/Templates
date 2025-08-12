#include <iostream>

template <typename T1, typename T2>
struct is_same {
    enum { value = 0 };
};

template <typename T>
struct is_same<T, T> {
    enum { value = 1};
};

template <typename T, typename... Types>
struct is_unique;

template <typename T, typename T1, typename ...Types>
struct is_unique<T, T1, Types...> {
    enum { value = is_same<T, T1>:: value ? 0 : is_unique<T, Types...>:: value};
};

template <typename T>
struct is_unique<T> {
    enum { value = 1};
};

template <typename ...Types>
struct count_types;

template <typename T, typename T1, typename ...Types>
struct count_types<T, T1, Types...> {
    enum { value = (is_unique<T, T1, Types...>:: value ? 1 : 0) + count_types<T1,Types...>:: value};
};

template <>
struct count_types<> {
    enum { value = 0 };
};

template <typename T>
struct count_types<T> {
    enum { value = 1 };
};



int main() {
    std::cout << count_types<>:: value << std::endl;
    std::cout << count_types<int>:: value << std::endl;
    std::cout << count_types<int, double, std::string>:: value << std::endl;
    std::cout << count_types<int, int, double>:: value << std::endl;
}

