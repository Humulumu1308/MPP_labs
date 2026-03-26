#ifndef SEQUENCE_H
#define SEQUENCE_H

template<typename T> class Sequence {
public:
    virtual ~Sequence() = default;

    virtual int GetLength() const = 0;
    virtual bool IsEmpty() const = 0;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual void Append(const T& item) = 0;
    virtual void Prepend(const T& item) = 0;
    virtual void InsertAt(int index, const T& item) = 0;
    virtual void Remove(const T& item) = 0;
};

#endif