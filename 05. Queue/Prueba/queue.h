/*----------------------------------------------------------
 * Lab #3: Queues
 * Implementation of the Queue class.
 *
 * Date: 05-Oct-2025
 * Authors:
 *           A01803172 Giancarlo Moreno 
 *           A01277159 Leonardo González
 *           A01748498 Emiliano Díaz    
 *----------------------------------------------------------*/

 #pragma once
 
 #include <stdexcept>

 template<typename T>
 class Queue{
    private:
        T* circ_array;
        int _next; // Next available place for storing data
        int _last; // Oldest element of the queue
        int _size;
        int _capacity;

    public:
        Queue(int capacity){
            _next = 0;
            _last = 0;
            _size = 0;
            _capacity = capacity;
            circ_array = new T[capacity];
        }

        Queue(const Queue& other) = delete;
        Queue<T>& operator=(const Queue& other) = delete;

        ~Queue(){
            delete[] circ_array; 
        }
        
        int capacity() const{
            return _capacity;
        }	

        void clear(){
            _next = 0;
            _last = 0;
            _size = 0;
        }
        
        T dequeue(){
            if(is_empty()){
                throw std::underflow_error(
                    "The queue is empty."
                );
            }
            T value = circ_array[_last];
            _last = (_last + 1) % _capacity;
            _size --;
            return value;
        }
        
        void enqueue(T value){
            if(_size == _capacity || _capacity == 0){
                throw std::overflow_error(
                    "There's not enough space in this array."
                );
            }
            circ_array[_next] = value;
            _next = (_next + 1) % _capacity;
            _size ++;
        }
        
        bool is_empty() const{
            return _size == 0;
       }
       
        T peek() const{
            if(is_empty()){
                throw std::underflow_error(
                    "The queue is empty."
                );
            }
            return circ_array[_last];
        }

        int size() const{
            return _size;
        }
 };
