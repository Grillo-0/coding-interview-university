#pragma once

#include <stdexcept>

template<typename T>
struct Node{
    T _value;
    struct Node<T>* _next;

    Node(T value): _value(value), _next(nullptr){}; 
    Node(T value, struct Node<T>* next): _value(value), _next(next){}; 
};

template<typename T>
class LinkedList{
    private:
        struct Node<T>* _head;
        struct Node<T>* _tail;
        int _size;
    public:
        LinkedList(): _head(nullptr), _tail(nullptr), _size(0){};

        int size(){
            return _size;
        }

        bool empty(){
            return _size == 0;
        }

        T value_at(int index){
            if(index < 0) throw std::invalid_argument("index cannot be negative");
            if(index == _size-1) return _tail->_value;
            struct Node<T>* tmp = _head;
            for(int i=0; i<index; i++){ 
                tmp = tmp->_next;  
                if(tmp == nullptr) throw std::runtime_error("index out of range");
            }
            return tmp->_value;
        }

        T operator[](int index){
            return value_at(index);
        }

        void push_front(T value){
            _head = new Node<T>(value, _head);
            _size++;
            if(_size == 1){
                _tail = _head;
            }
        }

        void pop_front(){
            struct Node<T>* tmp = _head;
            _head = _head->_next;
            delete tmp;
            _size--;
        }

        void push_back(T value){
            if(_size < 1){
                push_front(value);
                return;
            }
            _tail->_next = new Node<T>(value);
            _tail = _tail->_next;
            _size++;
        }

        void pop_back(){
            if(_size == 1){
                pop_front();
                return;
            }
            struct Node<T>* tmp = _head;
            while(tmp->_next != _tail) tmp = tmp->_next;
            delete tmp->_next;
            tmp->_next = nullptr;
            _tail = tmp;
            _size--;
        }

        T front(){
            return this->value_at(0) ;
        }

        T back(){
            return this->value_at(_size-1);
        }

        void insert(int index, T value){
            if(index >= _size || index < 0) throw std::invalid_argument("index out of range");
            if(index == 0){
                push_front(value);
                return;
            }
            struct Node<T>* tmp = _head;
            struct Node<T>* prev;
            for(int i=0; i<index; i++){
                prev = tmp;
                tmp = tmp->_next;
            }
            tmp = new Node<T>(value, tmp);
            prev->_next = tmp;
            _size++;
        }

        void erase(int index){
            if(index >= _size || index < 0) throw std::invalid_argument("index out of range");
            if(index == 0){
                pop_front();
                return;
            }

            struct Node<T>* tmp = _head;
            struct Node<T>* prev = _head;
            for(int i=0; i<index; i++){
                prev = tmp;
                tmp = tmp->_next;
            }
            prev->_next = tmp->_next;
            delete tmp;
            _size--;
        }

        T value_n_from_end(int n){
            return value_at(_size-n-1);
        }

        void reverse(){
            struct Node<T>* curr = _head;
            struct Node<T>* prev = nullptr;
            struct Node<T>* next = nullptr;
            while(curr != nullptr){
                next = curr->_next;
                curr->_next = prev;
                prev = curr;
                curr = next;
            }
            _tail = _head;
            _head = prev;
        }

        int remove_value(int value){
            if(_head->_value == value){
                pop_front();
                return 0;
            }

            struct Node<T>* tmp = _head;
            struct Node<T>* prev = nullptr;
            while(tmp != nullptr && tmp->_value != value){ 
                prev = tmp;
                tmp = tmp->_next;
            }
            if(tmp == nullptr) return -1;
            prev->_next = tmp->_next;
            delete tmp;
            if(prev->_next == nullptr) _tail = prev;
            _size--;
            return 0;
        }

};
