//
// Created by Черных Никита Алекандрович on 3/17/21.
//
//Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
//
//Обрабатывать команды push back и pop front.

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Element {
    T value;
    int exist;
};

template<typename T>
class Stack {
public:
    Stack() : size(0), capacity(1), capacityMultiply(0) {
        array = new T[capacity];
    };

    Stack(size_t size, size_t capacity, size_t capacityMultiply) : size(size),
                                                                   capacity(capacity),
                                                                   capacityMultiply(capacityMultiply) {
        array = new T[capacity];
    };

    ~Stack() {
        delete[] array;
    }

    void Push(const T &element) {
        if (size == capacity)
            resize();

        array[size++] = element;
    };

    Element<T> Pop() {
        Element<T> resp{};
        if (IsEmpty()) {
            resp.exist = -1;
            return resp;
        }

        resp.exist = 1;
        resp.value = array[--size];

        return resp;
    }

    bool IsEmpty() {
        return size == 0;
    }

private:
    void resize() {
        capacity *= capacityMultiply;
        auto new_array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    };


    T *array;
    size_t size;
    size_t capacity;
    size_t capacityMultiply;
};

template<typename T>
class Queue {

public:
    Queue() {
        in = Stack<T>();
        out = Stack<T>();
    };

    Queue(Stack<T> *in, Stack<T> *out) : in(in), out(out) {};

    void Push(const T &element) {
        in->Push(element);
    };

    Element<T> Pop() {
        if (out->IsEmpty())
            transfer();

        return out->Pop();
    }

    ~Queue() = default;

private:
    void transfer() {
        auto el = in->Pop();
        while (el.exist != -1) {
            out->Push(el.value);
            el = in->Pop();
        }
    };

    Stack<T> *in;
    Stack<T> *out;
};

const size_t size = 0;
const size_t capacity = 1;
const size_t capacityMultiply = 2;

const size_t pushOperation = 3;
const size_t popOperation = 2;

int main() {
    auto in = new Stack<int>(size, capacity, capacityMultiply);
    auto out = new Stack<int>(size, capacity, capacityMultiply);
    auto queue = new Queue<int>(in, out);
    size_t commandSize = 0;
    size_t command = 0;
    int result = 0;
    bool response = true;

    cin >> commandSize;
    while (commandSize >= 1) {
        cin >> command >> result;

        switch (command) {
            case pushOperation :
                queue->Push(result);
                break;
            case popOperation :
                auto el = queue->Pop();

                if (el.exist != result && el.value != result)
                    response = false;
                break;
        }

        if (!response)
            break;
        commandSize--;
    }

    if (response) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    delete queue;
    delete in;
    delete out;
    return 0;
}