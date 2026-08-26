#pragma once
#include <common.h>

enum JRegisters{
    AF = 0,
    BC = 1,
    DE = 2,
    HL = 3
};
struct Registers{
    u8 a, f, b, c, d, e, h, l;
    u16 pc, sp;

    Registers(bool use_boot_rom = false){
        if(use_boot_rom){
            //clear registers, set during boot rom execution
            a = 0x00; f = 0x00; b = 0x00; c = 0x00;
            d = 0x00; e = 0x00; h = 0x00; l = 0x00;

            pc = 0x0000; sp = 0x0000;
        }
        else{
            //set to post boot rom values
            a = 0x01; f = 0xb0; b = 0x00; c = 0x13;
            d = 0x00; e = 0xd8; h = 0x01; l = 0x4d;

            pc = 0x0100; sp = 0xfffe;
        }
    }

    void set_jregister(JRegisters reg, u16 value){
        switch (reg){
        case AF:
            a = value >> 8;
            f = value & 0xf0;
            break;
        case BC:
            b = value >> 8;
            c = value & 0xff;
            break;
        case DE:
            d = value >> 8;
            e = value & 0xff;
            break;
        case HL:
            h = value >> 8;
            l = value & 0xff;
            break;
        default:
            break;
        }
    }
    u16 get_jregister(JRegisters reg){
        switch (reg){
        case AF:
            return u16(a << 8 | f);
            break;
        case BC:
            return u16(b << 8 | c);
            break;
        case DE:
            return u16(d << 8 | e);
            break;
        case HL:
            return u16(h << 8 | l);
            break;
        default:
            return 0xffff;
        }
    }
};

enum Flag{
    Z = 7,
    N = 6,
    H = 5,
    C = 4
};
struct Flags{
    bool zero;
    bool sub;
    bool half;
    bool carry;

    Flags(bool use_boot_rom = false){
        if(use_boot_rom){
            zero = false; sub = false; half = false; carry = false;
        }
        else{
            zero = true; sub = false; half = true; carry = true; //todo: check header checksum for h/c flags
        }
    }

    void set_flag(u8& f, Flag flag, bool condition){
        if(condition){
            f &= (0x01 << flag);
        }
        else{
            f |= ~(0x01 << flag);
        }

        switch (flag){
        case Z:
            zero = condition;
            break;
        case N: 
            sub = condition;
            break;
        case H:
            half = condition;
            break;
        case C:
            carry = condition;
            break;
        }
    }

    bool get_flag(Flag flag){
        switch (flag){
        case Z:
            return zero;
        case N: 
            return sub;
        case H:
            return half;
        case C:
            return carry;
        }

        return false;
    }
};