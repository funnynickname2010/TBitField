#pragma once
#include <iostream>
#include <math.h>

class BitField
{	unsigned int* pmem_;
	unsigned int memSize_;
	unsigned int bitSize_;

	unsigned int getIntIndex(const unsigned int bitIndex_) const;
	unsigned int bitMask(const unsigned int location) const;

public:

	size_t getMemSize() const;
	size_t getBitSize() const;
	bool getBitState(const unsigned int bitIndex_) const;

	void setBitTrue(const size_t index);
	void setBitFalse (const size_t index);
	void resize(const size_t size);

	BitField& operator =(const BitField& obj2);
	bool operator ==(const BitField& obj2) const;
	BitField operator &(const BitField& obj2) const;
	BitField operator |(const BitField& obj2) const;

	BitField(const size_t& n);
	BitField(const BitField& obj2);
	~BitField();
};

