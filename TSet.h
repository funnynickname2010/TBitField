#pragma once
#include "BitField.h"

class TSet
{
public:

	unsigned int size;
	BitField bitfield_set;
	
	TSet(const unsigned int size);
	TSet(const TSet& op2);
	TSet(const BitField& bitfield_op);
	

};

