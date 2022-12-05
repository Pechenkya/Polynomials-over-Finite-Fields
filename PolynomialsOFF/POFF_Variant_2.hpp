// Include and predeclaration area

#include <string>
#include <bitset>

#define FIELD_POWER 173
class LongInt_holder;

// End of include and predeclaration area

/**
 * Class to describe Galois Fields with charasteristics 2
 * Irreducible polynomial to generate the field (Variant 2): p(x) = x^173 + x^10 + x^2 + x + 1
 */
class PB_Polynomial
{
    // Vector of coeficients for polynomials
    std::bitset<FIELD_POWER> coefs;
    const size_t bit_length;

public:
    // Constructors and destructor
    PB_Polynomial();
    PB_Polynomial(unsigned);
    PB_Polynomial(const std::bitset<FIELD_POWER>&);
    PB_Polynomial(const std::string&);
    ~PB_Polynomial();
    //

    // User interaction
    size_t get_field_power();
    static PB_Polynomial string_to_poly(const std::string&);
    std::string to_string();
    //

    // Operations over polynomials
    PB_Polynomial operator+(const PB_Polynomial&);
    PB_Polynomial operator*(const PB_Polynomial&);
    static int trace(const PB_Polynomial&);
    PB_Polynomial square();
    PB_Polynomial inverse();
    PB_Polynomial power(const LongInt_holder&);
    //
};

namespace PB_Constants
{
    extern const PB_Polynomial Zero;
    extern const PB_Polynomial One;
}
