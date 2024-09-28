#include "BitField.h"

#ifdef DEFAULT_CONSTRUCTOR

	BitField::BitField()
	{
		bitarray = new unsigned int[1];
		used_bits = 0;
		reserved_ints = 1;

		for (size_t i = 0; i < reserved_ints; i++)
		{
			bitarray[i] = 0;
		}
	}

#endif // DEFAULT_CONSTRUCTOR

	const size_t& BitField::GetReservedIntSize() const
	{
		return reserved_ints;
	}

	const size_t& BitField::GetUsedBitSize() const
	{
		return used_bits;
	}

	void BitField::TurnOn(const size_t index)
{
	bitarray[index >> 5] = (bitarray[index >> 5] | BitMask(0, (index & 31)));
}

void BitField::TurnOff(const size_t index)
{
	bitarray[index >> 5] = (bitarray[index >> 5] & BitMask(1, (index & 31)));
}

bool BitField::CheckState(const size_t index) const
{
	size_t op1 = (index >> 5);
	size_t op2 = (31 & index);
	int res1 = bitarray[op1];
	int	res2 = BitMask(2, op2);
	int res3 = (res1 & res2);
	bool res_final = (res3 != 0);

	return res_final;
}

unsigned int BitField::BitMask(const unsigned int task, const size_t location) const
{
	unsigned int result;

	switch (task)
	{
	case 0:

		result = 1 << location;
		break;

	case 1:

		result = ~(1 << location);
		break;

	default:

		throw (std::invalid_argument("Error. BitField::BitMask(...) incorrect parameter input."));
		break;
	}

	return result;
}

BitField::BitField(const size_t& n)
{
	bitarray = new unsigned int[n];
	used_bits = 0;
	reserved_ints = n;

	for (size_t i = 0; i < reserved_ints; i++)
	{
		bitarray[i] = 0;
	}
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

void BitField::ChangeSize(const size_t size)
{
	size_t int_size = ((size >> 5) + 1);

	if (reserved_ints < int_size)
	{
		BitField result(int_size);

		for (size_t i = 0; i < ((used_bits >> 5) + 1); i++)
		{
			result.bitarray[i] = bitarray[i];
		}
		
		result.used_bits = size;

		*this = result; //This is double copying, but I need move semantics otherwise, we haven't learned that yet and I'm kinda tired, so that will do for now
	}
	else
	{
		used_bits = size;
	}
}
