#pragma once
#include <common.h>
#include <io.h>

class Bus{
public:
    //  link components
    bool set_ptr_io(IO* io);
    void clear_ptrs();

    //  bus activity
    u8 fetch_irq(u16 address);
    u8 read(u16 address);
    void write(u16 address, u8 value);
    void idle();

private:
    IO* io;

};