#include <stdexcept>

template<class T>
class MyArray {
    private:
        T* _arr;
        int _size;
        int _capacity;
    public:
        MyArray(): _size(0), _capacity(16), _arr(new T[_capacity]){}

        ~MyArray(){
            delete _arr;
        }

        int size(){
            return _size;
        }

        int capacity(){
            return _capacity;
        }

        bool is_empty(){
            return _size == 0;
        }

        T at(int index){
            if(index > _size) throw std::invalid_argument("index out of bounds");
            return _arr[index];
        }
};
