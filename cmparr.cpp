#include <iostream>

template<typename T, std::size_t N1, std::size_t N2>
class CompareArrays {
public:
    static void compare(const T(&arr1)[N1], const T(&arr2)[N2]) {
        std::cout << "Cant cmp arrs of diff sizes: "<< std::endl;
    }
};

template<typename T, std::size_t N>
class CompareArrays<T, N, N> {
public:
    static void compare(const T(&arr1)[N], const T(&arr2)[N]) {
        for (std::size_t i = 0; i < N; ++i) {
            if (arr1[i] != arr2[i]) {
                std::cout << "Arrays differ at index " << i << std::endl;
                return;
            }
        }
        std::cout << "Arrs are the same" << std::endl;
    }
};

