#pragma once
#include <common.h>
#include <instructions.h>
#include <registers.h>
#include <bus.h>

class CPU{
public:
    //execution
    int run(Bus& bus);

private:
    //private vars
    Registers m_registers;
    Flags m_flags;

    u8 m_opcode = 0x00;
    bool m_prefixed = false;

    //execution
    u8 fetch_opcode(Bus& bus);
    int execute_opcode(Bus& bus);
    int execute_prefix(Bus& bus);

    //8 bit load instructions
    int ld_r_r(u8& dest, u8 src);
    int ld_r_n(Bus& bus, u8& dest);
    int ld_r_hl(Bus& bus, u8& dest);
    int ld_hl_r(Bus& bus, u8 src);
    int ld_hl_n(Bus& bus);
    int ld_a_bc(Bus& bus);
    int ld_a_de(Bus& bus);
    int ld_bc_a(Bus& bus);
    int ld_de_a(Bus& bus);
    int ld_a_nn(Bus& bus);
    int ld_nn_a(Bus& bus);
    int ldh_a_c(Bus& bus);
    int ldh_c_a(Bus& bus);
    int ldh_a_n(Bus& bus);
    int ldh_n_a(Bus& bus);
    int ld_a_hl_dec(Bus& bus);
    int ld_hl_dec_a(Bus& bus);
    int ld_a_hl_inc(Bus& bus);
    int ld_hl_inc_a(Bus& bus);

    //16 bit load instructions
    int ld_rr_nn(Bus& bus, JRegisters dest);
    int ld_rr_nn(Bus& bus,u16& dest);
    int ld_nn_sp(Bus& bus);
    int ld_sp_hl(Bus& bus);
    int push_rr(Bus& bus, JRegisters src);
    int pop_rr(Bus& bus, JRegisters dest);
    int ld_hl_sp_offset(Bus& bus);

    //8 bit arithmetic and logic instructions
    int add_r(u8 src);
    int add_hl(Bus& bus);
    int add_n(Bus& bus);
    int adc_r(u8 src);
    int adc_hl(Bus& bus);
    int adc_n(Bus& bus);
    int sub_r(u8 src);
    int sub_hl(Bus& bus);
    int sub_n(Bus& bus);
    int sbc_r(u8 src);
    int sbc_hl(Bus& bus);
    int sbc_n(Bus& bus);
    int cp_r(u8 src);
    int cp_hl(Bus& bus);
    int cp_n(Bus& bus);
    int inc_r(u8& src);
    int inc_hl(Bus& bus);
    int dec_r(u8& src);
    int dec_hl(Bus& bus);
    int and_r(u8 src);
    int and_hl(Bus& bus);
    int and_n(Bus& bus);
    int or_r(u8 src);
    int or_hl(Bus& bus);
    int or_n(Bus& bus);
    int xor_r(u8 src);
    int xor_hl(Bus& bus);
    int xor_n(Bus& bus);
    int ccf();
    int scf();
    int daa();
    int cpl();

    //16 bit arithmetic
    int inc_rr(Bus& bus, JRegisters src);
    int dec_rr(Bus& bus, JRegisters src);
    int add_hl_rr(Bus& bus, JRegisters src);
    int add_hl_rr(Bus& bus,u16 src);
    int add_sp_e(Bus& bus);

    //rotate shift and bit op instructions
    int rlca();
    int rrca();
    int rla();
    int rra();
    int rlc_r(u8& src);
    int rlc_hl(Bus& bus);
    int rrc_r(u8& src);
    int rrc_hl(Bus& bus);
    int rl_r(u8& src);
    int rl_hl(Bus& bus);
    int rr_r(Bus& bus,u8& src);
    int rr_hl(Bus& bus);
    int sla_r(u8& src);
    int sla_hl(Bus& bus);
    int sra_r(u8& src);
    int sra_hl(Bus& bus);
    int swap_r(u8& src);
    int swap_hl(Bus& bus);
    int srl_r(u8& src);
    int srl_hl(Bus& bus);
    int bit_b_r(int bit, u8 src);
    int bit_b_hl(Bus& bus, int bit);
    int res_b_r(int bit, u8& src);
    int res_b_hl(Bus& bus, int bit);
    int set_b_r(int bit, u8& src);
    int set_b_hl(Bus& bus, int bit);

    //control flow instructions
    int jp_nn(Bus& bus);
    int jp_hl(Bus& bus);
    int jp_cc(Bus& bus, bool condition);
    int jr_e(Bus& bus);
    int jr_cc(Bus& bus, bool condition);
    int call_nn(Bus& bus);
    int call_cc(Bus& bus, bool condition);
    int ret(Bus& bus);
    int ret_cc(Bus& bus, bool condition);
    int reti(Bus& bus);
    int rst_n(Bus& bus, u8 vector);

    //misc instructions
    int halt(Bus& bus);
    int stop(Bus& bus);
    int ei(Bus& bus);
    int di(Bus& bus);
};