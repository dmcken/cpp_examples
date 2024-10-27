/**
 * C++ Program to demonstrate thread pooling
 *
 * Uses boost library:
 * g++ -O3 -DBOOST_LOG_DYN_LINK multi_sink_test.cpp -std=c++20 -lboost_log -lboost_log_setup -lboost_thread -pthread && ./a.out
 *
 */

#include <functional>
#include <future>
#include <iostream>
#include <thread>

// Boost includes
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>


void init_logging()
{
    // Add console logs
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::filter     = boost::log::trivial::severity >= boost::log::trivial::trace,
        boost::log::keywords::format     = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
    );
    // Add file logs
    boost::log::add_file_log(
        boost::log::keywords::file_name           = "tpool_test_%N.log",
        boost::log::keywords::open_mode           = std::ios::out | std::ios::app,
        // boost::log::keywords::auto_flush          = true,
        boost::log::keywords::rotation_size       = 1 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        // ProcessID if we need process
        boost::log::keywords::format              = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
    );

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

    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "An informational severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::error) << "An error severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::fatal) << "A fatal severity message";

    BOOST_LOG_TRIVIAL(trace)   << "Trivial trace";
    BOOST_LOG_TRIVIAL(debug)   << "Trivial debug";
    BOOST_LOG_TRIVIAL(info)    << "Trivial info";
    BOOST_LOG_TRIVIAL(warning) << "Trivial warning";
    BOOST_LOG_TRIVIAL(error)   << "Trivial error";
    BOOST_LOG_TRIVIAL(fatal)   << "Trivial fatal";

    return 0;
}
