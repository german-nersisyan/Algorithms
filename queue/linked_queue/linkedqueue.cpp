#include <iostream>
#include <cassert>
#include <utility>

template <typename T>
struct Node {
    Node(T val, Node<T>* n = nullptr) : data(val), next(n) {}
    
    T data;
    Node<T>* next;
};

template <typename T>
class Queue {
    
public:
    
    virtual void enqueue(const T&) = 0;
    virtual void dequeue() = 0;
    virtual const T& front() const = 0;
    virtual std::size_t length() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
};

template <typename T>
class LinkedQueue : public Queue<T> {

public:

    LinkedQueue() : m_front(nullptr), m_rear(nullptr) {}
    
    LinkedQueue(const LinkedQueue& other) : m_front(nullptr), m_rear(nullptr)
    {
        std::cout << "Copy constructor" << std::endl;
        
        Node<T>* temp = other.m_front;
        while(temp) {
            enqueue(temp->data);
            temp = temp->next;
        }
    }
    
    LinkedQueue& operator=(const LinkedQueue& other)
    {
        std::cout << "Copy assignment" << std::endl;
        
        if(this == &other) {
            return *this;
        }
        
        clear();
        
        Node<T>* temp = other.m_front;
        while(temp) {
            enqueue(temp->data);
            temp = temp->next;
        }
        
        return *this;
    }
    
    LinkedQueue(LinkedQueue&& other) : m_front(other.m_front), m_rear(other.m_rear)
    {
        std::cout << "Move constructor" << std::endl;
        
        other.m_front = nullptr;
        other.m_rear = nullptr;
    }
    
    LinkedQueue& operator=(LinkedQueue&& other)
    {
        std::cout << "Move assignment" << std::endl;
        
        if(this == &other) {
            return *this;
        }
        
        clear();
        
        m_front = other.m_front;
        m_rear = other.m_rear;
        
        other.m_front = nullptr;
        other.m_rear = nullptr;
        
        return *this;
    }
    
    ~LinkedQueue()
    {
        std::cout << "Destructor" << std::endl;
        
        clear();
    }
    
    void enqueue(const T& val) override 
    {
        Node<T>* newNode = new Node<T>(val, nullptr);
        
        if(m_rear == nullptr) {
            m_front = m_rear = newNode;
        }
        else {
            m_rear->next = newNode;
            m_rear = newNode;
        }
    }
    
    void dequeue() override
    {
        if(empty()) {
            return;
        }
        Node<T>* temp = m_front;
        m_front = m_front->next;
        if(m_front == nullptr && m_rear != nullptr) {
            m_rear = nullptr;
        }
        delete temp;
    }
    
    const T& front() const override
    {
        assert(m_front != nullptr);
        return m_front->data;
    }
    
    bool empty() const override
    {
        return m_front == nullptr;
    }
    
    std::size_t length() const override
    {
        if(empty()) {
            return 0;
        }
        Node<T>* temp = m_front;
        std::size_t count = 0;
        while(temp != m_rear->next) {
            count++;
            temp = temp->next;
        }
        delete temp;
        return count;
    }
    
    void clear() override
    {
        while(!empty()) {
            dequeue();
        }
    }
    
    void swap(LinkedQueue& other)
    {
        std::cout << "Swap" << std::endl;
        
        Node<T>* temp_front = m_front;
        Node<T>* temp_rear = m_rear;
        
        m_front = other.m_front;
        m_rear = other.m_rear;
        
        other.m_front = temp_front;
        other.m_rear = temp_rear;
    }
    
private:

    Node<T>* m_front;
    Node<T>* m_rear;
    
};

int main()
{
    LinkedQueue<int> q;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(50);
    q.enqueue(15);
    q.enqueue(25);
    q.enqueue(60);
    
    std::cout << "Length: " << q.length() << std::endl;
    
    q.dequeue();
    
    std::cout << "Length after dequeue: " << q.length() << std::endl;
    
    std::cout << "Queue data: ";
    
    while(!q.empty()) {
        std::cout << q.front() << " ";
        q.dequeue();
    }
    
    std::cout << std::endl;
    
    std::cout << "Length after dequeue: " << q.length() << std::endl;
    
    LinkedQueue<int> q2;
    q2.enqueue(4);
    q2.enqueue(9);
    q2.enqueue(1);
    q2.enqueue(3);
    
    LinkedQueue<int> q3 = q2;
    
    LinkedQueue<int> q4;
    q4.enqueue(5);
    q4.enqueue(2);
    q4.enqueue(8);
    q4.enqueue(6);
    
    q4 = q2;
    
    LinkedQueue<int> q5 = std::move(q4);
    
    q2 = std::move(q3);
    
    LinkedQueue<int> q6;
    q6.enqueue(10);
    q6.enqueue(20);
    q6.enqueue(30);
    q6.enqueue(40);
    
    LinkedQueue<int> q7;
    q7.enqueue(10);
    q7.enqueue(20);
    
    std::cout << "Before swapping q6 length is " << q6.length() << ", q7 length is " << q7.length() << std::endl;
    q6.swap(q7);
    std::cout << "After swapping q6 length is " << q6.length() << ", q7 length is " << q7.length() << std::endl;
    return 0;
}