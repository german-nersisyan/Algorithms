#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {

public:

	virtual bool empty() const = 0;
	virtual bool full() const = 0;
	virtual std::size_t length() const = 0;
	virtual const T& front() const = 0;
	virtual void dequeue() = 0;
	virtual void enqueue(const T&) = 0;

};

template <typename T>
class ArrayQueue : public Queue<T> {

public:

	ArrayQueue() : m_capacity(10), m_size(0), m_front(0), m_rear(-1)
	{
		m_queue = new T[m_capacity];
	}

	ArrayQueue(const ArrayQueue& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_rear(other.m_rear)
	{
		m_queue = new T[m_capacity];
		for(std::size_t i = 0; i < m_capacity; i++) {
			m_queue[i] = other.m_queue[i];
		}
	}

	ArrayQueue(ArrayQueue&& other) : m_queue(other.m_queue), m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_rear(other.m_rear)
	{
		other.m_queue = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;
		other.m_front = 0;
		other.m_rear = -1;
	}

	ArrayQueue& operator=(const ArrayQueue& other) {
		if (this != &other) {
			delete[] m_queue;

			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_front = other.m_front;
			m_rear = other.m_rear;

			m_queue = new T[m_capacity];
			for (std::size_t i = 0; i < m_capacity; ++i) {
				m_queue[i] = other.m_queue[i];
			}
		}

		return *this;
	}
	
	ArrayQueue& operator=(ArrayQueue&& other) noexcept {
        if (this != &other) {
            delete[] m_queue;
            
            m_queue = other.m_queue;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_front = other.m_front;
            m_rear = other.m_rear;

            other.m_queue = nullptr;
            other.m_capacity = 0;
            other.m_size = 0;
            other.m_front = 0;
            other.m_rear = -1;
        }
        
        return *this;
    }

	~ArrayQueue()
	{
		delete[] m_queue;
	}

	bool empty() const override
	{
		return m_size == 0;
	}

	bool full() const override
	{
		return m_rear == static_cast<int>(m_capacity) - 1;
	}

	std::size_t length() const override
	{
		return m_size;
	}

	void enqueue(const T& val)
	{
		if(full()) {
			return;
		}

		m_queue[++m_rear] = val;
		m_size++;
	}

	void dequeue()
	{
		if(empty()) {
			return;
		}

		m_front++;
		m_size--;
	}

	const T& front() const override
	{
		if (empty())
			throw std::runtime_error("Queue is empty");
		return m_queue[m_front];
	}

	void swap(ArrayQueue& other)
	{
		T* temp_queue = m_queue;
		m_queue = other.m_queue;
		other.m_queue = temp_queue;

		std::size_t temp_capacity = m_capacity;
		m_capacity = other.m_capacity;
		other.m_capacity = temp_capacity;

		std::size_t temp_size = m_size;
		m_size = other.m_size;
		other.m_size = temp_size;

		int temp_front = m_front;
		m_front = other.m_front;
		other.m_front = temp_front;

		int temp_rear = m_rear;
		m_rear = other.m_rear;
		other.m_rear = temp_rear;
	}

private:

	T* m_queue;
	std::size_t m_capacity, m_size;
	int m_front, m_rear;

};

int main()
{
	ArrayQueue<int> q;
	q.enqueue(6);
	q.enqueue(3);
	q.enqueue(5);
	q.enqueue(8);

	std::cout << q.length() << std::endl;

	while(!q.empty()) {
		std::cout << q.front() << " ";
		q.dequeue();
	}

	std::cout << std::endl;
	std::cout << q.length() << std::endl;
	return 0;
}