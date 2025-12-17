#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
public:
    Stack() : maxSize(100) {}
    
    explicit Stack(int size) : maxSize(size) {}
    
    void push(T value)
    {
        if (isFull()) {
            throw std::overflow_error("Stack overflow: cannot push to full stack");
        }
        data.push_back(value);
    }
    
    T pop()
    {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow: cannot pop from empty stack");
        }
        T value = data.back();
        data.pop_back();
        return value;
    }
    
    T peek() const
    {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty: cannot peek");
        }
        return data.back();
    }
    
    bool isEmpty() const
    {
        return data.empty();
    }
    
    bool isFull() const
    {
        return data.size() >= maxSize;
    }
    
    int size() const
    {
        return data.size();
    }
    
    int capacity() const
    {
        return maxSize;
    }
    
    void clear()
    {
        data.clear();
    }
    
    std::vector<T> getData() const
    {
        return data;
    }
    
    int search(T value) const
    {
        for (int i = data.size() - 1; i >= 0; --i) {
            if (data[i] == value) {
                return data.size() - 1 - i; // Distance from top
            }
        }
        return -1;
    }

private:
    std::vector<T> data;
    size_t maxSize;
};

#endif // STACK_H
