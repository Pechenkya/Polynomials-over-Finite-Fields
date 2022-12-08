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
    static bool multiplication_matrix_generated;
    static std::bitset<__FIELD_POWER> mult_matrix[__FIELD_POWER];

public:
    // Constructors and destructor
    NB_Polynomial();
    NB_Polynomial(bool);                                // For 0 and 1
    NB_Polynomial(const NB_Polynomial&);
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
    NB_Polynomial operator*(const NB_Polynomial&) const;
    static int trace(const NB_Polynomial&);
    NB_Polynomial square() const;
    NB_Polynomial inverse() const;
    NB_Polynomial power(const std::string&) const;
    //

    // Compare
    bool operator==(const NB_Polynomial&) const;

// private:
    void in_square();
    static std::bitset<__FIELD_POWER> convert_string_to_power(const std::string&);
    static std::bitset<__FIELD_POWER> cycle_shift_left(const std::bitset<__FIELD_POWER>&, int);   // 1 to 0
    static void cycle_shift_left_self(std::bitset<__FIELD_POWER>&, int);
    static std::bitset<__FIELD_POWER> cycle_shift_right(const std::bitset<__FIELD_POWER>&, int);   // 0 to 1
    static void cycle_shift_right_self(std::bitset<__FIELD_POWER>&, int);
    static void generate_mult_matrix();
};

std::ostream& operator<<(std::ostream&, const NB_Polynomial&);
