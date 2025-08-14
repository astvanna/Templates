#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vector {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

private:
    size_type m_size;
    size_type m_capacity;
    value_type* m_data;

public:
    // Constructors & Destructor
    explicit Vector();
    explicit Vector(size_type size, const value_type& value = T());
    constexpr Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    constexpr Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    Vector& operator=(std::initializer_list<value_type> ilist);
    ~Vector();

    // Element access
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data();
    const T* data() const;

    // Capacity
    bool empty() const;
    size_type size() const;
    void reserve(size_type new_cap);
    size_type capacity() const;

    // Modifiers
    constexpr void clear() noexcept;
    constexpr void push_back(const T& value);
    constexpr void push_back(T&& value);
    
    template <typename... Args>
    reference emplace_back(Args&&... args);
    
    constexpr void pop_back();
    constexpr void resize(size_type count);
    constexpr void resize(size_type count, const T& value);
    constexpr void swap(Vector& other) noexcept;
};

// Non-member functions
template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs);

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs);

#include "vector.tpp"
#endif /* VECTOR_HPP */
