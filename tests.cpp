#include "../Stack/Stack.h"
#include <iostream>
#include <functional>
#include <stdexcept>

template<typename T>
bool test_copy_constructor()
{
    Stack<T> stack;
    if constexpr (std::is_same_v<T, int>)
    {
        stack.push(3);
        stack.push(4);
        stack.push(5);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        stack.push(2.15);
        stack.push(-8.65);
        stack.push(5.1);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        stack.push("3");
        stack.push("4");
        stack.push("5");
    }

    Stack<T> copied_stack(stack);

    if (stack.size() != copied_stack.size())
    {
        return false;
    }
    return true;
}

template<typename T>
bool test_move_constructor()
{
    Stack<T> stack;
    if constexpr (std::is_same_v<T, int>)
    {
        stack.push(3);
        stack.push(4);
        stack.push(5);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        stack.push(22.35);
        stack.push(-2.16);
        stack.push(3.2);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        stack.push("3");
        stack.push("4");
        stack.push("5");
    }

    Stack<T> copied_stack(stack);
    Stack<T> moved_stack(std::move(stack));

    if (!stack.empty())
    {
        return false;
    }

    while (!moved_stack.empty())
    {
        if (moved_stack.top() != copied_stack.top())
        {
            return false;
        }
        moved_stack.pop();
        copied_stack.pop();
    }

    return true;
}


template<typename T>
bool test_copy_assignment()
{
    Stack<T> stack;
    if constexpr (std::is_same_v<T, int>)
    {
        stack.push(3);
        stack.push(4);
        stack.push(5);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        stack.push(2.15);
        stack.push(-8.65);
        stack.push(5.1);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        stack.push("3");
        stack.push("4");
        stack.push("5");
    }

    Stack<T> assigned_stack;
    assigned_stack = stack;

    if (stack.size() != assigned_stack.size())
    {
        return false;
    }

    while (!stack.empty())
    {
        if (stack.top() != assigned_stack.top())
        {
            return false;
        }
        stack.pop();
        assigned_stack.pop();
    }

    return true;
}

template<typename T>
bool test_move_assignment()
{
    Stack<T> stack;
    if constexpr (std::is_same_v<T, int>)
    {
        stack.push(3);
        stack.push(4);
        stack.push(5);
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        stack.push(2.15);
        stack.push(-8.65);
        stack.push(5.1);
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        stack.push("3");
        stack.push("4");
        stack.push("5");
    }

    Stack<T> copied_stack(stack);
    Stack<T> moved_stack;
    moved_stack = std::move(stack);

    if (stack.size() != 0)
    {
        return false;
    }

    if (moved_stack.size() == 0)
    {
        return false;
    }

    while (!moved_stack.empty())
    {
        if (copied_stack.top() != moved_stack.top())
        {
            return false;
        }
        copied_stack.pop();
        moved_stack.pop();
    }

    return true;
}

template<typename T>
bool test_top()
{
    Stack<T> stack;
    T value;
    if constexpr (std::is_same_v<T, int>)
    {
        value = 655;
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        value = 233.233;
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        value = "18.65";
    }

    stack.push(value);

    return stack.top() == value;
}

template<typename T>
bool test_push()
{
    Stack<T> stack;
    T value;
    if constexpr (std::is_same_v<T, int>)
    {
        value = 655;
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        value = 233.233;
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        value = "18.65";
    }

    stack.push(value);

    return stack.top() == value;
}

template<typename T>
bool test_pop()
{
    Stack<T> stack;
    T value;
    if constexpr (std::is_same_v<T, int>)
    {
        value = 655;
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        value = 233.233;
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        value = "18.65";
    }

    stack.push(value);

    stack.pop();

    return stack.empty();
}

void run_test(const char* name, std::function<bool()> test)
{
    std::cout << name << ": ";
    try
    {
        if (test())
        {
            std::cout << "[OK]" << std::endl;
        }
        else
        {
            std::cout << "[FAIL]" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[EXCEPTION]" << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "[ERROR]" << std::endl;
    }
}

int main()
{
    std::cout << "Testing with type double:\n";
    run_test("double_push", test_push<double>);
    run_test("double_top", test_top<double>);
    run_test("double_pop", test_pop<double>);
    run_test("double_copy_constructor", test_copy_constructor<double>);
    run_test("double_move_constructor", test_move_constructor<double>);
    run_test("double_copy_assignment", test_copy_assignment<double>);
    run_test("double_move_assignment", test_move_assignment<double>);
    printf("========================\n");

    std::cout << "Testing with type int:\n";
    run_test("int_push", test_push<int>);
    run_test("int_top", test_top<int>);
    run_test("int_pop", test_pop<int>);
    run_test("int_copy_constructor", test_copy_constructor<int>);
    run_test("int_move_constructor", test_move_constructor<int>);
    run_test("int_copy_assignment", test_copy_assignment<int>);
    run_test("int_move_assignment", test_move_assignment<int>);
    printf("========================\n");

    std::cout << "Testing with type string:\n";
    run_test("std::string_push", test_push<std::string>);
    run_test("std::string_top", test_top<std::string>);
    run_test("std::string_pop", test_pop<std::string>);
    run_test("std::string_copy_constructor", test_copy_constructor<std::string>);
    run_test("std::string_move_constructor", test_move_constructor<std::string>);
    run_test("std::string_copy_assignment", test_copy_assignment<std::string>);
    run_test("std::string_move_assignment", test_move_assignment<std::string>);
    printf("========================\n");


}