#pragma once

#include <iostream>
#include <exception>

namespace
{
    template <typename T>
    void mySwap(T& a, T& b)
    {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }
}

static short INITIAL_CAPACITY = 4;

template <typename T>
class KPriorityQueue
{
    struct Node
    {
        T item;
        int priority;

        Node() : item(T()), priority(0) {}
        Node(const T& item, int priority) : item(item), priority(priority) {}
    };

    Node* data;
    size_t capacity;
    size_t size;
    size_t k;
    unsigned get; 
    unsigned put; 

    void resize();

    void moveFrom(KPriorityQueue<T>&& other);
    void copyFrom(const KPriorityQueue<T>& other);
    void free();

public:
    KPriorityQueue(size_t k);

    KPriorityQueue(const KPriorityQueue<T>& other);
    KPriorityQueue<T>& operator=(const KPriorityQueue<T>& other);

    KPriorityQueue(KPriorityQueue<T>&& other);
    KPriorityQueue<T>& operator=(KPriorityQueue<T>&& other);

    void push(const T& obj, int priority);
    void pop();

    const T& peek() const;
    bool isEmpty() const;

    ~KPriorityQueue();
};

template <typename T>
KPriorityQueue<T>::KPriorityQueue(size_t k):  k(k), capacity(INITIAL_CAPACITY), size(0), get(0), put(0)
{
    data = new Node[capacity];
}

template <typename T>
void KPriorityQueue<T>::push(const T& obj, int priority)
{
    if (priority < 0 || priority >= k)
        throw std::out_of_range("Invalid priority value!");

    if (size == capacity)
        resize();

    data[put] = Node(obj, priority);
    put = (put + 1) % capacity;
    size++;

    int index = size - 1;
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (data[index].priority > data[parentIndex].priority ||
            (data[index].priority == data[parentIndex].priority && index < parentIndex))
        {
            mySwap(data[index], data[parentIndex]);
            index = parentIndex;
        }
        else
            break;
    }
}

template <typename T>
void KPriorityQueue<T>::pop()
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");

    mySwap(data[get], data[(get + size - 1) % capacity]);
    size--;

    int index = 0;
    while (index < size)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size &&
            (data[left].priority > data[largest].priority || (data[left].priority == data[largest].priority && left < largest)))
            largest = left;

        if (right < size &&
            (data[right].priority > data[largest].priority || (data[right].priority == data[largest].priority && right < largest)))
            largest = right;

        if (largest != index)
        {
            mySwap(data[index], data[largest]);
            index = largest;
        }
        else
            break;
    }

    get = (get + 1) % capacity;
}

template <typename T>
bool KPriorityQueue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
const T& KPriorityQueue<T>::peek() const
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");

    return data[get].item;
}

template <typename T>
void KPriorityQueue<T>::resize()
{
    Node* resizedData = new Node[capacity * 2];
    for (size_t i = 0; i < size; i++)
    {
        resizedData[i] = data[(get + i) % capacity];
    }
    capacity *= 2;
    delete[] data;
    data = resizedData;
    get = 0;
    put = size;
}

template <typename T>
void KPriorityQueue<T>::copyFrom(const KPriorityQueue<T>& other)
{
    data = new Node[other.capacity];
    for (int i = 0; i < other.size; i++)
        data[i] = other.data[(other.get + i) % other.capacity];

    size = other.size;
    capacity = other.capacity;
    k = other.k;
    get = 0;
    put = size;
}

template <typename T>
void KPriorityQueue<T>::moveFrom(KPriorityQueue<T>&& other)
{
    size = other.size;
    capacity = other.capacity;
    k = other.k;
    data = other.data;
    other.data = nullptr;
    get = other.get;
    put = other.put;
}

template <typename T>
void KPriorityQueue<T>::free()
{
    delete[] data;
}

template <typename T>
KPriorityQueue<T>::KPriorityQueue(const KPriorityQueue<T>& other)
{
    copyFrom(other);
}

template <typename T>
KPriorityQueue<T>& KPriorityQueue<T>::operator=(const KPriorityQueue<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
KPriorityQueue<T>::KPriorityQueue(KPriorityQueue<T>&& other)
{
    moveFrom(std::move(other));
}

template <typename T>
KPriorityQueue<T>& KPriorityQueue<T>::operator=(KPriorityQueue<T>&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
KPriorityQueue<T>::~KPriorityQueue()
{
    free();
}
