#include "POFF_Variant_2.hpp"

// Include area
#include <iostream>
//

#define MAX_HEX 11
#define MAX_DEC 18

// Constructors and destructors
PB_Polynomial::PB_Polynomial() : coefs{0b0}, bit_length{__FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(unsigned uint_bit) : coefs{uint_bit}, bit_length{__FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(const std::bitset<__FIELD_POWER>& bit_repr) : coefs{bit_repr}, bit_length{__FIELD_POWER} {}

PB_Polynomial::PB_Polynomial(const std::string& string_repr) : bit_length{__FIELD_POWER} 
{
    // Expecting value in format "<bits>"
    int str_ln = string_repr.size() - 1;
    
    // Check mask and length
    if(str_ln > __FIELD_POWER)
        return; // coefs will be set to 0
    
    // Fill bitset according to the string
    int coef_id = 0;
    for(auto itr = string_repr.end() - 1; str_ln >= 0; --str_ln, --itr)
    {
        if(*itr == '1')
            coefs[coef_id] = 1;
        else if(*itr != '0')
        {
            // Corrupted string
            coefs = 0b0;
            return;
        }

        coef_id++;
    }
}

PB_Polynomial::~PB_Polynomial() {/*Empty destructor*/}
//

// User interaction
size_t PB_Polynomial::get_field_power() const
{
    return bit_length;
}

std::string PB_Polynomial::to_string() const
{
    // return "0b" + this->coefs.to_string();

    // Alternative implementation
    std::string res = "";
    bool found_1 = false;
    for(int i = __FIELD_POWER - 1; i >= 0; --i)
    {
        if(found_1)
            res += this->coefs[i] ? '1' : '0';
        else if(found_1 = this->coefs[i])
            res += '1';
    }

    if(res.size() == 0)
        return "0";

    return res;
}
//

// Arithmetic operations
PB_Polynomial& PB_Polynomial::operator=(const PB_Polynomial& r)
{
    // value to return
    this->coefs = r.coefs;
    return *this; 
}

PB_Polynomial PB_Polynomial::operator+(const PB_Polynomial& r) const
{
    // value to return
    PB_Polynomial res;

    // As we have polynomials over field {0, 1}, we use XOR to add coefs
    res.coefs = this->coefs ^ r.coefs;

    return res; 
}

std::bitset<__DOUBLED_FIELD_POWER> PB_Polynomial::double_bitset_size(const std::bitset<__FIELD_POWER>& st)
{
    std::bitset<__DOUBLED_FIELD_POWER> result;
    for(int i = 0; i < __FIELD_POWER; ++i)
        result[i] = st[i];

    return result;
}

std::bitset<__FIELD_POWER> PB_Polynomial::shrink_bitset_size(const std::bitset<__DOUBLED_FIELD_POWER>& st)
{
    std::bitset<__FIELD_POWER> result;
    for(int i = 0; i < __FIELD_POWER; ++i)
        result[i] = st[i];

    return result;
}

void PB_Polynomial::take_by_p_modulo(std::bitset<__DOUBLED_FIELD_POWER>& value)
{
    // Generate p (make it static?)
    std::bitset<__DOUBLED_FIELD_POWER> p;
    p[__FIELD_POWER] = p[10] = p[2] = p[1] = p[0] = 1;
    
    // We substract (in field 2) add p(x) shifted to corresponding bit, for bits [__FIELD_POWER, __DOUBLED_FIELD_POWER]
    for(int i = __DOUBLED_FIELD_POWER - 1; i >= __FIELD_POWER; --i)
    {
        if(value[i])
            value ^= (p << i - __FIELD_POWER);
    }
}

PB_Polynomial PB_Polynomial::operator*(const PB_Polynomial& right) const
{
    // As result we'll resive poly with maximum of twice size
    std::bitset<__DOUBLED_FIELD_POWER> mult_res_coefs;

    // Adjust values to calculation-convinient width (do it more efficient?)
    std::bitset<__DOUBLED_FIELD_POWER> l = double_bitset_size(this->coefs);
    std::bitset<__DOUBLED_FIELD_POWER> r = double_bitset_size(right.coefs);

    // We will multiply this values with standard algorithm
    for(int i = 0; i < __DOUBLED_FIELD_POWER; ++i, l <<= 1)
    {   
        // Add shifted value, if corresponding bit is 1
        if(r[i])
            mult_res_coefs ^= l;
    }

    // Than we need do adjust our values into our field (take mod p(x))
    take_by_p_modulo(mult_res_coefs);

    return PB_Polynomial(shrink_bitset_size(mult_res_coefs));
}

PB_Polynomial PB_Polynomial::trace(const PB_Polynomial& poly)
{
    // In finite fields trace is sum of Galois conjugates of element, which could
    // be calculated sequentially

    PB_Polynomial result = poly;
    PB_Polynomial current_conjugate = poly;
    for(int i = 1; i < __FIELD_POWER; ++i)
    {
        current_conjugate = current_conjugate.square();
        result.coefs ^= current_conjugate.coefs;
    }
    
    return result;
}

PB_Polynomial PB_Polynomial::square() const
{
    std::bitset<__DOUBLED_FIELD_POWER> square_res_coefs;
    // Use algebraic properties of squaring in field {0, 1}
    for(int i = 0; i < __FIELD_POWER; ++i)
        square_res_coefs[i << 1] = this->coefs[i];

    // Than we need do adjust our values into our field (take mod p(x))
    take_by_p_modulo(square_res_coefs);

    return PB_Polynomial(shrink_bitset_size(square_res_coefs));
}

void PB_Polynomial::in_square()
{
    std::bitset<__DOUBLED_FIELD_POWER> square_res_coefs;
    // Use algebraic properties of squaring in field {0, 1}
    for(int i = 0; i < __FIELD_POWER; ++i)
        square_res_coefs[i << 1] = this->coefs[i];

    // Than we need do adjust our values into our field (take mod p(x))
    take_by_p_modulo(square_res_coefs);
    this->coefs = shrink_bitset_size(square_res_coefs);
}

PB_Polynomial PB_Polynomial::inverse() const
{
    // We'll calculate inverse using Gorner's algorithm (O(1) :))
    // Power vector: 1...10 of len __FIELD_POWER
    PB_Polynomial result = 1;
    
    // __FIELD_POWER - 2: mult + square
    for(int i = 1; i < __FIELD_POWER; ++i)
    {
        result = result * *this;
        result.in_square();    
    }

    return result;
}

std::bitset<__FIELD_POWER> PB_Polynomial::convert_string_to_power(const std::string& ptc)
{
    std::bitset<__FIELD_POWER> res;
    if(ptc[0] == '0' && ptc[1] == 'b')
    {
        // Converting from binary string
        int str_ln = ptc.size() - 3;
        if(str_ln > __FIELD_POWER)
            return 0b0;

        int coef_id = 0;
        for(auto itr = ptc.end() - 1; str_ln >= 0; --str_ln, --itr)
        {
            if(*itr == '1')
                res[coef_id] = 1;
            else if(*itr != '0')
            {
                // Corrupted string
                return 0b0;
            }

            coef_id++;
        }
    }
    else if (ptc[0] == '0' && ptc[1] == 'x')
    {
        // Convering from hex string
        // TODO: last powers check
        int str_ln = ptc.size() - 3;
        if(str_ln > MAX_HEX)
            return 0b0;

        int coef_id = 0;
        for(auto itr = ptc.end() - 1; str_ln >= 0; --str_ln, --itr)
        {
            char curr = *itr;
            unsigned num;
            if(curr >= '0' && curr <= '9')
            {
                num = curr - 48;
            }
            else if(curr >= 'a' && curr <= 'f')
            {
                num = curr - 55;
            }
            else if(curr >= 'A' && curr <= 'F')
            {
                num = curr - 87;
            }
            else
            {
                // Corrupted string
                return 0b0;
            }

            res[coef_id++] = num & 1;
            res[coef_id++] = num & (1 << 1);
            res[coef_id++] = num & (1 << 2);
            res[coef_id++] = num & (1 << 3);
        }
    }
    else
    {
        // TODO: convert from decimal
        return 0b0;
    }

    // std::cout << res;
    return res;
}

PB_Polynomial PB_Polynomial::power(const std::string& pow) const
{
    std::bitset<__FIELD_POWER> c_pow = convert_string_to_power(pow);
    // __FIELD_POWER - 2: mult + square
    PB_Polynomial result = 1;

    for(int i = __FIELD_POWER - 1; i > 0; --i)
    {
        if(c_pow[i])
            result = result * *this;

        result.in_square();    
    }

    if(c_pow[0])
        result = result * *this;

    return result;
}
//

// Compare
bool PB_Polynomial::operator==(const PB_Polynomial& r) const
{
    return this->coefs == r.coefs;
}
//

std::ostream& operator<<(std::ostream& out, const PB_Polynomial& p)
{
    return out << p.to_string();
}