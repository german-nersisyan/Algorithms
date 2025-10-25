#include <iostream>
#include <stdexcept>

template <typename T>
class List {
    
public:

    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;
    virtual void clear() = 0;
    virtual void push_back(const T&) = 0;
    virtual void push_front(const T&) = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual const T& back() const = 0;
    virtual const T& front() const = 0;

};

template <typename T>
struct Node {
    
    Node(const T& val) : data(val), next(nullptr) {}
    
    T data;
    Node* next;
    
};

template <typename T>
class CyclicList : public List<T> {
    
public:

    CyclicList() : m_tail(nullptr), m_size(0) {}
    
    CyclicList(const CyclicList& other) : m_tail(nullptr), m_size(0)
    {
        std::cout << "Copy constructor" << std::endl;
        
        if (!other.empty()) {
            Node<T>* current = other.m_tail->next;
            do {
                push_back(current->data);
                current = current->next;
            } while (current != other.m_tail->next);
        }
    }
    
    CyclicList& operator=(const CyclicList& other)
    {
        std::cout << "Copy assignment" << std::endl;
        
        if (this == &other) {
            return *this;
        }
        
        clear();
        
        if (!other.m_tail) {
            return *this;
        }

        Node<T>* current = other.m_tail->next;
        do {
            push_back(current->data);
            current = current->next;
        } while (current != other.m_tail->next);
        return *this;
    }
    
    CyclicList(CyclicList&& other) : m_tail(nullptr), m_size(0)
    {
        std::cout << "Move constructor" << std::endl;
        
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    
    CyclicList& operator=(CyclicList&& other)
    {
        std::cout << "Move assignment" << std::endl;
        
        if (this == &other) {
            return *this;
        }

        clear();
        
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_tail = nullptr;
        other.m_size = 0;
        return *this;
    }
    
    ~CyclicList() 
    {
        clear();
    }
    
    bool empty() const override
    {
        return m_tail == nullptr;
    }
    
    std::size_t size() const override
    {
        return m_size;
    }
    
    void clear() override
    {
        if (empty()) return;

        Node<T>* head = m_tail->next;
        m_tail->next = nullptr;

        Node<T>* current = head;
        while(current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }

        m_tail = nullptr;
        m_size = 0;
    }
    
    void push_back(const T& val) override
    {
        Node<T>* new_node = new Node(val);
        
        if(empty()) {
            m_tail = new_node;
            m_tail->next = m_tail;
        }
        else {
            new_node->next = m_tail->next;
            m_tail->next = new_node;
            m_tail = new_node;
        }
        
        ++m_size;
    }
    
    void push_front(const T& val) override
    {
        Node<T>* new_node = new Node(val);
        
        if(empty()) {
            m_tail = new_node;
            m_tail->next = m_tail;
        }
        else {
            new_node->next = m_tail->next;
            m_tail->next = new_node;
        }
        
        ++m_size;
    }
    
    void pop_back() override
    {
        if(empty()) {
            return;
        }
        
        Node<T>* head = m_tail->next;
        if(head == m_tail) {
            delete m_tail;
            m_tail = nullptr;
        }
        else {
            Node<T>* current = head;
            while(current->next != m_tail) {
                current = current->next;
            }
            
            current->next = m_tail->next;
            delete m_tail;
            m_tail = current;
        }
        
        --m_size;
    }
    
    void pop_front() override
    {
        if(empty()) {
            return;
        }
        
        Node<T>* head = m_tail->next;
        if(head == m_tail) {
            delete head;
            m_tail = nullptr;
        }
        else {
            m_tail->next = head->next;
            delete head;
        }
        
        --m_size;
    }
    
    const T& back() const override
    {
        if (empty()) {
			throw std::runtime_error("List is empty");
        }
        
        return m_tail->data;
    }
    
    const T& front() const override
    {
        if (empty()) {
			throw std::runtime_error("List is empty");
        }
        
        return m_tail->next->data;
    }
    
    void swap(CyclicList& other)
    {
        Node<T>* temp_tail = m_tail;
        m_tail = other.m_tail;
        other.m_tail = temp_tail;
        
        std::size_t temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;
    }

private:

    Node<T>* m_tail;
    std::size_t m_size;

};

template <typename T>
void swap(CyclicList<T>& a, CyclicList<T>& b)
{
    a.swap(b);
}

int main()
{
    CyclicList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    CyclicList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    
    swap(list1, list2);
    
    while(!list1.empty()) {
        std::cout << list1.front() << " ";
        list1.pop_front();
    }
    std::cout << std::endl;
    
    while(!list2.empty()) {
        std::cout << list2.front() << " ";
        list2.pop_front();
    }
    std::cout << std::endl;
    
    CyclicList<int> list1_1 = list1;
    
    CyclicList<int> list3;
    list3.push_back(10);
    list3.push_back(20);
    
    list3 = list1;
    
    CyclicList<int> list4 = std::move(list1);
    
    CyclicList<int> list5;
    list5.push_back(100);
    list5.push_back(200);
    
    list5 = std::move(list4);
    return 0;
}