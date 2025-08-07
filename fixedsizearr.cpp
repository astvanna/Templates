#include <iostream>

template<typename T, std::size_t N>
class FixedArray {
private:
    T data[N];

public:
    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    std::size_t size() const {
        return N;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + N;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + N;
    }
};
