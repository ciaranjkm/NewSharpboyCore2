#include <cpu.h>

//execute instruction
int CPU::run(Bus& bus){
int cycles_taken = 0;

    //check for interrupt
    //is halted
    //get opcode
    //execute opcode

    return cycles_taken;
}

//8 bit load instructions
int CPU::ld_r_r(u8& dest, u8 src){
    dest = src;
    return 4;
}
int CPU::ld_r_n(Bus& bus, u8& dest){
    u8 value = bus.read(m_registers.pc++);
    dest = value;
    return 8;
}
int CPU::ld_r_hl(Bus& bus, u8& dest){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    dest = value;
    return 8;
}
int CPU::ld_hl_r(Bus& bus, u8 src){
    u16 hl = m_registers.get_jregister(HL);
    bus.write(hl, src);
    return 8;
}
int CPU::ld_hl_n(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(m_registers.pc++);
    bus.write(hl, value);
    return 12;
}
int CPU::ld_a_bc(Bus& bus){
    u16 bc = m_registers.get_jregister(BC);
    u8 value = bus.read(bc);
    m_registers.a = value;
    return 8;
}
int CPU::ld_a_de(Bus& bus){
    u16 de = m_registers.get_jregister(BC);
    u8 value = bus.read(de);
    m_registers.a = value;
    return 8;
}
int CPU::ld_bc_a(Bus& bus){
    u16 bc = m_registers.get_jregister(BC);
    bus.write(bc, m_registers.a);
    return 8;
}
int CPU::ld_de_a(Bus& bus){
    u16 de = m_registers.get_jregister(BC);
    bus.write(de, m_registers.a);
    return 8;
}
int CPU::ld_a_nn(Bus& bus){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 value = (high << 8) | low;
    m_registers.a = bus.read(value);
    return 16;
}
int CPU::ld_nn_a(Bus& bus){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 address = (high << 8) | low;
    bus.write(address, m_registers.a);
    return 16;
}
int CPU::ldh_a_c(Bus& bus){
    u16 address = 0xff00 | m_registers.c;
    m_registers.a = bus.read(address);
    return 8;
}
int CPU::ldh_c_a(Bus& bus){
    u16 address = 0xff00 | m_registers.c;
    bus.write(address, m_registers.a);
    return 8;
}
int CPU::ldh_a_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u16 address = 0xff00 | value;
    m_registers.a = bus.read(address);
    return 12;
}
int CPU::ldh_n_a(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u16 address = 0xff00 | value;
    bus.write(address, m_registers.a);
    return 12;
}
int CPU::ld_a_hl_dec(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl--);
    m_registers.a = value;
    m_registers.set_jregister(HL, hl);
    return 8;
}
int CPU::ld_hl_dec_a(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    bus.write(hl--, m_registers.a);
    m_registers.set_jregister(HL, hl);
    return 8;
}
int CPU::ld_a_hl_inc(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl++);
    m_registers.a = value;
    m_registers.set_jregister(HL, hl);
    return 8;
}
int CPU::ld_hl_inc_a(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    bus.write(hl++, m_registers.a);
    m_registers.set_jregister(HL, hl);
    return 8;
}

//16 bit load instructions
int CPU::ld_rr_nn(Bus& bus, JRegisters dest){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 value = (high << 8) | low;
    m_registers.set_jregister(dest, value);
    return 12;
}
int CPU::ld_nn_sp(Bus& bus){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 address = (high << 8) | low;
    bus.write(address++, (m_registers.sp & 0xff));
    bus.write(address, (m_registers.sp >> 8));
    return 20;
}
int CPU::ld_sp_hl(Bus& bus){
    bus.idle();
    m_registers.sp = m_registers.get_jregister(HL);
    return 8;
}
int CPU::push_rr(Bus& bus, JRegisters src){
    u16 value = m_registers.get_jregister(src);
    bus.idle();
    m_registers.sp--;
    bus.write(m_registers.sp--, (value >> 8));
    bus.write(m_registers.sp, (value & 0xff));
    return 16;
}
int CPU::pop_rr(Bus& bus, JRegisters dest){
    u8 low = bus.read(m_registers.sp++);
    u8 high = bus.read(m_registers.sp++);
    u16 value = (high << 8) | low;
    m_registers.set_jregister(dest, value);
    return 12;
}
int CPU::ld_hl_sp_offset(Bus& bus){
    u8 offset = bus.read(m_registers.pc++);
    u8 offset_sign = (offset >> 7) & 0x01;
    u8 result = (m_registers.sp & 0xff) + offset;
    bus.idle();
    m_registers.l = result;
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.sp & 0x0f) + (offset & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, (m_registers.sp & 0xff) + offset > 0xff);
    bus.idle();
    u8 adjust = (offset_sign != 0x00) ? 0xff : 0x00;
    result = (m_registers.sp >> 8) + adjust + (m_flags.get_flag(C) ? 0x01 : 0x00);
    m_registers.h = result;
    return 12;
}

