#include <iostream>
#include <vector>

template <typename T, size_t N>
class MultiDimMatrix;

template <typename T>
class MultiDimMatrix<T, 1> {
private:
    std::vector<T> _data;
    size_t _size;

public:
    MultiDimMatrix(size_t size, const std::vector<size_t>&) : _size(size), _data(size) {}

    T& operator[](size_t index) {
        return _data[index];
    }

    const T& operator[](size_t index) const {
        return _data[index];
    }

    void fill(const T& value) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = value;
        }
    }

    template <typename Func>
    void apply(Func func) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = func(_data[i]);
        }
    }

    T sum() const {
        T total = T(0);
        for (size_t i = 0; i < _size; ++i) {
            total += _data[i];
        }
        return total;
    }

    T min() const {
        T minimum = _data[0];
        for (size_t i = 1; i < _size; ++i) {
            if (_data[i] < minimum)
                minimum = _data[i];
        }
        return minimum;
    }

    T max() const {
        T maximum = _data[0];
        for (size_t i = 1; i < _size; ++i) {
            if (_data[i] > maximum)
                maximum = _data[i];
        }
        return maximum;
    }

    bool operator==(const MultiDimMatrix<T, 1>& other) const {
        return _data == other._data;
    }

    bool operator!=(const MultiDimMatrix<T, 1>& other) const {
        return !(*this == other);
    }
};

template <typename T, size_t N>
class MultiDimMatrix {
private:
    std::vector<MultiDimMatrix<T, N - 1>> _data;
    size_t _size;

public:
    MultiDimMatrix(size_t size, const std::vector<size_t>& dimensions) : _size(size), _data() {
        std::vector<size_t> arr(dimensions.begin() + 1, dimensions.end());
        _data.reserve(_size);
        for (size_t i = 0; i < _size; ++i) {
            _data.emplace_back(arr[0], arr);
        }
    }

    MultiDimMatrix<T, N - 1>& operator[](size_t index) {
        return _data[index];
    }

    const MultiDimMatrix<T, N - 1>& operator[](size_t index) const {
        return _data[index];
    }

    void fill(const T& value) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].fill(value);
        }
    }

    template <typename Func>
    void apply(Func func) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].apply(func);
        }
    }

    T sum() const {
        T total = T(0);
        for (size_t i = 0; i < _size; ++i) {
            total += _data[i].sum();
        }
        return total;
    }

    T min() const {
        T minimum = _data[0].min();
        for (size_t i = 1; i < _size; ++i) {
            T cur = _data[i].min();
            if (cur < minimum)
                minimum = cur;
        }
        return minimum;
    }

    T max() const {
        T maximum = _data[0].max();
        for (size_t i = 1; i < _size; ++i) {
            T cur = _data[i].max();
            if (cur > maximum)
                maximum = cur;
        }
        return maximum;
    }

    bool operator==(const MultiDimMatrix<T, N>& other) const {
        return _data == other._data;
    }

    bool operator!=(const MultiDimMatrix<T, N>& other) const {
        return !(*this == other);
    }
};

int main() {
    std::vector<size_t> dims = {3, 3, 3};
    MultiDimMatrix<int, 3> matrix(dims[0], dims);
    matrix.fill(0);
    matrix[0][0][0] = 1;
    matrix[1][1][1] = 14;
    matrix[2][2][2] = 27;
    std::cout << "matrix[0][0][0] = " << matrix[0][0][0] << std::endl;
    std::cout << "matrix[1][1][1] = " << matrix[1][1][1] << std::endl;
    std::cout << "matrix[2][2][2] = " << matrix[2][2][2] << std::endl;
    return 0;
}
