#include <iostream>

template <int N, int i>
struct IsPrime_Helper {
    static constexpr bool value = (N % i != 0) && IsPrime_Helper<N, i - 1>::value;
};

template <int N>
struct IsPrime_Helper<N, 1> {
    static constexpr bool value = true;
};

template <int N>
struct IsPrime {
    static constexpr bool value = (N > 1) && IsPrime_Helper<N, N / 2>::value;
};

template <>
struct IsPrime<0> {
    static constexpr bool value = false;
};

template <>
struct IsPrime<1> {
    static constexpr bool value = false;
};
