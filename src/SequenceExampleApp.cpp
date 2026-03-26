#include <iostream>
#include <string>
#include <ctime> 
#include "../heads/ArraySequence.h"
#include "../heads/ListSequence.h"

// Функция для демонстрации работы с последовательностью чисел
void demonstrateNumberSequence() {
    std::cout << "\n=== Демонстрация работы с числами ===\n";
    
    ArraySequence<double> numbers;
    
    std::cout << "Добавляем числа: ";
    for (double num : {3.14, 2.71, 1.41, 1.73, 2.23}) {
        std::cout << num << " ";
        numbers.Append(num);
    }
    std::cout << "\n";
    
    std::cout << "Длина последовательности: " << numbers.GetLength() << "\n";
    std::cout << "Первый элемент: " << numbers.GetFirst() << "\n";
    std::cout << "Последний элемент: " << numbers.GetLast() << "\n";
    
    auto subSeq = numbers.GetSubsequence(1, 3);
    std::cout << "Подпоследовательность [1..3]: ";
    for (int i = 0; i < subSeq->GetLength(); ++i) {
        std::cout << subSeq->Get(i) << " ";
    }
    std::cout << "\n";
    delete subSeq;
    
    std::cout << "Удаляем число 1.41\n";
    numbers.Remove(1.41);
    std::cout << "Новая длина: " << numbers.GetLength() << "\n";
}

// Функция для демонстрации работы со строками
void demonstrateStringSequence() {
    std::cout << "\n=== Демонстрация работы со строками ===\n";
    
    ListSequence<std::string> words;
    
    words.Append("мир");
    words.Prepend("Привет");
    words.Append("!");
    words.InsertAt(2, "прекрасный");
    
    std::cout << "Слова в последовательности:\n";
    for (int i = 0; i < words.GetLength(); ++i) {
        std::cout << "  [" << i << "] " << words.Get(i) << "\n";
    }
    
    std::cout << "\nПредложение: ";
    for (int i = 0; i < words.GetLength(); ++i) {
        std::cout << words.Get(i) << " ";
    }
    std::cout << "\n";
}

// Сравнение производительности
void comparePerformance() {
    std::cout << "\n=== Сравнение производительности ===\n";
    
    const int N = 10000;
    
    {
        ArraySequence<int> arrSeq;
        auto start = std::clock();
        for (int i = 0; i < N; ++i) {
            arrSeq.Append(i);
        }
        for (int i = 0; i < N; ++i) {
            arrSeq.Prepend(i);
        }
        auto end = std::clock();
        std::cout << "ArraySequence время: " 
                  << double(end - start) / CLOCKS_PER_SEC << " сек\n";
    }
    
    {
        ListSequence<int> listSeq;
        auto start = std::clock();
        for (int i = 0; i < N; ++i) {
            listSeq.Append(i);
        }
        for (int i = 0; i < N; ++i) {
            listSeq.Prepend(i);
        }
        auto end = std::clock();
        std::cout << "ListSequence время: " 
                  << double(end - start) / CLOCKS_PER_SEC << " сек\n";
    }
}

int main() {
    std::cout << "Приложение для работы с последовательностями\n";
    std::cout << "============================================\n";
    
    demonstrateNumberSequence();
    demonstrateStringSequence();
    comparePerformance();
    
    std::cout << "\nПриложение завершило работу.\n";
    return 0;
}