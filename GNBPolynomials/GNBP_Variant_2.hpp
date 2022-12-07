#pragma once
// Include and predeclaration area

#include <string>
#include <bitset>
#include <iostream>

#define __FIELD_POWER 173

// End of include and predeclaration area

/**
 * Class to describe Galois Fields with charasteristics 2
 * in Galois Normal Basis of second type
 * p = 2, m = 173
 * 
 * coefs[i] - corresponds to value next to x^{p^{i}}
 */
class NB_Polynomial
{
    // Vector of coeficients for polynomials
    std::bitset<__FIELD_POWER> coefs;
    const size_t bit_length;

public:
    // Constructors and destructor
    NB_Polynomial();
    NB_Polynomial(bool);                                // For 0 and 1
    NB_Polynomial(const NB_Polynomial&) = default;
    NB_Polynomial(const std::bitset<__FIELD_POWER>&);
    NB_Polynomial(const std::string&);
    ~NB_Polynomial();
    //

    // User interaction
    size_t get_field_power() const;
    std::string to_string() const;
    //

    // Operations over polynomials
    NB_Polynomial& operator=(const NB_Polynomial&);
    NB_Polynomial operator+(const NB_Polynomial&) const;
    // NB_Polynomial operator*(const NB_Polynomial&) const;
    static bool trace(const NB_Polynomial&);
    // NB_Polynomial square() const;
    // NB_Polynomial inverse() const;
    // NB_Polynomial power(const std::string&) const;
    //

    // Compare
    bool operator==(const NB_Polynomial&) const;

private:
};

std::ostream& operator<<(std::ostream&, const NB_Polynomial&);
