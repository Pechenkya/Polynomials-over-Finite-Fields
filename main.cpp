#include <iostream>
#include ".\\Tests\\tests.hpp"
#include ".\\PolynomialsOFF\\POFF_Variant_2.hpp"
#include ".\\GNBPolynomials\\GNBP_Variant_2.hpp"

int main()
{
    PB_NB_Tests::set_tests();
    int x = 1;
    while(true)
    {
        std::cout << "Input (0 to exit, 1 - PB tests, 2 - NB tests): ";
        std::cin >> x;
        if(!x)
            break;
        if(x == 1)
            PB_NB_Tests::run_PB_test();
        if(x == 2)
            PB_NB_Tests::run_NB_test();
    }

    // std::bitset<173> a = 0b111111000101;
    // std::cout << NB_Polynomial(a) << std::endl;
    // std::cout << NB_Polynomial(NB_Polynomial::cycle_shift_left(a, 1)) << std::endl;
    // std::cout << NB_Polynomial(NB_Polynomial::cycle_shift_left(a, 2)) << std::endl;
    // std::cout << NB_Polynomial(NB_Polynomial::cycle_shift_left(a, 3)) << std::endl;
    // std::cout << NB_Polynomial(NB_Polynomial::cycle_shift_left(a, 4)) << std::endl;
    // std::cout << NB_Polynomial(NB_Polynomial::cycle_shift_left(a, 5));

    // int x;
    // std::cin >> x;
    return 0;
}