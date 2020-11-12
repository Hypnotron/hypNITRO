#pragma once
#include "types.hpp"

template <typename DataType>
inline constexpr void setBits(
        const std::size_t& mask, 
        DataType& data, 
        const DataType& value) {
    data &= ~(static_cast<DataType>(mask));
    data |= value & mask;
}
template <u8 position, typename DataType>
inline constexpr void setBit(DataType& data, const bool& value) {
    data &= ~(static_cast<DataType>(1) << position);
    data |= static_cast<DataType>(value) << position;
}
