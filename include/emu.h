#pragma once
#include <common.h>
#include <cpu.h>
#include <bus.h>
#include <io.h>

class Emu{
public:
    //  constructor and destructor
    Emu();
    ~Emu();

private:
    //  private vars

    //  components
    CPU cpu;
    Bus bus;
    IO io;
};