#pragma once
#include <array>
#include <cstddef>

template <
        typename DataType, 
        typename SizeType,
        SizeType modeCount, 
        SizeType virtualSize, 
        SizeType actualSize> 
class Bank {
    protected:
        std::array<DataType, actualSize> data;

    public:
        std::array<SizeType, modeCount * virtualSize> bank; 
        SizeType mode; 

        Bank() {}

        DataType& operator[](const SizeType& index) const { 
            //Mode-major ordering for bank:
            return data[bank[mode * modeCount + index]];
        }
};

