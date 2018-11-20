#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

struct Info
{
    Info(): t1(std::chrono::high_resolution_clock::now()) { }

    ~Info() { }

    boost::property_tree::ptree pt;
    bool verbose_ = false;
    bool dbg_ = false;
    bool dbg_live_ = false;
    std::string debug_string;
    std::chrono::high_resolution_clock::time_point t1;

    void set_verbose()         { verbose_  = true; }
    void set_verbose(bool b)   { verbose_  = b; }
    void set_debug()           { dbg_      = true; }
    void set_debug(bool b)     { dbg_      = b; }
    void set_debuglive()       { dbg_live_ = true; }
    void set_debuglive(bool b) { dbg_live_ = b; }

    bool verbose() { return verbose_; }
    bool debug() { return (dbg_ || dbg_live_); }

    void verbose(std::string message)
    {
        if (verbose_ || dbg_live_)
            std::cout << message;
        if (dbg_)
            debug_string += message;
    }

    void debug(std::string message)
    {
        if (dbg_)
            debug_string += message;
        if (dbg_live_)
            std::cout << message;
    }

    void write_ini(std::string file)
    {
        if (file != "")
            boost::property_tree::write_ini(file, pt);
    }

    void write_dbg(std::string file)
    {
        if (file != "") {
            std::ofstream f(file);
            f << debug_string;
            f.close();
        }
    }

    double elapsed_time() const
    {
        std::chrono::high_resolution_clock::time_point t2
            = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span
            = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        return time_span.count();
    }

    template <class T>
    static std::string to_string(T t)
    {
        std::ostringstream s;
        s << t;
        return s.str();
    }
};