//8 bit arithmetic and logic instructions
int CPU::add_r(u8 value){
    u8 result = m_registers.a + value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value > 0xff);

    m_registers.a = result;
    return 4;
}
int CPU::add_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a + value;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value > 0xff);

    m_registers.a = result;
    return 8;
}
int CPU::add_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a + value;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value > 0xff);

    m_registers.a = result;
    return 8;
}
int CPU::adc_r(u8 value){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 result = m_registers.a + value + c;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) + c > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value + c > 0xff);

    m_registers.a = result;
    return 4;
}
int CPU::adc_hl(Bus& bus){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a + value + c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value > 0xff);

    m_registers.a = result;
    return 8;
}
int CPU::adc_n(Bus& bus){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a + value + c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (m_registers.a & 0x0f) + (value & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, m_registers.a + value > 0xff);

    m_registers.a = result;
    return 8;
}
int CPU::sub_r(u8 value){
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    m_registers.a = result;
    return 4;
}
int CPU::sub_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    m_registers.a = result;
    return 8;
}
int CPU::sub_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    m_registers.a = result;
    return 8;
}
int CPU::sbc_r(u8 value){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 result = m_registers.a - value - c;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, (value & 0x0f) + c > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value + c > m_registers.a);
    m_registers.a = result;
    return 4;
}
int CPU::sbc_hl(Bus& bus){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a - value - c;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, (value & 0x0f) + c > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value + c > m_registers.a);
    m_registers.a = result;
    return 8;
}
int CPU::sbc_n(Bus& bus){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a - value - c;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, (value & 0x0f) + c > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value + c > m_registers.a);
    m_registers.a = result;
    return 8;
}
int CPU::cp_r(u8 value){
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    return 4;
}
int CPU::cp_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    return 8;
}
int CPU::cp_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a - value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, value & 0x0f > m_registers.a & 0x0f);
    m_flags.set_flag(m_registers.f, C, value > m_registers.a);
    return 8;
}
int CPU::inc_r(u8& value){
    u8 result = value + 0x01;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (value & 0x0f) + 0x01 > 0x0f);
    value = result;
    return 4;
}
int CPU::inc_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = value + 0x01;
    bus.write(hl, result);
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (value & 0x0f) + 0x01 > 0x0f);
    return 12;
}
int CPU::dec_r(u8& value){
    u8 result = value - 0x01;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, 0x01 > value & 0x0f);
    value = result;
    return 4;
}
int CPU::dec_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = value - 0x01;
    bus.write(hl, result);
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, 0x01 > value & 0x0f);
    return 12;
}
int CPU::and_r(u8 value){
    u8 result = m_registers.a & value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, true);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 4;
}
int CPU::and_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a & value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, true);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::and_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a & value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, true);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::or_r(u8 value){
    u8 result = m_registers.a | value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 4;
}
int CPU::or_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a | value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::or_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a | value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::xor_r(u8 value){
    u8 result = m_registers.a ^ value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 4;   
}
int CPU::xor_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = m_registers.a ^ value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::xor_n(Bus& bus){
    u8 value = bus.read(m_registers.pc++);
    u8 result = m_registers.a ^ value;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, Z, false);
    m_registers.a = result;
    return 8;
}
int CPU::ccf(){
    bool c = m_flags.get_flag(C);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, !c);
    return 4;
}
int CPU::scf(){
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, true);
    return 4;
}
int CPU::daa(){
    u8 a = m_registers.a;
	u8 adjustment = 0x00;

	bool set_carry = false;

	bool sub_flag = m_flags.get_flag(N);
	bool halfcarry_flag = m_flags.get_flag(H);
	bool carry_flag = m_flags.get_flag(C);

	if (!sub_flag) {
		if (halfcarry_flag || (m_registers.a & 0x0f) > 0x09) {
			adjustment |= 0x06;
		}
		if (carry_flag || (m_registers.a > 0x99)) {
			adjustment += 0x60;
			set_carry = true;
		}

		a += adjustment;
	}
	else {
		if (halfcarry_flag) {
			adjustment |= 0x06;
		}
		if (carry_flag) {
			adjustment |= 0x60;
		}

		a -= adjustment;
	}

	m_registers.a = a;

	m_flags.set_flag(m_registers.f, Z, m_registers.a == 0);
	m_flags.set_flag(m_registers.f, H, false);
	m_flags.set_flag(m_registers.f, C, set_carry || carry_flag);
	return 4;
}
int CPU::cpl(){
    m_registers.a = ~(m_registers.a);
    m_flags.set_flag(m_registers.f, N, true);
    m_flags.set_flag(m_registers.f, H, true);
    return 4;
}

