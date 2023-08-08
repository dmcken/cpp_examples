/**
 * @file 001_create_thread_get_id.cpp
 * @author David Mc Ken ()
 * @brief 
 * @version 0.1
 * @date 2023-08-08
 * 
 * Simple thread ID example:
 * - Save the main thread's ID and use that in a function to determine if the
 *   current context is the main thread or not.
 * - Display the thread ID.
 *
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds

std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
    if ( main_thread_id == std::this_thread::get_id() ) {
        std::cout << "This is the main thread." << std::endl;
    } else {
        std::cout << "This is not the main thread." << std::endl;
    }

    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

int main() 
{
    is_main_thread();
    std::thread th (is_main_thread);
    th.join();

    return 0;
}
