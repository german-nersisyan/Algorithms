#include <iostream>
#include <cassert>

template <typename T>
struct Node {
    Node(const T& v, Node<T>* n = nullptr) : val(v), next(n) {}
    
    T val;
    Node<T>* next;
};

template <typename T>
class Stack {
    
public:

    virtual void push(const T&) = 0;
    virtual void pop() = 0;
    virtual void clear() = 0;
    virtual const T& top() const = 0;
    virtual bool empty() const = 0;
    
};

template <typename T>
class LinkedStack : public Stack<T> {

public:

    LinkedStack() : m_top(nullptr) {}
    
    LinkedStack(const LinkedStack& other) : m_top(nullptr)
    {
        std::cout << "Copy constructor" << std::endl;
        if(!other.m_top) {
            return;
        }
        
        m_top = new Node<T>(other.m_top->val);
        Node<T>* current = m_top;
        Node<T>* otherNode = other.m_top->next;
        
        while(otherNode) {
            current->next = new Node<T>(otherNode->val);
            current = current->next;
            otherNode = otherNode->next;
        }
    }
    
    LinkedStack& operator=(const LinkedStack& other)
    {
        std::cout << "Copy assignment" << std::endl;
        if(this == &other) {
            return *this;
        }
        
        clear();
        
        if(!other.m_top) {
            m_top = nullptr;
            return *this;
        }
        
        m_top = new Node<T>(other.m_top->val);
        Node<T>* current = m_top;
        Node<T>* otherNode = other.m_top->next;
        
        while(otherNode) {
            current->next = new Node<T>(otherNode->val);
            current = current->next;
            otherNode = otherNode->next;
        }
        
        return *this;
    }
    
    LinkedStack(LinkedStack&& other) : m_top(other.m_top)
    {
        std::cout << "Move constructor" << std::endl;
        other.m_top = nullptr;
    }
    
    LinkedStack& operator=(LinkedStack&& other)
    {
        std::cout << "Move assignment" << std::endl;
        if(this == &other) {
            return *this;
        }
        
        clear();
        m_top = other.m_top;
        other.m_top = nullptr;
        
        return *this;
    }
    
    ~LinkedStack()
    {
        std::cout << "Destructor" << std::endl;
        clear();
    }
    
    virtual bool empty() const override
    {
        return m_top == nullptr;
    }
    
    virtual const T& top() const override
    {
        assert(m_top != nullptr);
        return m_top->val;
    }
    
    virtual void pop() override
    {
        if(empty()) {
            return;
        }
        Node<T>* temp = m_top;
        m_top = m_top->next;
        delete temp;
    }
    
    virtual void push(const T& newVal) override
    {
        m_top = new Node<T>(newVal, m_top);
    }
    
    virtual void clear() override
    {
        while(!empty()) {
            pop();
        }
    }

    void swap(LinkedStack& other)
    {
        Node<T>* temp = m_top;
        m_top = other.m_top;
        other.m_top = temp;
    }
    
private:

    Node<T>* m_top;
    
};

int main()
{
    LinkedStack<int> st;
    st.push(7);
    st.push(4);
    st.push(5);
    st.push(9);
    
    while(!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    
    std::cout << std::endl;
    
    LinkedStack<int> st1;
    st.push(2);
    st.push(6);
    st.push(1);
    st.push(8);
    
    LinkedStack<int> st2(st1);
    
    LinkedStack<int> st3;
    st3 = st2;
    
    LinkedStack<int> st4(std::move(st3));
    
    LinkedStack<int> st5;
    st5 = std::move(st4);
    return 0;
}