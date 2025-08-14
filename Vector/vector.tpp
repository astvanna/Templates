#include <vector.hpp>
#include <stdexcept>
#include <utility>
#include <initializer_list>

// Constructors
template <typename T>
Vector<T>::Vector() : m_size{0}, m_capacity{0}, m_data{nullptr} {}

template <typename T>
Vector<T>::Vector(typename Vector<T>::size_type size, const typename Vector<T>::value_type& value)
    : m_size{size}, m_capacity{size * 2}, m_data{new value_type[m_capacity]} {
    for (typename Vector<T>::size_type i = 0; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template <typename T>
constexpr Vector<T>::Vector(const Vector& other)
    : m_size{other.m_size}, m_capacity{other.m_capacity}, m_data{new value_type[m_capacity]} {
    for (typename Vector<T>::size_type i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : m_size{other.m_size}, m_capacity{other.m_capacity}, m_data{other.m_data} {
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

template <typename T>
constexpr Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) return *this;
    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new value_type[m_capacity];
    for (typename Vector<T>::size_type i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (this == &other) return *this;
    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<value_type> ilist) {
    delete[] m_data;
    m_size = ilist.size();
    m_capacity = m_size * 2;
    m_data = new value_type[m_capacity];
    
    typename Vector<T>::size_type i = 0;
    for (const auto& elem : ilist) {
        m_data[i++] = elem;
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] m_data;
    m_size = 0;
    m_capacity = 0;
    m_data = nullptr;
}

// Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(typename Vector<T>::size_type pos) {
    if (pos >= m_size) throw std::out_of_range{"Out of range"};
    return m_data[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(typename Vector<T>::size_type pos) const {
    if (pos >= m_size) throw std::out_of_range{"Out of range"};
    return m_data[pos];
}

template <typename T>
constexpr typename Vector<T>::reference Vector<T>::operator[](typename Vector<T>::size_type pos) {
    return m_data[pos];
}

template <typename T>
constexpr typename Vector<T>::const_reference Vector<T>::operator[](typename Vector<T>::size_type pos) const {
    return m_data[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return m_data[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return m_data[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return m_data[m_size - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return m_data[m_size - 1];
}

template <typename T>
T* Vector<T>::data() {
    return m_data;
}

template <typename T>
const T* Vector<T>::data() const {
    return m_data;
}

// Capacity
template <typename T>
bool Vector<T>::empty() const {
    return m_size == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
    return m_size;
}

template <typename T>
void Vector<T>::reserve(typename Vector<T>::size_type new_cap) {
    if (new_cap <= m_capacity) return;
    value_type* new_data = new value_type[new_cap];
    for (typename Vector<T>::size_type i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_cap;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
    return m_capacity;
}

// Modifiers
template <typename T>
constexpr void Vector<T>::clear() noexcept {
    m_size = 0;
}

template <typename T>
constexpr void Vector<T>::push_back(const T& value) {
    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    m_data[m_size] = value;
    ++m_size;
}

template <typename T>
constexpr void Vector<T>::push_back(T&& value) {
    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    m_data[m_size] = std::move(value);
    ++m_size;
}

template <typename T>
template <typename... Args>
typename Vector<T>::reference Vector<T>::emplace_back(Args&&... args) {
    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    m_data[m_size] = value_type{std::forward<Args>(args)...};
    ++m_size;
    return m_data[m_size - 1];
}

template <typename T>
constexpr void Vector<T>::pop_back() {
    --m_size;
}

template <typename T>
constexpr void Vector<T>::resize(typename Vector<T>::size_type count) {
    if (m_size == count) return;
    else if (count >= m_capacity) reserve(count * 2 + 1);
    m_size = count;
}

template <typename T>
constexpr void Vector<T>::resize(typename Vector<T>::size_type count, const T& value) {
    if (m_size == count) return;
    else if (m_size > count) {
        m_size = count;
    } else {
        if (count >= m_capacity) reserve(count * 2 + 1);
        for (typename Vector<T>::size_type i = m_size; i < count; ++i) {
            m_data[i] = value;
        }
        m_size = count;
    }
}

template <typename T>
constexpr void Vector<T>::swap(Vector& other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
}

// Non-member functions
template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    std::size_t minSize = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    for (std::size_t i = 0; i < minSize; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (lhs[i] > rhs[i]) return false;
    }
    return lhs.size() < rhs.size();
}

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}
