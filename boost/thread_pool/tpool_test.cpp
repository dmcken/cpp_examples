/**
 * C++ to demonstrate thread pooling using the Boost ASIO library (and the Boost log
 * library for some sort of visibility).
 *
 * Uses boost library:
 * g++ -O3 -DBOOST_LOG_DYN_LINK tpool_test.cpp -std=c++20 -lboost_log -lboost_log_setup -lboost_thread -pthread && ./a.out
 *
 */

#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <thread>

// Boost includes
#include <boost/asio.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>




// Random number generators
static std::mt19937_64 rng;
static std::uniform_int_distribution<uint> sleep_dist(100, 2000);


void init_logging()
{
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::filter     = boost::log::trivial::severity >= boost::log::trivial::trace,
        boost::log::keywords::format     = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
    );
    // If you want the logs also to a file.
    // boost::log::add_file_log(
    //     boost::log::keywords::file_name           = "tpool_test.log",
    //     boost::log::keywords::open_mode           = std::ios::out | std::ios::app,
    //     // ProcessID if we need process
    //     boost::log::keywords::format              = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
    // );

    // Global filter
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );
    boost::log::add_common_attributes();
}


int main()
{
    init_logging();
    // boost::log::add_common_attributes();

    boost::log::sources::severity_logger< boost::log::trivial::severity_level > lg ;

    // Random number generator seed
    rng.seed(static_cast<uint>(
        std::chrono::high_resolution_clock().now().time_since_epoch().count()
    ));

    // Create a thread pool with 4 threads
    boost::asio::thread_pool pool(4);

    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "Start";

    // Enqueue tasks for execution
    for (int i = 0; i < 80; ++i) {
        unsigned sleep_ms = sleep_dist(rng);
        boost::asio::post(pool, [i, sleep_ms, &lg] {

            BOOST_LOG_SEV(lg, boost::log::trivial::debug) << "Task " << i  << " is running on thread "
                << std::this_thread::get_id() << " for " << sleep_ms << " ms";

            // Simulate some work

            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

            BOOST_LOG_SEV(lg, boost::log::trivial::info) << "Task " << i << " woke up after " << sleep_ms << "ms" << std::endl;
        });
    }

    std::future<int> r1 = boost::asio::post(pool, boost::asio::use_future([]() { return 2; }));
    BOOST_LOG_TRIVIAL(info) << "Result = " << r1.get();

    pool.join();

    BOOST_LOG_TRIVIAL(info) << "Done";

    return 0;
}
