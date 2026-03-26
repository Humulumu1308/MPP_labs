#include <iostream>
#include <cassert>
#include "../heads/ArraySequence.h"
#include "../heads/ListSequence.h"

template<typename TSeq>
void TestSequence() {
    std::cout << "Тестируем " << typeid(TSeq).name() << "...\n";

    // 6.1.1 Создать пустую последовательность (int)
    TSeq seq;

    // 6.1.2 Проверить, что длина = 0
    assert(seq.GetLength() == 0);
    assert(seq.IsEmpty());

    // 6.1.3 Добавить (Append) элемент «23».
    seq.Append(23);

    // 6.1.4 Проверить, что длина = 1
    assert(seq.GetLength() == 1);
    assert(!seq.IsEmpty());

    // 6.1.5 Проверить, что GetFirst возвращает «23»
    assert(seq.GetFirst() == 23);

    // 6.1.6 Проверить, что GetLast возвращает «23»
    assert(seq.GetLast() == 23);

    // 6.1.7 Проверить, что Get(0) возвращает «23», а Get(-1) и Get(1) – выбрасывают исключение.
    assert(seq.Get(0) == 23);

    bool thrown = false;
    try { seq.Get(-1); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { seq.Get(1); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // 6.1.8 Добавить (Append) элемент «43»
    seq.Append(43);

    // 6.1.9 Проверить, что длина = 2
    assert(seq.GetLength() == 2);

    // 6.1.10 Проверить, что GetFirst возвращает «23»
    assert(seq.GetFirst() == 23);

    // 6.1.11 Проверить, что GetLast возвращает «43»
    assert(seq.GetLast() == 43);

    // 6.1.12 Проверить, что Get(0) возвращает «23», Get(1) – «43», а Get(-1) и Get(2) – выбрасывают исключение.
    assert(seq.Get(0) == 23);
    assert(seq.Get(1) == 43);

    thrown = false;
    try { seq.Get(-1); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { seq.Get(2); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // 6.1.13 Добавить (Prepend) элемент «53»
    seq.Prepend(53);

    // 6.1.14 Проверить, что длина = 3
    assert(seq.GetLength() == 3);

    // 6.1.15 Проверить, что GetFirst возвращает «53»
    assert(seq.GetFirst() == 53);

    // 6.1.16 Проверить, что GetLast возвращает «43»
    assert(seq.GetLast() == 43);

    // 6.1.17 Проверить, что Get(0) возвращает «53», Get(1) – «23», Get(2) – «43», а Get(-1) и Get(3) – выбрасывают исключение.
    assert(seq.Get(0) == 53);
    assert(seq.Get(1) == 23);
    assert(seq.Get(2) == 43);

    thrown = false;
    try { seq.Get(-1); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { seq.Get(3); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // 6.1.18 Проверить, что GetSubsequence(1,1) возвращает последовательность, у которой:
    Sequence<int>* sub = seq.GetSubsequence(1, 1);
    // 6.1.18.1 длина = 1
    assert(sub->GetLength() == 1);
    // 6.1.18.2 первый и последний элемент – 23
    assert(sub->GetFirst() == 23);
    assert(sub->GetLast() == 23);
    delete sub;

    std::cout << "Все тесты успешно пройдены.\n";
}

// Дополнительно проверим работу Remove (не входит в сценарий, но для полноты)
template<typename TSeq>
void TestRemove() {
    TSeq seq;
    seq.Append(10);
    seq.Append(20);
    seq.Append(10);
    seq.Remove(10);
    assert(seq.GetLength() == 2);
    assert(seq.Get(0) == 20);
    assert(seq.Get(1) == 10);
    seq.Remove(10);
    assert(seq.GetLength() == 1);
    assert(seq.Get(0) == 20);
    seq.Remove(99); // ничего не происходит
    assert(seq.GetLength() == 1);
    std::cout << "Тесты Remove() также пройдены.\n\n";
}

int main() {
    std::cout << "Запуск тестирования ArraySequence<int>...\n";
    TestSequence<ArraySequence<int>>();
    TestRemove<ArraySequence<int>>();

    std::cout << "Запуск тестирования ListSequence<int>...\n";
    TestSequence<ListSequence<int>>();
    TestRemove<ListSequence<int>>();

    std::cout << "Все тестирования успешно завершены!" << std::endl;
    return 0;
}