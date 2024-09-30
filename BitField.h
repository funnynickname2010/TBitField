#pragma once
#include <iostream>
#include <math.h>

class BitField
{
	unsigned int* bitarray;
	size_t reserved_ints;
	size_t used_bits;

	unsigned int BitMask(const unsigned int task, const unsigned int location) const;
	size_t IntIndex(const unsigned int bit_index) const;

public:

	const size_t& GetReservedIntSize() const;
	const size_t& GetUsedBitSize() const;

	void TurnOn(const unsigned int index);
	void TurnOff(const unsigned int index);
	bool CheckState(const unsigned int overall_bit_index) const;
	void ChangeSize(const size_t size);

	BitField& operator =(const BitField& obj2);
	bool operator ==(const BitField& obj2) const;

	BitField operator &(const BitField& obj2) const;
	BitField operator |(const BitField& obj2) const;

	BitField();
	BitField(const size_t& n);
	BitField(const BitField& obj2);
	~BitField();
};

