#include <iostream>

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
class CircularQueue : Queue<T> {

public:

	CircularQueue() : m_capacity(10), m_size(0)
	{
		m_front = m_rear = -1;
		m_queue = new T[m_capacity];
	}

	CircularQueue(const T& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_rear(other.m_rear)
    {
        m_queue = new T[m_capacity];
        for(std::size_t i = 0; i < m_capacity; i++) {
            m_queue[i] = other.m_queue[i];
        }
    }

	CircularQueue& operator=(const T& other)
    {
        if(this != &other) {
           delete[] m_queue;
           
           m_capacity = other.m_capacity;
           m_size = other.m_size;
           m_front = other.m_front;
           m_rear = other.m_rear;

           m_queue = new T[m_capacity];
           for(std::size_t i = 0; i < m_capacity; i++) {
               m_queue[i] = other.m_queue[i];
            }
        }

        return *this;
    }

	CircularQueue(T&& other) : m_queue(other.m_queue), m_capacity(other.m_capacity), m_size(other.m_size), m_front(other.m_front), m_rear(other.m_rear)
    {
        other.m_queue = nullptr;
        other.m_size = 0;
        other.m_front = other.m_rear = -1;
        other.m_capacity = 0;
    }

	CircularQueue& operator=(T&& other)
    {
        if(this != &other) {
            m_queue = other.m_queue;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_front = other.m_front;
            m_rear = other.m_rear;

            other.m_queue = nullptr;
            other.m_size = 0;
            other.m_front = other.m_rear = -1;
            other.m_capacity = 0;
        }

        return *this;
    }

	~CircularQueue()
	{
		delete[] m_queue;
	}

	bool empty() const override
	{
		return m_size == 0;
	}

	bool full() const override
	{
		return m_size == m_capacity;
	}

	const T& front() const override
	{
		if(empty()) {
			throw("runtime exception");
		}

		return m_queue[m_front];
	}

	void enqueue(const T& value) override
	{
		if(full()) {
			return;
		}

		if(empty()) {
			m_front = m_rear = 0;
		}
		else {
			m_rear = (m_rear + 1) % m_capacity;
		}

		m_queue[m_rear] = value;
		m_size++;
	}

	void dequeue() override
	{
		if(empty()) {
			return;
		}

		if(m_front == m_rear) {
			m_front = m_rear = -1;
		}
		else {
			m_front = (m_front + 1) % m_capacity;
		}

		m_size--;
	}

	std::size_t length() const override
	{
		return m_size;
	}

    void swap(CircularQueue& other)
    {
        T* temp_queue = m_queue;
        m_queue = other.m_queue;
        other.m_queue = temp_queue;

        int temp_front = m_front;
        m_front = other.m_front;
        other.m_front = temp_front;

        int temp_rear = m_rear;
        m_rear = other.m_rear;
        other.m_rear = temp_rear;

        std::size_t temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;

        std::size_t temp_capacity = m_capacity;
        m_capacity = other.m_capacity;
        other.m_capacity = temp_capacity;
    }

private:

	T* m_queue;
	int m_front, m_rear;
	std::size_t m_capacity, m_size;

};

int main()
{
	CircularQueue<int> q;
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