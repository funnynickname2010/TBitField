#pragma once
#include <iostream>
#include <math.h>


class BitField
{
public:

	unsigned int* bitarray;
	size_t reserved_ints;
	size_t used_bits;

	unsigned int BitMask(unsigned int task, size_t location);

	void TurnOn(size_t index);
	void TurnOff(size_t index);
	bool CheckState(size_t index);
	void ChangeSize(size_t size);

	BitField& operator =(const BitField& obj2);
	bool operator ==(const BitField& obj2);

	BitField operator &(const BitField& obj2);
	BitField operator |(const BitField& obj2);

	BitField(); //Make a constant
	BitField(size_t& n);
	BitField(BitField& obj2);
	~BitField();
};