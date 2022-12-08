#pragma once
#include <vector>
#include <string>

class PB_NB_Tests
{
    static std::vector<std::string> binaries;
    static std::vector<std::string> powers;
    static std::vector<std::string> nb_binaries;

    static void parse_gen_numbers();
public:
    PB_NB_Tests() = delete;
    static void set_tests();
    static void run_PB_test();
    static void run_NB_test();
};