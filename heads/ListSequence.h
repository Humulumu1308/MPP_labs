#ifndef LIST_SEQUENCE
#define LIST_SEQUENCE

#include <stdexcept>
#include "Sequence.h"

template<typename T> class ListSequence : public Sequence<T> {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node(const T& val, Node* prv = nullptr, Node* nxt = nullptr) 
            : value(val), prev(prv), next(nxt) {}
    };

    Node* head;
    Node* tail;
    int count;

    void CheckIndex(int index, int upper_bound) const {
        if (index < 0 || index >= upper_bound)
            throw std::out_of_range("Index out of range");
    }

    Node* GetNode(int index) const {
        if (index < count / 2) {
            Node* cur = head;
            for (int i = 0; i < index; ++i) cur = cur->next;
            return cur;
        } else {
            Node* cur = tail;
            for (int i = count - 1; i > index; --i) cur = cur->prev;
            return cur;
        }
    }

public:
    ListSequence() : head(nullptr), tail(nullptr), count(0) {}

    ListSequence(const ListSequence& other) : head(nullptr), tail(nullptr), count(0) {
        Node* cur = other.head;
        while (cur) {
            Append(cur->value);
            cur = cur->next;
        }
    }

    ~ListSequence() override {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    int GetLength() const override {
        return count;
    }

    bool IsEmpty() const override {
        return count == 0;
    }

    T GetFirst() const override {
        if (IsEmpty()) throw std::out_of_range("Sequence is empty");
        return head->value;
    }

    T GetLast() const override {
        if (IsEmpty()) throw std::out_of_range("Sequence is empty");
        return tail->value;
    }

    T Get(int index) const override {
        CheckIndex(index, count);
        return GetNode(index)->value;
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        CheckIndex(startIndex, count);
        CheckIndex(endIndex, count);
        if (startIndex > endIndex) throw std::invalid_argument("startIndex > endIndex");

        ListSequence<T>* sub = new ListSequence<T>();
        Node* cur = GetNode(startIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            sub->Append(cur->value);
            cur = cur->next;
        }
        return sub;
    }

    void Append(const T& item) override {
        Node* newNode = new Node(item);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++count;
    }

    void Prepend(const T& item) override {
        Node* newNode = new Node(item);
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++count;
    }

    void InsertAt(int index, const T& item) override {
        CheckIndex(index, count + 1);

        if (index == 0) {
            Prepend(item);
        } else if (index == count) {
            Append(item);
        } else {
            Node* nextNode = GetNode(index);
            Node* prevNode = nextNode->prev;
            Node* newNode = new Node(item, prevNode, nextNode);
            prevNode->next = newNode;
            nextNode->prev = newNode;
            
            ++count;
        }
    }

    void Remove(const T& item) override {
        Node* cur = head;
        while (cur) {
            if (cur->value == item) {
                if (cur->prev) {
                    cur->prev->next = cur->next;
                } else {
                    head = cur->next;
                }
                
                if (cur->next) {
                    cur->next->prev = cur->prev;
                } else {
                    tail = cur->prev;
                }
                
                delete cur;
                --count;
                return;
            }
            cur = cur->next;
        }
    }
};

#endif