// #pragma once

// #include <stdexcept>


// template<typename T>
// class Queue{
//     private:
//         T* circular_a;
//         int _capacity;
//         int _last; // Value that has been the longest
//         int _next; // New value 
//         int _size;

//     public:
//         Queue(int capacity){
//             _capacity = capacity;
//             _next = 0;
//             _last = -1;
//             _size = 0;
//             circular_a = new T[capacity];
//         }

//         ~Queue(){
//             delete[] circular_a; 
//         }
//         Queue(const Queue& other) = delete;
//         Queue<T>& operator=(const Queue& other) = delete;


//         int capacity() const{
//             return _capacity;
//         }


//         void clear(){
//             _next = 0;
//             _last = -1;
//             _size = 0;
//         }

//         T dequeue(){
//             if(is_empty()){
//                 throw std::underflow_error(
//                     "The queue is empty!"
//                 );
//             }
//             T value = circular_a[_last];
//             _last = (_last + 1) % _capacity;
//             _size --;
//             return value;
//         }

//         void enqueue(T value){
//             if(_size == _capacity){
//                 throw std::overflow_error(
//                     "Insufficient space."
//                 );
//             }
//             if(_capacity == 0){
//                 throw std::overflow_error("Insufficient space."
//                 );
//             }

//             if(is_empty()){
//                 _last = _next;
//             }

//             circular_a[_next] = value;
//             _next = (_next + 1) % _capacity;
//             _size ++;
//             }


//         bool is_empty() const{
//             if(_size == 0 || _capacity == 0){
//                 return true;
//             }else{
//                 return false;
//             }
//         }

//         T peek() const{
//             if(is_empty()){
//                 throw std::underflow_error(
//                     "The queue is empty!"
//                 );
//             }
//             return circular_a[_last];
//         }

//         int size() const{
//             return _size;
//         }

// };


#pragma once
#include <stdexcept>

template<typename T>
class Queue{
private:
    T* circular_a;
    int _capacity;
    int _next;   // Donde insertamos
    int _last;   // Donde sacamos  
    int _size;   // Contador de elementos

public:
    Queue(int capacity){
        if(capacity < 0) {
            throw std::invalid_argument("Capacity cannot be negative");
        }
        _capacity = capacity;  // ✅ QUITAR el +1 - usamos capacidad real
        _next = 0;
        _last = 0;
        _size = 0;
        
        // Manejar capacidad 0
        if(capacity == 0) {
            std::overflow_error(
                "Capacity 0."
            );
        } else {
            circular_a = new T[_capacity];
        }
    }

    ~Queue(){
        if(_capacity > 0) {
            delete[] circular_a;
        }
    }
    
    Queue(const Queue& other) = delete;
    Queue<T>& operator=(const Queue& other) = delete;

    int capacity() const { 
        return _capacity;  // ✅ Capacidad real (sin -1)
    }

    void clear(){
        _next = 0;
        _last = 0;
        _size = 0;
    }

    T dequeue(){
        if(is_empty()){
            throw std::underflow_error("The queue is empty!");
        }
        T value = circular_a[_last];
        _last = (_last + 1) % _capacity;
        _size--;  // ✅ MOVER antes del return
        return value;
    }

    void enqueue(T value){
        // Caso especial para capacidad 0
        if(_capacity == 0) {
            throw std::overflow_error("Insufficient space.");
        }
        
        // ✅ CONDICIÓN CORRECTA con contador
        if(is_full()){
            throw std::overflow_error("Insufficient space.");
        }
        
        circular_a[_next] = value;
        _next = (_next + 1) % _capacity;
        _size++;
    }

    bool is_empty() const {
        // ✅ Usar el contador en lugar de comparar índices
        return _size == 0;
    }

    bool is_full() const {
        // ✅ CONDICIÓN SIMPLE con contador
        return _size == _capacity;
    }

    T peek() const {
        if(is_empty()){
            throw std::underflow_error("The queue is empty!");
        }
        return circular_a[_last];
    }

    int size() const {
        return _size;  // ✅ Directo del contador
    }
};