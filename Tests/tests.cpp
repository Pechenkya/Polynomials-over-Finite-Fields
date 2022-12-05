#include "tests.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>
#include "..\\PolynomialsOFF\\POFF_Variant_2.hpp"

#define TEST_SAMPLES 500
#define POWER_SAMPLES 30

std::vector<std::string> PB_Tests::binaries;
std::vector<std::string> PB_Tests::powers;

void PB_Tests::parse_gen_numbers()
{
    std::ifstream inp("./binaries.txt");
    std::string input;
    while(std::getline(inp, input))
    {
        std::string temp = input.substr(0, rand() % 173 + 1);
        PB_Tests::binaries.push_back(temp);
    }
    inp.close();
    inp.open("./powers.txt");
    while(std::getline(inp, input))
    {
        PB_Tests::powers.push_back(input);
    }
    inp.close();
}

void PB_Tests::set_tests()
{
    srand(time(NULL));
    std::cout << std::boolalpha << std::left << std::hex;
    parse_gen_numbers();
}

void PB_Tests::run_test()
{
    std::cout << "--------- TEST START -----------\n";
    std::string _a = binaries[rand() % TEST_SAMPLES];
    std::string _b = binaries[rand() % TEST_SAMPLES];
    std::cout << "Input A: " << _a << std::endl;
    std::cout << "Input B: " << _b << std::endl;
    std::string pow = powers[rand() % POWER_SAMPLES];
    std::cout << "Input POW: " << pow << std::endl;
    PB_Polynomial a(_a);
    PB_Polynomial b(_b);

    std::cout << "Converted A:" << a << std::endl;
    std::cout << "Converted B:" << b << std::endl;

    std::cout << "A + B: " << a + b << std::endl;
    std::cout << "A * B: " << a * b << std::endl;
    std::cout << "A^-1 : " << a.inverse() << std::endl;
    std::cout << "Correct: " << (a.inverse() * a == PB_Polynomial("1")) << std::endl;
    std::cout << "B^-1 : " << b.inverse() << std::endl;
    std::cout << "Correct: " << (b.inverse() * b == PB_Polynomial("1")) << std::endl;
    std::cout << "A^2 : " << a.square() << std::endl;
    std::cout << "Correct: " << (a.square() == a*a) << std::endl;
    std::cout << "B^2 : " << b.square() << std::endl;
    std::cout << "Correct: " << (b.square() == b*b) << std::endl;
    std::cout << "A^POW:" << a.power(pow) << std::endl;
    std::cout << "B^POW:" << b.power(pow) << std::endl;
    std::cout << "Tr(A): " << PB_Polynomial::trace(a) << std::endl;
    std::cout << "Tr(B): " << PB_Polynomial::trace(b) << std::endl;
    std::cout << "--------- TEST END -----------\n";
}

