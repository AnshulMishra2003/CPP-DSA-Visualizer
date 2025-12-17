#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node *next;
        
        Node(T value) : data(value), next(nullptr) {}
    };

    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~LinkedList()
    {
        clear();
    }

    void insertAtBeginning(T value)
    {
        Node *newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    void insertAtEnd(T value)
    {
        Node *newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    bool insertAtPosition(T value, int position)
    {
        if (position < 0 || position > count) {
            return false;
        }
        
        if (position == 0) {
            insertAtBeginning(value);
            return true;
        }
        
        if (position == count) {
            insertAtEnd(value);
            return true;
        }

        Node *newNode = new Node(value);
        Node *current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        count++;
        return true;
    }

    bool deleteFromBeginning()
    {
        if (head == nullptr) {
            return false;
        }
        
        Node *temp = head;
        head = head->next;
        
        if (head == nullptr) {
            tail = nullptr;
        }
        
        delete temp;
        count--;
        return true;
    }

    bool deleteFromEnd()
    {
        if (head == nullptr) {
            return false;
        }
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            count--;
            return true;
        }
        
        Node *current = head;
        while (current->next != tail) {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = nullptr;
        count--;
        return true;
    }

    bool deleteAtPosition(int position)
    {
        if (position < 0 || position >= count || head == nullptr) {
            return false;
        }
        
        if (position == 0) {
            return deleteFromBeginning();
        }
        
        Node *current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        Node *temp = current->next;
        current->next = temp->next;
        
        if (temp == tail) {
            tail = current;
        }
        
        delete temp;
        count--;
        return true;
    }

    int search(T value)
    {
        Node *current = head;
        int position = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        
        return -1;
    }

    void reverse()
    {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;
        tail = head;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
    }

    void clear()
    {
        while (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    std::vector<T> toVector() const
    {
        std::vector<T> result;
        Node *current = head;
        while (current != nullptr) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    Node* getHead() const { return head; }

private:
    Node *head;
    Node *tail;
    int count;
};

#endif // LINKEDLIST_H
