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
    if (this->getIntIndex(bitIndex_) < memSize_) {
        unsigned int bit_mask = this->bitMask(bitIndex_);
        
        if ((bit_mask & pmem_[this->getIntIndex(bitIndex_)]) != 0) {
            result = 1;
        }
    }
    else {
        throw std::out_of_range("BitField::getBitState error: bitIndex_ out of range");
    }
    return result;
}

void BitField::setBitTrue(const unsigned int index)
{
    if (index < bitSize_) {
        pmem_[this->getIntIndex(index)] | this->bitMask(index)
    }
    else {
        throw std::out_of_range("BitField::setBitTrue error: index >= bitSize_");
    }
}

void BitField::setBitFalse(const unsigned int index)
{
    if (index < bitSize_) {
        pmem_[this->getIntIndex(index)] & ~(this->bitMask(index));
    }
    else {
        throw std::out_of_range("BitField::setBitFalse error: index >= bitSize_");
    }
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
    memSize_ = obj2.memSize_;
    bitSize_ = obj2.bitSize_;
    try {
        pmem_ = new unsigned int[memSize_];
        for (size_t i = 0; i < memSize_; i++) {
            pmem_[i] = obj2.pmem_[i];
        }
    }
    catch (std::exception& e) {
        throw;
    }
    return *this;
}

bool BitField::operator==(const BitField& obj2) const
{
    bool result = 1;

    if (memSize_ != obj2.memSize_ || bitSize_ != obj2.bitSize_) {
        result = 0;
    }
    else if (pmem_ != obj2.pmem_) {
        for (size_t i = 0; i < memSize_; i++) {
            if (pmem_[i] != obj2.pmem_[i]) {
                result = 0;
            }
        }
    }

    return result;
}

BitField BitField::operator&(const BitField& obj2) const
{
    size_t up_bound = std::min(bitSize_, obj2.bitSize_);
    BitField bf_result(up_bound);

    for (size_t i = 0; i < up_bound; i++) {
        if (this->getBitState(i) & obj2.getBitState(i)) {
            bf_result.setBitTrue(i);
        }
        else {
            bf_result.setBitFalse(i);
        }
    }

    return bf_result;
}

BitField BitField::operator|(const BitField& obj2) const
{
    unsigned int bigger_field;
    size_t low_bound = 0;
    size_t up_bound = 0;

    if (bitSize_ < obj2.bitSize_) { 
        bigger_field = 1; 
        up_bound = obj2.bitSize_;
        low_bound = bitSize_;
    }
    else {
        bigger_field = 0;
        up_bound = bitSize_;
        low_bound = obj2.bitSize_;
    }

    BitField bf_result(up_bound);

    for (size_t i = 0; i < low_bound; i++) {
        if (this->getBitState(i) | obj2.getBitState(i)) {
            bf_result.setBitTrue(i);
        }
        else {
            bf_result.setBitFalse(i);
        }
    }

    bool t_loop_state;
    for (size_t j = low_bound; j < up_bound; j++) {
        if (bigger_field == 0) { t_loop_state = this->getBitState(j); }
        else { t_loop_state = obj2.getBitState(j); }

        if (t_loop_state) { bf_result.setBitTrue(j); }
        else { bf_result.setBitFalse(j); }
    }

    return bf_result;
}

BitField::BitField(const size_t& n)
{
    bitSize_ = n;
    this->getIntIndex(n);
    memSize_ = (n + 1);
    try {
        pmem_ = new unsigned int[memSize_];
    }
    catch (std::exception& e) {
        throw;
    }

    for (size_t i = 0; i < memSize_; i++) {
        pmem_[i] = unsigned(0);
    }
}

BitField::BitField(const BitField& obj2)
{
    bitSize_ = obj2.bitSize_;
    memSize_ = obj2.memSize_;
    try {
        pmem_ = new unsigned int[memSize_];
    }
    catch (std::exception& e) {
        throw;
    }  

    for (size_t i = 0; i < memSize_; i++)
    {
        pmem_[i] = obj2.pmem_[i];
    }
}

BitField::~BitField()
{
    delete[] pmem_;
}

std::ostream& operator <<(std::ostream& os, BitField& obj)
{
    try {
        for (size_t i = 0; i < obj.bitSize_; i++) {
            os << obj.getBitState(i);
        }
    }
    catch (std::exception& e) {
        throw;
    }
    return os;
}

std::istream& operator >>(std::istream& is, BitField& obj)
{
    std::string i_buffer = "";

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
    }
    std::getline(is >> std::ws, i_buffer);

    try {
        for (size_t i = 0; i < i_buffer.size(); i++) {
            char c_temp = i_buffer[i];

            if (c_temp == '1') {
                obj.setBitTrue(i);
            }
            else if (c_temp == '0') {
                obj.setBitFalse(i);
            }
            else {
                break;
            }
        }
    }
    catch (std::exception& e) {
        throw;
    }

}
