#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class Stack {
    
public:

    virtual void pop() = 0;
    virtual void push(const T&) = 0;
    virtual const T& top() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual size_t stacksize() const = 0;
    
};

template <typename T>
class ArrayStack : public Stack<T> {
    
private:
    
    T* arr;
    size_t size;
    size_t capacity;
    
    void resize()
    {
        capacity *= 2;
        T* newarr = new T[capacity];
        for(int i = 0; i < size; i++) {
            newarr[i] = std::move(arr[i]);
        }
        
        
        delete[] arr;
        arr = newarr;
    }
    
public:

    ArrayStack() : size(0), capacity(1)
    {
        arr = new T[capacity];
    }
    
    ArrayStack(const ArrayStack& other) : capacity(other.capacity), size(other.size)
    {
        arr = new T[capacity];
        for(int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    
    ArrayStack& operator=(const ArrayStack& other) 
    {
        if(this == &other) {
            return *this;
        }
        
        delete[] arr;
        
        capacity = other.capacity;
        size = other.size;
        arr = new T[capacity];
        for(int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        
        return *this;
    }
    
    ArrayStack(ArrayStack&& other) : arr(other.arr), capacity(other.capacity), size(other.size) 
    {
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    
    ArrayStack& operator=(ArrayStack&& other) 
    {
        if(this == &other) {
            return *this;
        }
        
        delete[] arr;
        arr = other.arr;
        capacity = other.capacity;
        size = other.size;
        
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
        
        return *this;
    }
    
    ~ArrayStack()
    {
        delete[] arr;
    }
    
    virtual const T& top() const override
    {
        if(empty()) throw std::out_of_range("Stack is empty");
        return arr[size - 1];
    }
    
    virtual bool empty() const override
    {
        return size == 0;
    }
    
    virtual void pop() override
    {
        if(!empty()) {
            --size;
        }
    }
    
    virtual void push(const T& value) override
    {
        if(size == capacity) {
            resize();
        }
        
        arr[size++] = value;
    }
    
    virtual void clear() override {
        size = 0;
    };
    
    virtual size_t stacksize() const override
    {
        return size;
    }

    void swap(ArrayStack& other)
    {
        T* temp_arr = arr;
        arr = other.arr;
        other.arr = temp_arr;

        size_t temp_size = size;
        size = other.size;
        other.size = temp_size;

        size_t temp_capacity = capacity;
        capacity = other.capacity;
        other.capacity = temp_capacity;
    }
};

int main()
{
    ArrayStack<int> a;
    
    a.push(5);
    a.push(6);
    a.push(7);
    a.push(8);
    
    std::cout << "size = " << a.stacksize() << std::endl;
    while(!a.empty()) {
        std::cout << a.top() << " ";
        a.pop();
    }
    std::cout << std::endl;
    std::cout << "size = " << a.stacksize() << std::endl;
    return 0;
}