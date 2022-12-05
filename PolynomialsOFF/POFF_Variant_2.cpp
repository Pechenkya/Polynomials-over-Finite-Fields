#include "POFF_Variant_2.hpp"

// Include area

//

// Constants
namespace PB_Constants
{

}
//

PB_Polynomial::PB_Polynomial() : coefs{0b0}, bit_length{FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(unsigned uint_bit) : coefs{uint_bit}, bit_length{FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(const std::bitset<FIELD_POWER>& bit_repr) : coefs{bit_repr}, bit_length{FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(const std::string& string_repr) : bit_length{FIELD_POWER} 
{
    // Expecting value in format "0b<bits>"
    int str_ln = string_repr.size();
    // TODO
}