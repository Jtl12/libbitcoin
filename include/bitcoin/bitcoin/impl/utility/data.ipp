/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_DATA_IPP
#define LIBBITCOIN_DATA_IPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <bitcoin/bitcoin/utility/assert.hpp>

namespace libbitcoin {

inline byte_array<1> to_byte(uint8_t byte)
{
    return byte_array<1>{{byte}};
}

inline data_chunk build_data(std::initializer_list<data_slice> slices,
    size_t extra_space)
{
    size_t size = 0;
    for (const auto slice: slices)
        size += slice.size();

    data_chunk out;
    out.reserve(size + extra_space);
    for (const auto slice: slices)
        out.insert(out.end(), slice.begin(), slice.end());

    return out;
}

template <typename Data>
data_chunk to_data_chunk(Data iterable)
{
    return data_chunk(std::begin(iterable), std::end(iterable));
}

template <typename Data, typename Type>
void extend_data(Data& buffer, const Type& other)
{
    buffer.insert(std::end(buffer), std::begin(other), std::end(other));
}

template <typename Value>
Value range_constrain(Value value, Value minimum, Value maximum)
{
    if (value < minimum)
        return minimum;

    if (value > maximum)
        return maximum;

    return value;
}

template <typename Data>
static data_chunk slice(const Data& buffer, size_t start, size_t end)
{
    BITCOIN_ASSERT(start <= buffer.size());

    const auto& data = buffer.data();
    return data_chunk
    {
        &data[start], &data[end]
    };
}

template <typename Data>
void split(Data& buffer, data_chunk& lower, data_chunk& upper, size_t size)
{
    BITCOIN_ASSERT(buffer.size() == size);

    const size_t front = size / 2;
    const size_t rest = size - front;
    lower.assign(buffer.begin(), buffer.end() - front);
    upper.assign(buffer.begin() + rest, buffer.end());
}

} // namespace libbitcoin

#endif
