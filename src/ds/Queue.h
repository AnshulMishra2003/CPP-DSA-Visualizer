#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdexcept>

template <typename T>
class Queue
{
public:
    Queue() : maxSize(100), frontIdx(0), rearIdx(-1), count(0) {}
    
    explicit Queue(int size) : maxSize(size), frontIdx(0), rearIdx(-1), count(0) {}
    
    void enqueue(T value)
    {
        if (isFull()) {
            throw std::overflow_error("Queue overflow: cannot enqueue to full queue");
        }
        data.push_back(value);
        rearIdx++;
        count++;
    }
    
    T dequeue()
    {
        if (isEmpty()) {
            throw std::underflow_error("Queue underflow: cannot dequeue from empty queue");
        }
        T value = data[frontIdx];
        frontIdx++;
        count--;
        
        // Reset indices when queue becomes empty
        if (isEmpty()) {
            frontIdx = 0;
            rearIdx = -1;
            data.clear();
        }
        
        return value;
    }
    
    T front() const
    {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: cannot get front");
        }
        return data[frontIdx];
    }
    
    T rear() const
    {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: cannot get rear");
        }
        return data[rearIdx];
    }
    
    bool isEmpty() const
    {
        return count == 0;
    }
    
    bool isFull() const
    {
        return count >= maxSize;
    }
    
    int size() const
    {
        return count;
    }
    
    int capacity() const
    {
        return maxSize;
    }
    
    void clear()
    {
        data.clear();
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }
    
    std::vector<T> getData() const
    {
        if (isEmpty()) {
            return std::vector<T>();
        }
        return std::vector<T>(data.begin() + frontIdx, data.end());
    }
    
    int search(T value) const
    {
        for (int i = frontIdx; i <= rearIdx; ++i) {
            if (data[i] == value) {
                return i - frontIdx; // Position from front
            }
        }
        return -1;
    }

private:
    std::vector<T> data;
    size_t maxSize;
    int frontIdx;
    int rearIdx;
    int count;
};

#endif // QUEUE_H
