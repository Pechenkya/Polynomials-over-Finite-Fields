#pragma once
// Include and predeclaration area

#include <string>
#include <bitset>
#include <iostream>

#define __FIELD_POWER 173
#define __DOUBLED_FIELD_POWER 346
class LongInt_holder;

// End of include and predeclaration area

/**
 * Class to describe Galois Fields with charasteristics 2
 * Irreducible polynomial to generate the field (Variant 2): p(x) = x^173 + x^10 + x^2 + x + 1
 */
class PB_Polynomial
{
    // Vector of coeficients for polynomials
    std::bitset<__FIELD_POWER> coefs;
    const size_t bit_length;

public:
    // Constructors and destructor
    PB_Polynomial();
    PB_Polynomial(unsigned);
    PB_Polynomial(const std::bitset<__FIELD_POWER>&);
    PB_Polynomial(const std::string&);
    ~PB_Polynomial();
    //

    // User interaction
    size_t get_field_power() const;
    std::string to_string() const;
    //

    // Operations over polynomials
    PB_Polynomial& operator=(const PB_Polynomial&);
    PB_Polynomial operator+(const PB_Polynomial&) const;
    PB_Polynomial operator*(const PB_Polynomial&) const;
    static PB_Polynomial trace(const PB_Polynomial&);
    PB_Polynomial square() const;
    PB_Polynomial inverse() const;
    PB_Polynomial power(const std::string&) const;
    //

    // Compare
    bool operator==(const PB_Polynomial&) const;

private:
    void in_square();
    static std::bitset<__FIELD_POWER> convert_string_to_power(const std::string&);
    static void take_by_p_modulo(std::bitset<__DOUBLED_FIELD_POWER>&);
    static std::bitset<__DOUBLED_FIELD_POWER> double_bitset_size(const std::bitset<__FIELD_POWER>&);
    static std::bitset<__FIELD_POWER> shrink_bitset_size(const std::bitset<__DOUBLED_FIELD_POWER>&);
};

std::ostream& operator<<(std::ostream&, const PB_Polynomial&);
