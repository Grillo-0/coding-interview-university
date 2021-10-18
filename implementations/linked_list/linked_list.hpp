#pragma once

#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T _value;
        struct Node* _next;

        Node(T value)
            : _value(value)
            , _next(nullptr) {};
        Node(T value, struct Node* next)
            : _value(value)
            , _next(next) {};
    };

    struct Node* _head;
    struct Node* _tail;
    int _size;

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = struct Node;
        using pointer = struct Node*;
        using reference = struct Node&;

        Iterator(pointer ptr)
            : _ptr(ptr) {};

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        Iterator& operator++()
        {
            _ptr = _ptr->_next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b)
        {
            return a._ptr == b._ptr;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b)
        {
            return a._ptr != b._ptr;
        }

    private:
        pointer _ptr;
    };

public:
    Iterator begin() { return Iterator(_head); }

    Iterator end()
    {
        if (_size == 0) {
            return Iterator(_tail);
        }
        return Iterator(_tail->_next);
    }

    LinkedList();

    int size();

    bool empty();

    T value_at(int index);

    T operator[](int index);

    void push_front(T value);

    void pop_front();

    void push_back(T value);

    void pop_back();

    T front();

    T back();

    void insert(int index, T value);

    void erase(int index);

    T value_n_from_end(int n);

    void reverse();

    int remove_value(int value);
};

template <typename T>
LinkedList<T>::LinkedList()
    : _head(nullptr)
    , _tail(nullptr)
    , _size(0) {};

template <typename T>
int LinkedList<T>::size()
{
    return _size;
}

template <typename T>
bool LinkedList<T>::empty()
{
    return _size == 0;
}

template <typename T>
T LinkedList<T>::value_at(int index)
{
    if (index < 0)
        throw std::invalid_argument("index cannot be negative");
    if (index == _size - 1)
        return _tail->_value;
    struct Node* tmp = _head;
    for (int i = 0; i < index; i++) {
        tmp = tmp->_next;
        if (tmp == nullptr)
            throw std::runtime_error("index out of range");
    }
    return tmp->_value;
}

template <typename T>
T LinkedList<T>::operator[](int index)
{
    return value_at(index);
}

template <typename T>
void LinkedList<T>::push_front(T value)
{
    _head = new Node(value, _head);
    _size++;
    if (_size == 1) {
        _tail = _head;
    }
}

template <typename T>
void LinkedList<T>::pop_front()
{
    struct Node* tmp = _head;
    _head = _head->_next;
    delete tmp;
    _size--;
}

template <typename T>
void LinkedList<T>::push_back(T value)
{
    if (_size < 1) {
        push_front(value);
        return;
    }
    _tail->_next = new Node(value);
    _tail = _tail->_next;
    _size++;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if (_size == 1) {
        pop_front();
        return;
    }
    struct Node* tmp = _head;
    while (tmp->_next != _tail)
        tmp = tmp->_next;
    delete tmp->_next;
    tmp->_next = nullptr;
    _tail = tmp;
    _size--;
}

template <typename T>
T LinkedList<T>::front()
{
    return this->value_at(0);
}

template <typename T>
T LinkedList<T>::back()
{
    return this->value_at(_size - 1);
}

template <typename T>
void LinkedList<T>::insert(int index, T value)
{
    if (index >= _size || index < 0)
        throw std::invalid_argument("index out of range");
    if (index == 0) {
        push_front(value);
        return;
    }
    struct Node* tmp = _head;
    struct Node* prev;
    for (int i = 0; i < index; i++) {
        prev = tmp;
        tmp = tmp->_next;
    }
    tmp = new Node(value, tmp);
    prev->_next = tmp;
    _size++;
}

template <typename T>
void LinkedList<T>::erase(int index)
{
    if (index >= _size || index < 0)
        throw std::invalid_argument("index out of range");
    if (index == 0) {
        pop_front();
        return;
    }

    struct Node* tmp = _head;
    struct Node* prev = _head;
    for (int i = 0; i < index; i++) {
        prev = tmp;
        tmp = tmp->_next;
    }
    prev->_next = tmp->_next;
    delete tmp;
    _size--;
}

template <typename T>
T LinkedList<T>::value_n_from_end(int n)
{
    return value_at(_size - n - 1);
}

template <typename T>
void LinkedList<T>::reverse()
{
    struct Node* curr = _head;
    struct Node* prev = nullptr;
    struct Node* next = nullptr;
    while (curr != nullptr) {
        next = curr->_next;
        curr->_next = prev;
        prev = curr;
        curr = next;
    }
    _tail = _head;
    _head = prev;
}

template <typename T>
int LinkedList<T>::remove_value(int value)
{
    if (_head->_value == value) {
        pop_front();
        return 0;
    }

    struct Node* tmp = _head;
    struct Node* prev = nullptr;
    while (tmp != nullptr && tmp->_value != value) {
        prev = tmp;
        tmp = tmp->_next;
    }
    if (tmp == nullptr)
        return -1;
    prev->_next = tmp->_next;
    delete tmp;
    if (prev->_next == nullptr)
        _tail = prev;
    _size--;
    return 0;
}
