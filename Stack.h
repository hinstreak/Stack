#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T>
class Stack
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* top_n;
    std::size_t stack_size;

public:
    Stack();

    Stack(const Stack& another);
    Stack(Stack&& another) noexcept;
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void pop();
    T& top();
    void push(const T& val);
    void push(T&& val);

    bool empty() const;
    std::size_t size() const;
};

template<typename T>
Stack<T>::Stack() : top_n(nullptr), stack_size(0) {}

template<typename T>
Stack<T>::Stack(const Stack& other) : top_n(nullptr), stack_size(0)
{
    Node* other_current = other.top_n;
    Stack<T> temp_stack;
    while (other_current != nullptr)
    {
        temp_stack.push(other_current->data);
        other_current = other_current->next;
    }

    while (!temp_stack.empty())
    {
        push(temp_stack.top());
        temp_stack.pop();
    }
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept : top_n(nullptr), stack_size(0)
{
    std::swap(top_n, other.top_n);
    std::swap(stack_size, other.stack_size);
}

template<typename T>
Stack<T>::~Stack()
{
    while (top_n != nullptr)
    {
        Node* temp = top_n;
        top_n = top_n->next;
        delete temp;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
    if (this != &other)
    {
        Stack temp(other);
        std::swap(top_n, temp.top_n);
        std::swap(stack_size, temp.stack_size);
    }

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
    if (this != &other)
    {
        delete top_n;
        top_n = nullptr;
        stack_size = 0;
        std::swap(top_n, other.top_n);
        std::swap(stack_size, other.stack_size);
    }
    return *this;
}

template<typename T>
void Stack<T>::push(const T& value)
{
    Node* new_node = new Node(value);
    new_node->next = top_n;
    top_n = new_node;
    ++stack_size;
}

template<typename T>
void Stack<T>::push(T&& value)
{
    Node* new_node = new Node(std::move(value));
    new_node->next = top_n;
    top_n = new_node;
    ++stack_size;
}

template<typename T>
void Stack<T>::pop()
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    Node* temp = top_n;
    top_n = top_n->next;
    delete temp;
    --stack_size;
}
template<typename T>
T& Stack<T>::top()
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    return top_n->data;
}

template<typename T>
bool Stack<T>::empty() const
{
    return top_n == nullptr;
}

template<typename T>
std::size_t Stack<T>::size() const
{
    return stack_size;
}

template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;