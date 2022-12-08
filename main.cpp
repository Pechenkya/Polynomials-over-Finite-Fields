#include <iostream>
#include ".\\Tests\\tests.hpp"

void run_NB_test()
{
    std::cout << "--------- TEST START (NB) -----------\n";
    std::string _a, _b, pow;
    PB_NB_Tests::get_nb_values(_a, _b, pow);

    std::cout << "Input A: " << _a << std::endl;
    std::cout << "Input B: " << _b << std::endl;
    std::cout << "Input POW: " << pow << std::endl;
    NB_Polynomial a(_a);
    NB_Polynomial b(_b);

    std::cout << "Converted A:" << a << std::endl;
    std::cout << "Converted B:" << b << std::endl;

    std::cout << "A + B: " << a + b << std::endl;
    std::cout << "A * B: " << a * b << std::endl;
    std::cout << "A^-1 : " << a.inverse() << std::endl;
    std::cout << "-- TEMP --\n";
    std::cout << "A^-1 * A: " << a.inverse() * a << std::endl;
    std::cout << "A^-1^-1 : " << a.inverse().inverse() << std::endl;
    std::cout << "Correct: " << ((a.inverse() * a == NB_Polynomial(1)) && (a.inverse().inverse() == a)) << std::endl;
    std::cout << "B^-1 : " << b.inverse() << std::endl;
    std::cout << "Correct: " << ((b.inverse() * b == NB_Polynomial(1)) && (b.inverse().inverse() == b)) << std::endl;
    std::cout << "A^2 : " << a.square() << std::endl;
    std::cout << "Correct: " << (a.square() == a*a) << std::endl;
    std::cout << "B^2 : " << b.square() << std::endl;
    std::cout << "Correct: " << (b.square() == b*b) << std::endl;
    std::cout << "Square correct: " << ((a + b).square() == (a.square() + b.square())) << std::endl;
    std::cout << "A^POW:" << a.power(pow) << std::endl;
    std::cout << "B^POW:" << b.power(pow) << std::endl;
    std::cout << "Tr(A): " << NB_Polynomial::trace(a) << std::endl;
    std::cout << "Tr(B): " << NB_Polynomial::trace(b) << std::endl;
    std::cout << "--------- TEST END (NB) -----------\n";
}

void pg_test()
{
    NB_Polynomial a("01100011100100001001110111000101101001011000100010110010101010010010100100100010010001110100001011010011011111100000001011000110111011110011011000010000110101100101000001010");
    NB_Polynomial b("10110100101100001110101100000110100010011101111110100100001110101111010001111111001110010010100000010011110111111000100001001101010001001100100111101000111111110111000001101");

    std::cout << a.inverse() * a << std::endl;
    std::cout << (a * a.inverse() == NB_Polynomial(1)) << std::endl;
    std::cout << (a.inverse().inverse() == a) << std::endl;
}


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
            PB_NB_Tests:run_NB_test();
        if(x == 3)
            pg_test();
    }

    return 0;
}