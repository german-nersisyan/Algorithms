#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {

public:

	virtual void push_front(const T&) = 0;
	virtual void push_back(const T&) = 0;
	virtual void pop_front() = 0;
	virtual void pop_back() = 0;
	virtual const T& front() const = 0;
	virtual const T& back() const = 0;
	virtual bool empty() const = 0;
	virtual std::size_t size() const = 0;

};

template <typename T>
class ArrayDeque : public Deque<T> {

public:

	ArrayDeque() : m_capacity(10), m_size(0), m_front(0), m_back(-1)
	{
		m_deque = new T[m_capacity];
	}

	ArrayDeque(const ArrayDeque& other) : m_capacity(other.m_capacity), m_front(other.m_front), m_back(other.m_back), m_size(other.m_size)
	{
		std::cout << "Copy constructor" << std::endl;
		m_deque = new T[m_capacity];
		for (int i = 0; i < m_capacity; ++i) {
			m_deque[i] = other.m_deque[i];
		}
	}

	ArrayDeque& operator=(const ArrayDeque& other)
	{
		std::cout << "Copy assignment" << std::endl;
		if (this != &other) {
            ArrayDeque temp(other);
            swap(temp);
        }
    
        return *this;
	}

	ArrayDeque(ArrayDeque&& other) noexcept : m_deque(nullptr), m_capacity(0), m_front(0), m_back(-1), m_size(0)
	{
		std::cout << "Move constructor" << std::endl;
		swap(other);
	}

	ArrayDeque& operator=(ArrayDeque&& other)
	{
        std::cout << "Move assignment" << std::endl;
        if (this != &other) {
            swap(other);
        }
		return *this;
	}

	~ArrayDeque()
	{
	    std::cout << "Destructor" << std::endl;
		delete[] m_deque;
	}

	bool empty() const override
	{
		return m_size == 0;
	}

	std::size_t size() const override
	{
		return m_size;
	}

	void push_back(const T& val) override
	{
		if(m_size == m_capacity) {
			resize(m_capacity * 2);
		}

		m_back = (m_back + 1) % m_capacity;
		m_deque[m_back] = val;
		++m_size;
	}

	void push_front(const T& val) override
	{
		if(m_size == m_capacity) {
			resize(m_capacity * 2);
		}

		m_front = (m_front - 1 + m_capacity) % m_capacity;
		m_deque[m_front] = val;
		++m_size;
	}

	void pop_back() override {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		m_back = (m_back - 1 + m_capacity) % m_capacity;
		--m_size;
	}

	void pop_front() override {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		m_front = (m_front + 1) % m_capacity;
		--m_size;
	}

	const T& back() const override {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return m_deque[m_back];
	}

	const T& front() const override {
		if (empty()) {
			throw std::out_of_range("Deque is empty");
		}
		return m_deque[m_front];
	}

	void swap(ArrayDeque& other)
	{
		T* temp_arr = m_deque;
		m_deque = other.m_deque;
		other.m_deque = temp_arr;

		int temp_capacity = m_capacity;
		m_capacity = other.m_capacity;
		other.m_capacity = temp_capacity;

		int temp_front = m_front;
		m_front = other.m_front;
		other.m_front = temp_front;

		int temp_back = m_back;
		m_back = other.m_back;
		other.m_back = temp_back;

		int temp_size = m_size;
		m_size = other.m_size;
		other.m_size = temp_size;
	}

private:

	T* m_deque;
	int m_front, m_back;
	std::size_t m_capacity, m_size;

	void resize(int new_capacity)
	{
		T* new_arr = new T[new_capacity];
		for(int i = 0; i < m_size; i++) {
			new_arr[i] = m_deque[(m_front + i) % m_capacity];
		}

		delete[] m_deque;

		m_deque = new_arr;
		m_capacity = new_capacity;
		m_front = 0;
		m_back = m_size - 1;
	}

};

int main()
{
	ArrayDeque<int> dq1;
    dq1.push_back(1);
    dq1.push_back(2);
    dq1.push_front(0);
    dq1.push_front(-1);
    dq1.push_back(5);
	
	while(!dq1.empty()) {
	    std::cout << dq1.front() << " ";
	    dq1.pop_front();
	}
	std::cout << std::endl;
	
    dq1.push_back(5);
    dq1.push_back(-7);
    dq1.push_front(3);
    dq1.push_front(0);
    dq1.push_back(-4);
	
	ArrayDeque<int> dq2(dq1);
	
	ArrayDeque<int> dq3;
    dq3 = dq1;
    
    ArrayDeque<int> dq4;
    dq4.push_back(100);
    dq4.push_back(200);
    
    ArrayDeque<int> dq5(std::move(dq4));
    
    ArrayDeque<int> dq6;
    dq6 = std::move(dq5);
	
	return 0;
}