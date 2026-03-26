#ifndef ARRAY_SEQUENCE
#define ARRAY_SEQUENCE

#include <stdexcept>
#include "Sequence.h"

template<typename T> class ArraySequence : public Sequence<T> {
private:
    T* data;
    int size;
    int capacity;

    void Resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < size; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void CheckIndex(int index, int upper_bound) const {
        if (index < 0 || index >= upper_bound)
            throw std::out_of_range("Index out of range");
    }

public:
    ArraySequence() : data(nullptr), size(0), capacity(0) {}

    ArraySequence(const ArraySequence& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    ~ArraySequence() override {
        delete[] data;
    }

    int GetLength() const override {
        return size;
    }

    bool IsEmpty() const override {
        return size == 0;
    }

    T GetFirst() const override {
        if (IsEmpty()) throw std::out_of_range("Sequence is empty");
        return data[0];
    }

    T GetLast() const override {
        if (IsEmpty()) throw std::out_of_range("Sequence is empty");
        return data[size - 1];
    }

    T Get(int index) const override {
        CheckIndex(index, size);
        return data[index];
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        CheckIndex(startIndex, size);
        CheckIndex(endIndex, size);
        if (startIndex > endIndex) throw std::invalid_argument("startIndex > endIndex");

        ArraySequence<T>* sub = new ArraySequence<T>();
        for (int i = startIndex; i <= endIndex; ++i) {
            sub->Append(data[i]);
        }
        return sub;
    }

    void Append(const T& item) override {
        if (size == capacity) {
            int new_cap = capacity == 0 ? 1 : capacity * 2;
            Resize(new_cap);
        }
        data[size++] = item;
    }

    void Prepend(const T& item) override {
        InsertAt(0, item);
    }

    void InsertAt(int index, const T& item) override {
        CheckIndex(index, size + 1);

        if (size == capacity) {
            int new_cap = capacity == 0 ? 1 : capacity * 2;
            Resize(new_cap);
        }
		for (int i = size; i > index; --i) {
			data[i] = data[i - 1];
		}
		data[index] = item;
		++size;
    }

    void Remove(const T& item) override {
        for (int i = 0; i < size; ++i) {
            if (data[i] == item) {
                for (int j = i; j < size - 1; ++j) {
                    data[j] = data[j + 1];
                }
                --size;
                return;
            }
        }
    }
};

#endif