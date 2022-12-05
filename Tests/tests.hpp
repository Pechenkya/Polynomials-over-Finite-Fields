#pragma once
#include <vector>
#include <string>

class PB_Tests
{
    static std::vector<std::string> binaries;
    static std::vector<std::string> powers;

    static void parse_gen_numbers();
public:
    PB_Tests() = delete;
    static void set_tests();
    static void run_test();
};