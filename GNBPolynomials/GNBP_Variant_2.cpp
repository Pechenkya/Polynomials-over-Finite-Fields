#include "GNBP_Variant_2.hpp"

// Include area

#include <iostream>

//

#define MAX_HEX 11
#define MAX_DEC 18

// Constructors and destructors
NB_Polynomial::NB_Polynomial() : coefs{0b0}, bit_length{__FIELD_POWER} {}

NB_Polynomial::NB_Polynomial(bool cnst) : bit_length{__FIELD_POWER} 
{
    if(cnst)
    {
        // In NB 1 represented as (1....1)
        for(int i = 0; i < __FIELD_POWER; ++i)
        {
            coefs[i] = 1;
        }
    }
}

NB_Polynomial::NB_Polynomial(const std::bitset<__FIELD_POWER>& bit_repr) : coefs{bit_repr}, bit_length{__FIELD_POWER} {}

NB_Polynomial::NB_Polynomial(const std::string& string_repr) : bit_length{__FIELD_POWER} 
{
    // Expecting value in format "<b0><b1>....<bm-1>"
    // !! With length of __FIELD_POWER !!
    if(string_repr.size() != __FIELD_POWER)
        return; // coefs will be set to 0
    
    // Fill bitset according to the string
    for(int coef_id = 0; coef_id < __FIELD_POWER; ++coef_id)
    {
        if(string_repr[coef_id] == '1')
            coefs[coef_id] = 1;
        else if(string_repr[coef_id] != '0')
        {
            // Corrupted string
            coefs = 0b0;
            return;
        }
    }
}

NB_Polynomial::~NB_Polynomial() {/*Empty destructor*/}
//

// User interaction
size_t NB_Polynomial::get_field_power() const
{
    return bit_length;
}

std::string NB_Polynomial::to_string() const
{
    std::string res = "";
    for(int i = 0; i < __FIELD_POWER; ++i)
    {
        if(coefs[i])
            res += '1';
        else
            res += '0';
    }

    return res;
}
//

// Arithmetic operations
NB_Polynomial& NB_Polynomial::operator=(const NB_Polynomial& r)
{
    // value to return
    this->coefs = r.coefs;
    return *this; 
}

NB_Polynomial NB_Polynomial::operator+(const NB_Polynomial& r) const
{
    // value to return
    NB_Polynomial res;

    // As we have polynomials over field {0, 1}, we use XOR to add coefs
    res.coefs = this->coefs ^ r.coefs;

    return res; 
}

// NB_Polynomial NB_Polynomial::operator*(const NB_Polynomial& right) const
// {
//     // TODO
// }

bool NB_Polynomial::trace(const NB_Polynomial& poly)
{
    // In NB trace of elements is equal to sum of coefficients
}