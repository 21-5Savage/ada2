#include <iostream>
#include <thread>

void say_hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(say_hello);
    t.join();  // Wait for the thread to finish
    return 0;
}