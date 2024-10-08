#include "BitField.h"

BitField::BitField() //Why does it give of a failure if I don't initialize the second field? Optimization?
{
	bitarray = new unsigned int[2]; //So it doesn't count as an array if it's just one element? What?
	used_bits = 0;
	reserved_ints = 1;

	bitarray[0] = 0;
	bitarray[1] = 0;
}

const size_t& BitField::GetReservedIntSize() const
{
	return reserved_ints;
}

const size_t& BitField::GetUsedBitSize() const
{
	return used_bits;
}

void BitField::TurnOn(const unsigned int index)
{
	bitarray[this->IntIndex(index)] = (bitarray[this->IntIndex(index)] | BitMask(0, (index & 31)));
}

void BitField::TurnOff(const unsigned int index)
{
	bitarray[this->IntIndex(index)] = (bitarray[this->IntIndex(index)] & BitMask(1, (index & 31)));
}

bool BitField::CheckState(const unsigned int overall_bit_index) const
{
	unsigned int real_bit_index = (overall_bit_index & 31);
	unsigned int bmask = BitMask(0, real_bit_index); //Creating the bit mask, it has every bit except bit_index equal to 0.
	//Using bit multiplication & to get either 0...010...0 or 0...0.

	return !((bmask & bitarray[this->IntIndex(overall_bit_index)]) == 0);
}

unsigned int BitField::BitMask(const unsigned int task, const unsigned int location) const
{
	unsigned int result;

	switch (task)
	{
	case 0:

		result = (1 << location);
		break;

	case 1:

		result = ~(1 << location);
		break;

	default:

		throw std::invalid_argument("Error. BitField::BitMask(...) incorrect parameter input.");
		break;
	}

	return result;
}

size_t BitField::IntIndex(const unsigned int bit_index) const
{
	return (bit_index >> 5);
}

BitField::BitField(const size_t& n)
{
	used_bits = n;
	reserved_ints = this->IntIndex(n);
	bitarray = new unsigned int[reserved_ints];

	std::fill_n(bitarray, reserved_ints, 0);
}

BitField::BitField(const BitField& obj2)
{
	used_bits = obj2.used_bits;
	reserved_ints = obj2.reserved_ints;
	bitarray = new unsigned int[obj2.reserved_ints];

	for (size_t i = 0; i < reserved_ints; i++)
	{
		bitarray[i] = obj2.bitarray[i];
	}
}

BitField::~BitField()
{
	delete[] bitarray;
}

bool BitField::operator ==(const BitField& obj2) const
{
	bool result = 1;

	if (reserved_ints != obj2.reserved_ints || used_bits != obj2.used_bits)
	{
		result = 0;
	}
	else
	{
		for (size_t i = 0; i < reserved_ints; i++)
		{
			if (bitarray[i] != obj2.bitarray[i])
			{
				result = 0;
				break;
			}
		}
	}

	return result;
}

BitField& BitField::operator =(const BitField& obj2)
{
	if (this != &obj2)
	{
		if (reserved_ints != obj2.reserved_ints)
		{
			reserved_ints = obj2.reserved_ints;
			bitarray = new unsigned int[obj2.reserved_ints];
		}

		for (size_t i = 0; i < reserved_ints; i++)
		{
			bitarray[i] = obj2.bitarray[i];
		}

		used_bits = obj2.used_bits;
	}

	return *this;
}

BitField BitField::operator &(const BitField& obj2) const
{
	unsigned int result_bitfield_size;
	int smaller_bitfield_size;

	if (reserved_ints >= obj2.reserved_ints)
	{
		result_bitfield_size = reserved_ints;
		smaller_bitfield_size = obj2.reserved_ints;
	}
	else
	{
		result_bitfield_size = obj2.reserved_ints;
		smaller_bitfield_size = reserved_ints;
	}

	BitField result(result_bitfield_size);

	if (used_bits > obj2.used_bits)
	{
		result.used_bits = used_bits;
	}
	else
	{
		result.used_bits = obj2.used_bits;
	}

	for (size_t i = 0; i < smaller_bitfield_size; i++)
	{
		result.bitarray[i] = (bitarray[i] & obj2.bitarray[i]);
	}

	return result;
}

BitField BitField::operator |(const BitField& obj2) const
{
	unsigned int result_bitfield_size;
	int smaller_bitfield_size;

	if (reserved_ints >= obj2.reserved_ints)
	{
		result_bitfield_size = reserved_ints;
		smaller_bitfield_size = obj2.reserved_ints;
	}
	else
	{
		result_bitfield_size = obj2.reserved_ints;
		smaller_bitfield_size = reserved_ints;
	}

	BitField result(result_bitfield_size);

	if (used_bits > obj2.used_bits)
	{
		result.used_bits = used_bits;
	}
	else
	{
		result.used_bits = obj2.used_bits;
	}

	for (size_t i = 0; i < smaller_bitfield_size; i++)
	{
		result.bitarray[i] = (bitarray[i] | obj2.bitarray[i]);
	}

	if (smaller_bitfield_size == reserved_ints)
	{
		for (unsigned int i = smaller_bitfield_size; i < obj2.reserved_ints; i++)
		{
			result.bitarray[i] = obj2.bitarray[i];
		}
	}
	else if (smaller_bitfield_size == obj2.reserved_ints)
	{
		for (unsigned int i = smaller_bitfield_size; i < reserved_ints; i++)
		{
			result.bitarray[i] = bitarray[i];
		}
	}

	return result;
}

void BitField::ChangeSize(const size_t bit_size)
{
	size_t int_size = this->IntIndex(bit_size);

	if (reserved_ints < int_size)
	{
		BitField result(bit_size);
		std::fill_n(result.bitarray, result.reserved_ints, unsigned int(0));

		for (size_t i = 0; i < reserved_ints; i++)
		{
			result.bitarray[i] = bitarray[i];
		}

		delete[] bitarray;

		bitarray = result.bitarray;
		reserved_ints = result.reserved_ints;
	}

	used_bits = bit_size;
}
