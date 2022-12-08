#include "GNBP_Variant_2.hpp"

// Include area

#include <iostream>

//

#define MAX_HEX 11
#define MAX_DEC 18
#define LOG_OF_POWER 8

// Multiplication matrix generation

bool NB_Polynomial::multiplication_matrix_generated = false;

std::bitset<__FIELD_POWER> NB_Polynomial::mult_matrix[173];

template<int N>
struct PowOf2
{
    constexpr PowOf2() : arr()
    {
        constexpr int p = 2 * __FIELD_POWER + 1;
        for(int i = 0; i < N; ++i)
        {
            unsigned val = 1u;
            for(int j = 0; j < i; ++j)
            {
                val = (val << 1) % p;
            }
            arr[i] = val;
        }
    }
    int arr[N];
};

void NB_Polynomial::generate_mult_matrix()
{
    constexpr int p = 2 * __FIELD_POWER + 1;
    constexpr auto pow_of_2 = PowOf2<173>();

    for(int i = 0; i < __FIELD_POWER; ++i)
    {
        for(int j = 0; j < __FIELD_POWER; ++j)
        {
            int v_1 = pow_of_2.arr[i] + pow_of_2.arr[j];
            int v_2 = pow_of_2.arr[i] - pow_of_2.arr[j];
            int v_3 = -pow_of_2.arr[i] + pow_of_2.arr[j];
            int v_4 = -pow_of_2.arr[i] - pow_of_2.arr[j];
            mult_matrix[i][j] = (v_1 % p == 1 || (v_1 % p) + p == 1)
                             || (v_2 % p == 1 || (v_2 % p) + p == 1)
                             || (v_3 % p == 1 || (v_3 % p) + p == 1)
                             || (v_4 % p == 1 || (v_4 % p) + p == 1);
        }
    }
}

//


// Constructors and destructors
NB_Polynomial::NB_Polynomial() : coefs{0b0}, bit_length{__FIELD_POWER} 
{
    if(!multiplication_matrix_generated)
    {
        generate_mult_matrix();
        multiplication_matrix_generated = true;
    }
}

NB_Polynomial::NB_Polynomial(bool cnst) : bit_length{__FIELD_POWER} 
{
    if(!multiplication_matrix_generated)
    {
        generate_mult_matrix();
        multiplication_matrix_generated = true;

        for(int i = 0; i < __FIELD_POWER; ++i)
        {
            for(int j = 0; j < __FIELD_POWER; ++j)
            {
                std::cout << mult_matrix[i][j];
            }
            std::cout << std::endl;
        }
    }

    if(cnst)
    {
        // In NB 1 represented as (1....1)
        for(int i = 0; i < __FIELD_POWER; ++i)
        {
            coefs[i] = 1;
        }
    }
}

NB_Polynomial::NB_Polynomial(const NB_Polynomial& othr) : bit_length{othr.bit_length}
{
    this->coefs = othr.coefs;
}

NB_Polynomial::NB_Polynomial(const std::bitset<__FIELD_POWER>& bit_repr) : coefs{bit_repr}, bit_length{__FIELD_POWER} 
{
    if(!multiplication_matrix_generated)
    {
        generate_mult_matrix();
        multiplication_matrix_generated = true;
    }
}

NB_Polynomial::NB_Polynomial(const std::string& string_repr) : bit_length{__FIELD_POWER} 
{
    if(!multiplication_matrix_generated)
    {
        generate_mult_matrix();
        multiplication_matrix_generated = true;
    }

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

NB_Polynomial NB_Polynomial::operator*(const NB_Polynomial& right) const
{
    std::bitset<__FIELD_POWER> res_coefs;

    std::bitset<__FIELD_POWER> left_temp = this->coefs;
    std::bitset<__FIELD_POWER> right_temp = right.coefs;
    for(int i = 0; i < __FIELD_POWER; ++i)
    {
        
        std::bitset<__FIELD_POWER> first_mult = 0b0;
        for(int j = 0; j < __FIELD_POWER; ++j)
        {
            for(int k = 0; k < __FIELD_POWER; ++k)
            {
                first_mult[j] = first_mult[j] ^ (left_temp[j] && mult_matrix[j][k]);
            }
        }

        for(int k = 0; k < __FIELD_POWER; ++k)
        {
            res_coefs[i] = res_coefs[i] ^ (first_mult[k] && right_temp[k]);
        }
    }

    return NB_Polynomial(res_coefs);
}

int NB_Polynomial::trace(const NB_Polynomial& poly)
{
    // In NB trace of element is equal to sum of it's coefficients (+ == ^)
    int result = 0;
    for(int i = 0; i < __FIELD_POWER; ++i)
    {
        result ^= (int)poly.coefs[i];
    }
    return result;
}

NB_Polynomial NB_Polynomial::square() const
{
    // In NB square of element is equal to element with cycle shifted to right coefs
    return NB_Polynomial(cycle_shift_right(this->coefs, 1));
}

NB_Polynomial NB_Polynomial::inverse() const
{
    // To calculate inverse in NB we will use Itoh-Tsujii algorithm (Modified Gorner to use more squares)
    NB_Polynomial result = *this;
    unsigned k = 1u;
    unsigned to_pow = (unsigned)__FIELD_POWER - 1u;

    NB_Polynomial temp(1);
    for(int i = LOG_OF_POWER - 1; i >= 0; --i)
    {
        temp = result;
        for(int j = 0; j < k; ++j)
        {
            result = result.square();
        }
        result = result * temp;

        // if m_i == 1
        if(to_pow & (1u << i))
        {
            result = result.square() * *this;
            ++k;
        }
    }

    return result.square();
}

void NB_Polynomial::in_square()
{
    this->coefs = cycle_shift_right(this->coefs, 1);
}

std::bitset<__FIELD_POWER> NB_Polynomial::convert_string_to_power(const std::string& ptc)
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

NB_Polynomial NB_Polynomial::power(const std::string& pow) const
{
    std::bitset<__FIELD_POWER> c_pow = convert_string_to_power(pow);
    // __FIELD_POWER - 2: mult + square
    NB_Polynomial result = 1;

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
// 1 to 0
std::bitset<__FIELD_POWER> NB_Polynomial::cycle_shift_left(const std::bitset<__FIELD_POWER>& in, int i)
{
    return (in >> i) ^ (in << __FIELD_POWER - i);       // shifts 1 to 0, 2 to 1, and so on 0 to __FIELD_POWER-1
}

void NB_Polynomial::cycle_shift_left_self(std::bitset<__FIELD_POWER>& in, int i)
{
    in = (in >> i) ^ (in << __FIELD_POWER - i);
}

// 0 to 1
std::bitset<__FIELD_POWER> NB_Polynomial::cycle_shift_right(const std::bitset<__FIELD_POWER>& in, int i)
{
    return (in << i) ^ (in >> __FIELD_POWER - i);      // shifts 0 to 1, 1 to 2, and so on
}

void NB_Polynomial::cycle_shift_right_self(std::bitset<__FIELD_POWER>& in, int i)
{
    in = (in << i) ^ (in >> __FIELD_POWER - i);
}


// Compare
bool NB_Polynomial::operator==(const NB_Polynomial& r) const
{
    return this->coefs == r.coefs;
}
//

std::ostream& operator<<(std::ostream& out, const NB_Polynomial& p)
{
    return out << p.to_string();
}