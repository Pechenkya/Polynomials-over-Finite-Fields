#pragma once
#include <vector>
#include <string>
#include "..\\PolynomialsOFF\\POFF_Variant_2.hpp"
#include "..\\GNBPolynomials\\GNBP_Variant_2.hpp"

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
    static void get_nb_values(std::string&, std::string&, std::string&);
    static void run_NB_test();
};