//16 bit arithmetic
int CPU::inc_rr(Bus& bus, JRegisters src){
    bus.idle();
    u16 rr = m_registers.get_jregister(src);
    rr++;
    m_registers.set_jregister(src, rr);
    return 8;
}
int CPU::dec_rr(Bus& bus, JRegisters src){
    bus.idle();
    u16 rr = m_registers.get_jregister(src);
    rr--;
    m_registers.set_jregister(src, rr);
    return 8;
}
int CPU::add_hl_rr(Bus& bus, JRegisters src){
    bus.idle();
    u16 hl = m_registers.get_jregister(HL);
    u16 rr = m_registers.get_jregister(src);
    u16 result = hl + rr;

    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (hl & 0x0fff) + (rr & 0x0fff) > 0x0fff);
    m_flags.set_flag(m_registers.f, C, hl + rr > 0xffff);
    
    m_registers.set_jregister(HL, result);
}
int CPU::add_hl_rr(Bus& bus, u16 src){
    bus.idle();
    u16 hl = m_registers.get_jregister(HL);
    u16 result = hl + src;

    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, (hl & 0x0fff) + (src & 0x0fff) > 0x0fff);
    m_flags.set_flag(m_registers.f, C, hl + src > 0xffff);
    
    m_registers.set_jregister(HL, result);
}
int CPU::add_sp_e(Bus& bus){
    s8 e = bus.read(m_registers.pc++);
    bus.idle();
    bool sign = (e >> 7) != 0x00;
    u16 result = m_registers.sp + e;
    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, ((m_registers.sp & 0xff) & 0x0f) + (e & 0x0f) > 0x0f);
    m_flags.set_flag(m_registers.f, C, (m_registers.sp & 0xff) + e > 0xff);
    bus.idle();
    m_registers.sp = result;
    return 16;
}

//rotate shift and bit op instructions
int CPU::rlca(){
    u8 b7 = (m_registers.a >> 7) & 0x01;
    u8 result = (m_registers.a << 1) | b7;

    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    m_registers.a = result;
    return 4;
}
int CPU::rrca(){
    u8 b0 = m_registers.a & 0x01;
    u8 result = m_registers.a >> 1 | b0 << 7;

    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    m_registers.a = result;
    return 4;
}
int CPU::rla(){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 b7 = (m_registers.a >> 7) & 0x01;
    u8 result = m_registers.a << 1 | c;

    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    m_registers.a = result;
    return 4;
}
int CPU::rra(){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 b0 = m_registers.a & 0x01;
    u8 result = m_registers.a >> 1 | c << 7;

    m_flags.set_flag(m_registers.f, Z, false);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    m_registers.a = result;
    return 4;
}
int CPU::rlc_r(u8& src){
    u8 b7 = (src >> 7) & 0x01;
    u8 result = (src << 1) | b7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    src = result;
    return 8;
}
int CPU::rlc_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 b7 = (value >> 7) & 0x01;
    u8 result = (value << 1) | b7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::rrc_r(u8& src){
    u8 b0 = src & 0x01;
    u8 result = src >> 1 | b0 << 7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    src = result;
    return 8;
}
int CPU::rrc_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 b0 = value & 0x01;
    u8 result = value >> 1 | b0 << 7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::rl_r(u8& src){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00; 
    u8 b7 = (src >> 7) & 0x01;
    u8 result = (src << 1) | c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    src = result;
    return 8;
}
int CPU::rl_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00; 
    u8 b7 = (value >> 7) & 0x01;
    u8 result = (value << 1) | c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::rr_r(Bus& bus,u8& src){
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 b0 = src & 0x01;
    u8 result = src >> 1 | c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    src = result;
    return 8;
}
int CPU::rr_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 c = m_flags.get_flag(C) ? 0x01 : 0x00;
    u8 b0 = value & 0x01;
    u8 result = value >> 1 | c;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::sla_r(u8& src){
    u8 b7 = (src >> 7) & 0x01;
    u8 result = (src << 1) | 0x00;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    src = result;
    return 8;
}
int CPU::sla_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 b7 = (value >> 7) & 0x01;
    u8 result = (value << 1) | 0x00;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b7 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::sra_r(u8& src){
    u8 b7 = (src >> 7) | 0x01;
    u8 b0 = src & 0x01;
    u8 result = (src >> 1) | b7 << 7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    src = result;
    return 8;
}
int CPU::sra_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 b7 = (value >> 7) | 0x01;
    u8 b0 = value & 0x01;
    u8 result = (value >> 1) | b7 << 7;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::swap_r(u8& src){
    u8 result = (src >> 4) | (src << 4);

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, false);

    src = result;
    return 8;
}
int CPU::swap_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = (value >> 4) | (value << 4);

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, false);

    bus.write(hl, result);
    return 16;
}
int CPU::srl_r(u8& src){
    u8 b0 = src & 0x01;
    u8 result = (src >> 1) | 0x00;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    src = result;
    return 8;
}
int CPU::srl_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 b0 = value & 0x01;
    u8 result = (value >> 1) | 0x00;

    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, false);
    m_flags.set_flag(m_registers.f, C, b0 != 0x00);

    bus.write(hl, result);
    return 16;
}
int CPU::bit_b_r(int bit, u8 src){
    u8 result = (src >> bit) & 0x01;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, true);
    return 8;
}
int CPU::bit_b_hl(Bus& bus, int bit){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl);
    u8 result = (value >> bit) & 0x01;
    m_flags.set_flag(m_registers.f, Z, result == 0x00);
    m_flags.set_flag(m_registers.f, N, false);
    m_flags.set_flag(m_registers.f, H, true);
    return 16;
}
int CPU::res_b_r(int bit, u8& src){
    u8 result = ~(0x01 << bit) & src;
    return 8;
}
int CPU::res_b_hl(Bus& bus, int bit){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl); 
    u8 result = ~(0x01 << bit) & value;
    bus.write(hl, result);
    return 16;
}
int CPU::set_b_r(int bit, u8& src){
    u8 result = (0x01 << bit) | src;
    src = result;
    return 8;
}
int CPU::set_b_hl(Bus& bus, int bit){
    u16 hl = m_registers.get_jregister(HL);
    u8 value = bus.read(hl); 
    u8 result = (0x01 << bit) | value;
    bus.write(hl, result);
    return 16;
}

