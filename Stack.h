#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* top_node;
    std::size_t stack_size;

public:
    Stack();

    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    ~Stack();

    void push(const T& value);
    void pop();
    T& top();
    bool empty() const;
    std::size_t size() const;
};

template<typename T>
Stack<T>::Stack() : top_node(nullptr), stack_size(0) {}

template<typename T>
Stack<T>::Stack(const Stack& other) : top_node(nullptr), stack_size(0)
{
    static_assert(std::is_copy_constructible<T>::value, "T must be copy constructible");

    Node* other_current = other.top_node;
    Stack<T> temp_stack;
    while (other_current)
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
Stack<T>::Stack(Stack&& other) noexcept : top_node(nullptr), stack_size(0)
{
    static_assert(std::is_move_constructible<T>::value, "T must be move constructible");

    std::swap(top_node, other.top_node);
    std::swap(stack_size, other.stack_size);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
    static_assert(std::is_copy_assignable<T>::value, "T must be copy assignable");

    if (this != &other)
    {
        Stack temp(other);
        std::swap(top_node, temp.top_node);
        std::swap(stack_size, temp.stack_size);
    }

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
    static_assert(std::is_move_assignable<T>::value, "T must be move assignable");

    if (this != &other)
    {
        delete top_node;
        top_node = nullptr;
        stack_size = 0;
        std::swap(top_node, other.top_node);
        std::swap(stack_size, other.stack_size);
    }

    return *this;
}

template<typename T>
Stack<T>::~Stack()
{
    static_assert(std::is_destructible<T>::value, "T must be destructible");

    while (top_node)
    {
        Node* temp = top_node;
        top_node = top_node->next;
        delete temp;
    }
}

template<typename T>
void Stack<T>::push(const T& value)
{
    Node* new_node = new Node(value);
    new_node->next = top_node;
    top_node = new_node;
    ++stack_size;
}

template<typename T>
void Stack<T>::pop()
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    Node* temp = top_node;
    top_node = top_node->next;
    delete temp;
    --stack_size;
}

template<typename T>
T& Stack<T>::top()
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    return top_node->data;
}

template<typename T>
bool Stack<T>::empty() const
{
    return top_node == nullptr;
}

template<typename T>
std::size_t Stack<T>::size() const
{
    return stack_size;
}

template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;