#include "BitField.h"

unsigned int BitField::getIntIndex(const unsigned int bitIndex_) const
{
    return (bitIndex_ >> 5);
}

unsigned int BitField::bitMask(const unsigned int index) const
{
    return (1 << (index & 32));
}

size_t BitField::getMemSize() const
{
    return size_t(memSize_);
}

size_t BitField::getBitSize() const
{
    return size_t(bitSize_);
}

bool BitField::getBitState(const unsigned int bitIndex_) const
{
    bool result = 0;
    if (bitIndex_ < memSize_) {
        unsigned int bit_mask = this->bitMask(bitIndex_);
        
        if ((bit_mask & pmem_[this->getIntIndex(bitIndex_)]) != 0) {
            result = 1;
        }
    }
    else {
        throw std::invalid_argument("Error: bitIndex_ out of range");
    }
    return result;
}

void BitField::setBitTrue(const unsigned int index)
{
    pmem_[this->getIntIndex(index)] | this->bitMask(index);
}

void BitField::setBitFalse(const unsigned int index)
{
    pmem_[this->getIntIndex(index)] & ~(this->bitMask(index));
}

void BitField::resize(const size_t size)
{
    if ((bitSize_ < size) && (memSize_ <= (size >> 5))) {
        unsigned int new_mem_size = ((size + 31) >> 5);
        unsigned int* temp_mem = nullptr;

        try {
             temp_mem = new unsigned int[new_mem_size];
        }
        catch (std::exception& e) {
            throw;
        }

        for (size_t i = 0; i < memSize_; i++) {
            temp_mem[i] = pmem_[i]; //It really is fine
        }
        for (unsigned int j = memSize_; j < new_mem_size; j++) {
            temp_mem[j] = unsigned int(0);
        }

        delete[] pmem_;
        pmem_ = temp_mem;
        memSize_ = new_mem_size;
        bitSize_ = size;
    }
    else if (((bitSize_ < size) && (memSize_ > (size >> 5)))) {
        bitSize_ = size;
    }
}

BitField& BitField::operator=(const BitField& obj2)
{
    // TODO: вставьте здесь оператор return
}
