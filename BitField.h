#pragma once
#include <iostream>
#include <math.h>

class BitField
{	unsigned int* pmem_;
	unsigned int memSize_;
	unsigned int bitSize_;

	unsigned int getIntIndex(const unsigned int bit_index) const;
	unsigned int bitMask(const unsigned int index) const;

public:

	size_t getMemSize() const;
	size_t getBitSize() const;
	bool getBitState(const unsigned int index) const;

	void setBitTrue(const unsigned int index);
	void setBitFalse (const unsigned int index);
	void resize(const size_t size);

	BitField& operator =(const BitField& obj2);
	bool operator ==(const BitField& obj2) const;
	BitField operator &(const BitField& obj2) const;
	BitField operator |(const BitField& obj2) const;

	BitField(const size_t& n);
	BitField(const BitField& obj2);
	~BitField();

	friend std::istream& operator >>(std::istream& is, BitField& obj);
	friend std::ostream& operator <<(std::ostream& os, BitField& obj);
};

