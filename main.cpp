#include <iostream>
#include <bitset>
#include "PolynomialsOFF\\POFF_Variant_2.hpp"

int main()
{
    PB_Polynomial a(0b11);
    std::string pow = "0x0003";
    std::cout << a.power(pow).to_string() << std::endl;
    std::cout << (a*a*a).to_string() << std::endl;

    int x;
    std::cin >> x;
    return 0;
}