//control flow instructions
int CPU::jp_nn(Bus& bus){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 jump = (high << 8) | low;
    bus.idle();
    m_registers.pc = jump;
    return 16;
}
int CPU::jp_hl(Bus& bus){
    u16 hl = m_registers.get_jregister(HL);
    m_registers.pc = hl;
    return 4;
}
int CPU::jp_cc(Bus& bus, bool condition){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 jump = (high << 8) | low;

    if(condition){
        bus.idle();
        m_registers.pc = jump;
        return 16;
    }
    else{
        return 12;
    }
}
int CPU::jr_e(Bus& bus){
    s8 e = bus.read(m_registers.pc++);
    bus.idle();
    u16 result = m_registers.pc + e;
    m_registers.pc = result;
    return 12;
}
int CPU::jr_cc(Bus& bus, bool condition){
    s8 e = bus.read(m_registers.pc++);
    if(condition){
        bus.idle();
        u16 result = m_registers.pc + e;
        m_registers.pc = result;
        return 12;
    }
    else{
        return 8;
    }
}
int CPU::call_nn(Bus& bus){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 nn = (high << 8) | low;
    bus.idle();
    bus.write(--m_registers.sp, (m_registers.pc >> 8));
    bus.write(--m_registers.sp, (m_registers.pc & 0xff));
    m_registers.pc = nn;
    return 24;
}
int CPU::call_cc(Bus& bus, bool condition){
    u8 low = bus.read(m_registers.pc++);
    u8 high = bus.read(m_registers.pc++);
    u16 nn = (high << 8) | low;
    if(condition){
        bus.idle();
        bus.write(--m_registers.sp, (m_registers.pc >> 8));
        bus.write(--m_registers.sp, (m_registers.pc & 0xff));
        m_registers.pc = nn;
        return 24;
    }
    else{
        return 12;
    }
}
int CPU::ret(Bus& bus){
    u8 low = bus.read(m_registers.sp++);
    u8 high = bus.read(m_registers.sp++);
    u16 ret = (high << 8) | low;
    bus.idle();
    m_registers.pc = ret;
    return 16;
}
int CPU::ret_cc(Bus& bus, bool condition){
    bus.idle();
    if(condition){
        u8 low = bus.read(m_registers.sp++);
        u8 high = bus.read(m_registers.sp++);
        u16 ret = (high << 8) | low;
        bus.idle();
        m_registers.pc = ret;
        return 20; 
    }
    else{
        return 8;
    }
}
int CPU::reti(Bus& bus){
    u8 low = bus.read(m_registers.sp++);
    u8 high = bus.read(m_registers.sp++);
    u16 ret = (high << 8) | low;
    bus.idle();
    m_registers.pc = ret;
    //todo enable ime
    return 16;
}
int CPU::rst_n(Bus& bus, u8 vector){
    u16 jump = 0x0000 | vector;
    bus.idle();
    bus.write(--m_registers.sp, (m_registers.pc >> 8));
    bus.write(--m_registers.sp, (m_registers.pc & 0xff));
    m_registers.pc = jump;
    return 16;
}

//misc instructions
int CPU::halt(Bus& bus){
    return 0;
}
int CPU::stop(Bus& bus){
    return 0;
}
int CPU::ei(Bus& bus){
    return 0;
}
int CPU::di(Bus& bus){
    return 0;
}