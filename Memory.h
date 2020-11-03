//
// Created by Yaroslav on 16.10.2020.
//

#ifndef VM7_MEMORY_H
#define VM7_MEMORY_H


#include <cstdint>
#include "Types.h"

class Memory
{
public:
    Memory() {}
    ~Memory() { }

    void LoadData(uint16_t address, const data &dat);
    void LoadData(uint16_t a, MemUnion dat, int n);
    data GetData(uint16_t address) noexcept;

    int32_t memory[65536];
};


#endif //VM7_MEMORY_H
