#pragma once
#include <common.h>

enum IOName{
    JOYP = 0x00,
    SB = 0x01,
    SC = 0x02,
    DIV = 0x04,
    TIMA = 0x05,
    TMA = 0x06,
    TAC = 0x07,
    IF = 0x0f,

    //SOUND IO GOES HERE

    LCDC = 0x40,
    STAT = 0x41,
    SCY = 0x42,
    SCX = 0x43,
    LY = 0x44,
    LYC = 0x45,
    DMA = 0x46,
    BGP = 0x47,
    OBP0 = 0x48,
    OBP1 = 0x49,
    WY = 0x4a,
    WX = 0x4b
};
struct IO{
    u8 joyp;
    u8 sb, sc;
    u8 div, tima, tma, tac;
    u8 iF;

    //sound io goes here

    u8 lcdc, stat, scy, scx, ly, lyc, bgp, obp0, obp1, wy, wx;
    u8 dma;

    IO(bool use_boot_rom = false){
        if(use_boot_rom){
            joyp = 0xff;
            sb = 0x00;
            sc = 0x00;
            div = 0x00;
            tima = 0x00;
            tma = 0x00;
            tac = 0x00;
            iF = 0x00;
            lcdc = 0x00;
            stat = 0x00;
            scy = 0x00;
            scx = 0x00;
            ly = 0x00;
            lyc = 0x00;
            bgp = 0x00;
            obp0 = 0x00;
            obp1 = 0x00;
            wy = 0x00;
            wx = 0x00;
            dma = 0xff;
        }
        else{
            joyp = 0xff;
            sb = 0x00;
            sc = 0x7e;
            div = 0xab;
            tima = 0x00;
            tma = 0x00;
            tac = 0xf8;
            iF = 0xe1;
            lcdc = 0x91;
            stat = 0x85;
            scy = 0x00;
            scx = 0x00;
            ly = 0x00;
            lyc = 0x00;
            bgp = 0xfc;
            obp0 = 0xff;
            obp1 = 0xff;
            wy = 0x00;
            wx = 0x00;  
            dma = 0xff;
        }
    }
    u8 read(u8 address_masked){
        switch (address_masked)
        {
        case JOYP: return joyp;
        case SB: return sb;
        case SC: return sc;
        case DIV: return div;
        case TIMA: return tima;
        case TMA: return tma;
        case TAC: return tac;
        case IF: return iF;
        case LCDC: return lcdc;
        case STAT: return stat;
        case SCY: return scy;
        case SCX: return scx;
        case LY: return ly;
        case LYC: return lyc;
        case BGP: return bgp;
        case OBP0: return obp0;
        case OBP1: return obp1;
        case WY: return wy; 
        case WX: return wx;
        case DMA: return dma;
           
        default: return 0xff;
        }
    }
    void write(u8 address_masked, u8 value){
        switch (address_masked)
        {
        case JOYP: joyp = value;
        case SB: sb = value;
        case SC: sc = value;
        case DIV: div = value;
        case TIMA: tima = value;
        case TMA: tma = value;
        case TAC: tac = value;
        case IF: iF = value;
        case LCDC: lcdc = value;
        case STAT: stat = value;
        case SCY: scy = value;
        case SCX: scx = value;
        case LY: ly = value;
        case LYC: lyc = value;
        case BGP: bgp = value;
        case OBP0: obp0 = value;
        case OBP1: obp1 = value;
        case WY: wy = value; 
        case WX: wx = value;
        case DMA: dma = value;
           
        default: return;
        }
    }
};