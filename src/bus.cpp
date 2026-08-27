#include <bus.h>

//link components
bool Bus::set_ptr_io(IO* io){
    this->io = io;

    if(this->io){
        return true;
    }

    return false;
}
void Bus::clear_ptrs(){
    io = nullptr;
}

//bus activity
u8 Bus::fetch_irq(u16 address){
    //tick()
    //tick()
    //tick()
    //check irq
    //tick()
    //return value
}
u8 Bus::read(u16 address){
    if(address < 0x8000){
        //cart rom
    }
    else if(address >= 0x8000 && address < 0xa000){
        //vram
    }
    else if(address >= 0xa000 && address < 0xc000){
        //external ram (cart)
    }
    else if(address >= 0xc000 && address < 0xd000){
        //wram bank 0
    }
    else if(address >= 0xd000 && address < 0xe000){
        //wram bank 1
    }
    else if(address >= 0xe000 && address < 0xfe00){
        //echo
    }
    else if(address >= 0xfe00 && address < 0xfea0){
        //oam
    }
    else if(address >= 0xff00 && address < 0xff80){
        u8 address_masked = address & 0xff;
        return io->read(address_masked);
    }
    else if(address >= 0xff80 && address < 0xffff){
        //hram
    }
    else if(address == 0xffff){
        //ie
    }

    return 0xff;
}
void Bus::write(u16 address, u8 value){
    if(address < 0x8000){
        //cart rom
    }
    else if(address >= 0x8000 && address < 0xa000){
        //vram
    }
    else if(address >= 0xa000 && address < 0xc000){
        //external ram (cart)
    }
    else if(address >= 0xc000 && address < 0xd000){
        //wram bank 0
    }
    else if(address >= 0xd000 && address < 0xe000){
        //wram bank 1
    }
    else if(address >= 0xe000 && address < 0xfe00){
        //echo
    }
    else if(address >= 0xfe00 && address < 0xfea0){
        //oam
    }
    else if(address >= 0xff00 && address < 0xff80){
        u8 address_masked = address & 0xff;
        io->write(address_masked, value);
    }
    else if(address >= 0xff80 && address < 0xffff){
        //hram
    }
    else if(address == 0xffff){
        //ie
    }
}
void Bus::idle(){
    //idle other components here to keep everything in sync
}
