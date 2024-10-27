#include <iostream>
#include <vector>
#include <stdexcept>

class Stack {
private:
    std::vector<int> elements;

public:
    void push(int element) {
        elements.push_back(element);
    }

    int pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        int top = elements.back();
        elements.pop_back();
        return top;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    Stack stack;

    // Push some elements
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Print the top element
    std::cout << "Top element: " << stack.peek() << std::endl;

    // Pop and print elements
    while (!stack.isEmpty()) {
        std::cout << "Popped: " << stack.pop() << std::endl;
    }

    return 0;
}