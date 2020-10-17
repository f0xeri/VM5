//
// Created by Yaroslav on 05.09.2020.
//

#include "Processor.h"

Processor::Processor()
{
    InitCommands();
}

void Processor::Run()
{
    while (regs.psw.IF != 0)
    {
        auto currentCmd = GetCommand(memory, regs.psw.IP);
        regs.currentCommand = currentCmd;
        if (currentCmd.cmd.opcode)
            commands[currentCmd.cmd.opcode]->operator()(memory, regs);
        else
            regs.psw.IF = 0;
        regs.psw.IP += sizeof(MemUnion);
    }
}

void Processor::SetIP(unsigned short address)
{
    regs.psw.IP = address;
}

void Processor::InitCommands()
{
    commands.assign(128, nullptr);
    commands[stop] = new Stop();
    commands[ldstr] = new LoadString();
    commands[prtstr] = new PrintString();
}

command16 Processor::GetCommand16(const Memory &mem, unsigned char address)
{
    MemUnion dat{};
    for (int j = address, k = 0; j < (address + sizeof(MemUnion)); ++j, ++k)
        dat.bytes[k] = mem.memory[j];
    return dat.cmd16;
}

command32 Processor::GetCommand(const Memory &mem, unsigned char address) {
    MemUnion dat{};
    for (int j = address, k = 0; j < (address + sizeof(MemUnion)); ++j, ++k)
        dat.bytes[k] = mem.memory[j];
    return dat.cmd32;
}
