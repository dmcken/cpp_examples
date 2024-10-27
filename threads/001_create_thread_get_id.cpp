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
 * To build:
 * - g++ 001_create_thread_get_id.cpp -o 001_create_thread_get_id.exe 
 *
 * @copyright Copyright (c) 2023
 * 
 */

// Standard library includes
#include <chrono>         // std::chrono::seconds
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id


// Global variables
std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread()
{
    // Get what is our current thread ID.
    std::thread::id current_thread_id = std::this_thread::get_id();

    if ( main_thread_id == current_thread_id ) {
        std::cout << "This is the main thread." << std::endl;
    } else {
        std::cout << "This is not the main thread." << std::endl;
    }

    std::cout << "Thread ID: " << current_thread_id << std::endl;
}

int main() 
{
    // Run the function directly in the main thread
    is_main_thread();

    // Create a thread and run the same function with no parameter
    std::thread th (is_main_thread);

    // Join (Wait until it terminates) onto the thread
    th.join();

    return 0;
}
