#include <cpu.h>

//execute instruction
int CPU::run(Bus& bus){
    int cycles_taken = 0;

    m_opcode = fetch_opcode(bus);
    cycles_taken += !m_prefixed ? execute_opcode(bus) : execute_prefix(bus);

    return cycles_taken;
}

//execution
u8 CPU::fetch_opcode(Bus& bus){
    m_prefixed = false;
    u8 opcode = bus.read(m_registers.pc++);

    if(m_opcode == 0xcb){
        m_prefixed = true;
        opcode = bus.read(m_registers.pc++);
    }

    return opcode;
}

int CPU::execute_opcode(Bus& bus){
    int cycles_consumed = 0;

    switch (m_opcode){
    case GBInstructions::NOOP: cycles_consumed += 4; return;
    case GBInstructions::LD_BC_NN: cycles_consumed += ld_rr_nn(bus, BC); break;
    case GBInstructions::LD_BC_A: cycles_consumed += ld_bc_a(bus); break;
    case GBInstructions::INC_BC: cycles_consumed += inc_rr(bus, BC); break;
    case GBInstructions::INC_B: cycles_consumed += inc_r(m_registers.b); break;
    case GBInstructions::DEC_B: cycles_consumed += dec_r(m_registers.b); break;
    case GBInstructions::LD_B_N: cycles_consumed += ld_r_n(bus, m_registers.b); break;
    case GBInstructions::RLCA: cycles_consumed += rlca(); break;
    case GBInstructions::LD_NN_SP: cycles_consumed += ld_nn_sp(bus); break;
    case GBInstructions::ADD_HL_BC: cycles_consumed += add_hl_rr(bus, BC); break;
    case GBInstructions::LD_A_BC: cycles_consumed += ld_a_bc(bus); break;
    case GBInstructions::DEC_BC: cycles_consumed += dec_rr(bus, BC); break;
    case GBInstructions::INC_C: cycles_consumed += inc_r(m_registers.c); break;
    case GBInstructions::DEC_C: cycles_consumed += dec_r(m_registers.c); break;
    case GBInstructions::LD_C_N: cycles_consumed += ld_r_n(bus, m_registers.c); break;
    case GBInstructions::RRCA: cycles_consumed += rrca(); break;

    case GBInstructions::STOP_N:
    case GBInstructions::LD_DE_NN:
    case GBInstructions::LD_DE_A:
    case GBInstructions::INC_DE:
    case GBInstructions::INC_D:
    case GBInstructions::DEC_D:
    case GBInstructions::LD_D_N:
    case GBInstructions::RLA:
    case GBInstructions::JR_E:
    case GBInstructions::ADD_HL_DE:
    case GBInstructions::LD_A_DE:
    case GBInstructions::DEC_DE:
    case GBInstructions::INC_E:
    case GBInstructions::DEC_E:
    case GBInstructions::LD_E_N:
    case GBInstructions::RRA:
    
    case GBInstructions::JR_NZ_E:    
    case GBInstructions::LD_HL_NN:
    case GBInstructions::LDI_HL_A:
    case GBInstructions::INC_HL:
    case GBInstructions::INC_H:
    case GBInstructions::DEC_H:
    case GBInstructions::LD_H_N:
    case GBInstructions::DAA:
    case GBInstructions::JR_Z_E:
    case GBInstructions::ADD_HL_HL:
    case GBInstructions::LD_A_HLI:
    case GBInstructions::DEC_HL:
    case GBInstructions::INC_L:
    case GBInstructions::DEC_L:
    case GBInstructions::LD_L_N:
    case GBInstructions::CPL:
        
    case GBInstructions::JR_NC_E:
    case GBInstructions::LD_SP_NN:
    case GBInstructions::LDD_HL_A:
    case GBInstructions::INC_SP:
    case GBInstructions::INC_memHL:
    case GBInstructions::DEC_memHL:
    case GBInstructions::LD_HL_N:
    case GBInstructions::SCF:
    case GBInstructions::JR_C_E:
    case GBInstructions::ADD_HL_SP:
    case GBInstructions::LD_A_HLD:
    case GBInstructions::DEC_SP:
    case GBInstructions::INC_A:
    case GBInstructions::DEC_A:
    case GBInstructions::LD_A_N:
    case GBInstructions::CCF:

    case GBInstructions::LD_B_B:
    case GBInstructions::LD_B_C:
    case GBInstructions::LD_B_D:
    case GBInstructions::LD_B_E:
    case GBInstructions::LD_B_H:
    case GBInstructions::LD_B_L:
    case GBInstructions::LD_B_HL:
    case GBInstructions::LD_B_A:
    case GBInstructions::LD_C_B:
    case GBInstructions::LD_C_C:
    case GBInstructions::LD_C_D:
    case GBInstructions::LD_C_E:
    case GBInstructions::LD_C_H:
    case GBInstructions::LD_C_L:
    case GBInstructions::LD_C_HL:
    case GBInstructions::LD_C_A:

    case GBInstructions::LD_D_B:
    case GBInstructions::LD_D_C:
    case GBInstructions::LD_D_D:
    case GBInstructions::LD_D_E:
    case GBInstructions::LD_D_H:
    case GBInstructions::LD_D_L:
    case GBInstructions::LD_D_HL:
    case GBInstructions::LD_D_A:
    case GBInstructions::LD_E_B:
    case GBInstructions::LD_E_C:
    case GBInstructions::LD_E_D:
    case GBInstructions::LD_E_E:
    case GBInstructions::LD_E_H:
    case GBInstructions::LD_E_L:
    case GBInstructions::LD_E_HL:
    case GBInstructions::LD_E_A:

    case GBInstructions::LD_H_B:
    case GBInstructions::LD_H_C:
    case GBInstructions::LD_H_D:
    case GBInstructions::LD_H_E:
    case GBInstructions::LD_H_H:
    case GBInstructions::LD_H_L:
    case GBInstructions::LD_H_HL:
    case GBInstructions::LD_H_A:
    case GBInstructions::LD_L_B:
    case GBInstructions::LD_L_C:
    case GBInstructions::LD_L_D:
    case GBInstructions::LD_L_E:
    case GBInstructions::LD_L_H:
    case GBInstructions::LD_L_L:
    case GBInstructions::LD_L_HL:
    case GBInstructions::LD_L_A:
    
    case GBInstructions::LD_HL_B:    
    case GBInstructions::LD_HL_C:
    case GBInstructions::LD_HL_D:
    case GBInstructions::LD_HL_E:
    case GBInstructions::LD_HL_H:
    case GBInstructions::LD_HL_L:
    case GBInstructions::HALT:
    case GBInstructions::LD_HL_A:
    case GBInstructions::LD_A_B:
    case GBInstructions::LD_A_C:
    case GBInstructions::LD_A_D:
    case GBInstructions::LD_A_E:
    case GBInstructions::LD_A_H:
    case GBInstructions::LD_A_L:
    case GBInstructions::LD_A_HL:
    case GBInstructions::LD_A_A:

    case GBInstructions::ADD_A_B:
    case GBInstructions::ADD_A_C:
    case GBInstructions::ADD_A_D:
    case GBInstructions::ADD_A_E:
    case GBInstructions::ADD_A_H:
    case GBInstructions::ADD_A_L:
    case GBInstructions::ADD_A_HL:
    case GBInstructions::ADD_A_A:
    case GBInstructions::ADC_A_B:
    case GBInstructions::ADC_A_C:
    case GBInstructions::ADC_A_D:
    case GBInstructions::ADC_A_E:
    case GBInstructions::ADC_A_H:
    case GBInstructions::ADC_A_L:
    case GBInstructions::ADC_A_HL:
    case GBInstructions::ADC_A_A:

    case GBInstructions::SUB_A_B:
    case GBInstructions::SUB_A_C:
    case GBInstructions::SUB_A_D:
    case GBInstructions::SUB_A_E:
    case GBInstructions::SUB_A_H:
    case GBInstructions::SUB_A_L:
    case GBInstructions::SUB_A_HL:
    case GBInstructions::SUB_A_A:
    case GBInstructions::SBC_A_B:
    case GBInstructions::SBC_A_C:
    case GBInstructions::SBC_A_D:    
    case GBInstructions::SBC_A_E:    
    case GBInstructions::SBC_A_H:
    case GBInstructions::SBC_A_L:
    case GBInstructions::SBC_A_HL:
    case GBInstructions::SBC_A_A:

    case GBInstructions::AND_A_B:
    case GBInstructions::AND_A_C:
    case GBInstructions::AND_A_D:
    case GBInstructions::AND_A_E:
    case GBInstructions::AND_A_H:
    case GBInstructions::AND_A_L:
    case GBInstructions::AND_A_HL:
    case GBInstructions::AND_A_A:
    case GBInstructions::XOR_A_B:
    case GBInstructions::XOR_A_C:
    case GBInstructions::XOR_A_D:
    case GBInstructions::XOR_A_E:
    case GBInstructions::XOR_A_H:
    case GBInstructions::XOR_A_L:
    case GBInstructions::XOR_A_HL:
    case GBInstructions::XOR_A_A:

    case GBInstructions::OR_A_B:
    case GBInstructions::OR_A_C:
    case GBInstructions::OR_A_D:
    case GBInstructions::OR_A_E:
    case GBInstructions::OR_A_H:
    case GBInstructions::OR_A_L:
    case GBInstructions::OR_A_HL:
    case GBInstructions::OR_A_A:
    case GBInstructions::CP_A_B:
    case GBInstructions::CP_A_C:
    case GBInstructions::CP_A_D:
    case GBInstructions::CP_A_E:
    case GBInstructions::CP_A_H:
    case GBInstructions::CP_A_L:
    case GBInstructions::CP_A_HL:
    case GBInstructions::CP_A_A:

    case GBInstructions::RET_NZ:
    case GBInstructions::POP_BC:
    case GBInstructions::JP_NZ_NN:
    case GBInstructions::JP_NN:
    case GBInstructions::CALL_NZ_NN:
    case GBInstructions::PUSH_BC:
    case GBInstructions::ADD_A_N:
    case GBInstructions::RST_00:
    case GBInstructions::RET_Z:
    case GBInstructions::RET:
    case GBInstructions::JP_Z_NN:        
    case GBInstructions::CB:
    case GBInstructions::CALL_Z_NN:
    case GBInstructions::CALL_NN:
    case GBInstructions::ADC_A_N:
    case GBInstructions::RST_08:
        

    case GBInstructions::RET_NC:
    case GBInstructions::POP_DE:
    case GBInstructions::JP_NC_NN:
    case GBInstructions::CALL_NC_NN:
    case GBInstructions::PUSH_DE:
    case GBInstructions::SUB_A_N:
    case GBInstructions::RST_10:
    case GBInstructions::RET_C:
    case GBInstructions::RETI:
    case GBInstructions::JP_C_NN:
    case GBInstructions::CALL_C_NN:
    case GBInstructions::SBC_A_N:
    case GBInstructions::RST_18:

    case GBInstructions::LDH_N_A:
    case GBInstructions::POP_HL:
    case GBInstructions::LDH_C_A:
    case GBInstructions::PUSH_HL:
    case GBInstructions::AND_A_N:
    case GBInstructions::RST_20:
    case GBInstructions::ADD_SP_E:
    case GBInstructions::JP_HL:
    case GBInstructions::LD_NN_A:
    case GBInstructions::XOR_A_N:
    case GBInstructions::RST_28:

    case GBInstructions::LDH_A_N:
    case GBInstructions::POP_AF:
    case GBInstructions::LDH_A_C:
    case GBInstructions::DI:
    case GBInstructions::PUSH_AF:
    case GBInstructions::OR_A_N:
    case GBInstructions::RST_30:
    case GBInstructions::LD_HL_SP_E:
    case GBInstructions::LD_SP_HL:
    case GBInstructions::LD_A_NN:
    case GBInstructions::EI:
    case GBInstructions::CP_A_N:
    case GBInstructions::RST_38:

    default:
        std::cerr << std::format("[ERROR @ CPU::run()] Invalid opcode, {:x2}\n", m_opcode);
        break;
    }

    return cycles_consumed;
}
int CPU::execute_prefix(Bus& bus){
    int cycles_consumed = 0;

    switch (m_opcode) {
    case GBPrefixedInstructions::CB_RLC_B:
        
    case GBPrefixedInstructions::CB_RLC_C:
        
    case GBPrefixedInstructions::CB_RLC_D:
        
    case GBPrefixedInstructions::CB_RLC_E:
        
    case GBPrefixedInstructions::CB_RLC_H:
        
    case GBPrefixedInstructions::CB_RLC_L:
        
    case GBPrefixedInstructions::CB_RLC_HL:
        
    case GBPrefixedInstructions::CB_RLC_A:
        

    case GBPrefixedInstructions::CB_RRC_B:
        
    case GBPrefixedInstructions::CB_RRC_C:
        
    case GBPrefixedInstructions::CB_RRC_D:
        
    case GBPrefixedInstructions::CB_RRC_E:
        
    case GBPrefixedInstructions::CB_RRC_H:
        
    case GBPrefixedInstructions::CB_RRC_L:
        
    case GBPrefixedInstructions::CB_RRC_HL:
        
    case GBPrefixedInstructions::CB_RRC_A:
        

    case GBPrefixedInstructions::CB_RL_B:
        
    case GBPrefixedInstructions::CB_RL_C:
        
    case GBPrefixedInstructions::CB_RL_D:
        
    case GBPrefixedInstructions::CB_RL_E:
        
    case GBPrefixedInstructions::CB_RL_H:
        
    case GBPrefixedInstructions::CB_RL_L:
        
    case GBPrefixedInstructions::CB_RL_HL:
        
    case GBPrefixedInstructions::CB_RL_A:
        

    case GBPrefixedInstructions::CB_RR_B:
        
    case GBPrefixedInstructions::CB_RR_C:
        
    case GBPrefixedInstructions::CB_RR_D:
        
    case GBPrefixedInstructions::CB_RR_E:
        
    case GBPrefixedInstructions::CB_RR_H:
        
    case GBPrefixedInstructions::CB_RR_L:
        
    case GBPrefixedInstructions::CB_RR_HL:
        
    case GBPrefixedInstructions::CB_RR_A:
        

    case GBPrefixedInstructions::CB_SLA_B:
        
    case GBPrefixedInstructions::CB_SLA_C:
        
    case GBPrefixedInstructions::CB_SLA_D:
        
    case GBPrefixedInstructions::CB_SLA_E:
        
    case GBPrefixedInstructions::CB_SLA_H:
        
    case GBPrefixedInstructions::CB_SLA_L:
        
    case GBPrefixedInstructions::CB_SLA_HL:
        
    case GBPrefixedInstructions::CB_SLA_A:
        

    case GBPrefixedInstructions::CB_SRA_B:
        
    case GBPrefixedInstructions::CB_SRA_C:
        
    case GBPrefixedInstructions::CB_SRA_D:
        
    case GBPrefixedInstructions::CB_SRA_E:
        
    case GBPrefixedInstructions::CB_SRA_H:
        
    case GBPrefixedInstructions::CB_SRA_L:
        
    case GBPrefixedInstructions::CB_SRA_HL:
        
    case GBPrefixedInstructions::CB_SRA_A:
        

    case GBPrefixedInstructions::CB_SWAP_B:
        
    case GBPrefixedInstructions::CB_SWAP_C:
        
    case GBPrefixedInstructions::CB_SWAP_D:
        
    case GBPrefixedInstructions::CB_SWAP_E:
        
    case GBPrefixedInstructions::CB_SWAP_H:
        
    case GBPrefixedInstructions::CB_SWAP_L:
        
    case GBPrefixedInstructions::CB_SWAP_HL:
        
    case GBPrefixedInstructions::CB_SWAP_A:
        

    case GBPrefixedInstructions::CB_SRL_B:
        
    case GBPrefixedInstructions::CB_SRL_C:
        
    case GBPrefixedInstructions::CB_SRL_D:
        
    case GBPrefixedInstructions::CB_SRL_E:
        
    case GBPrefixedInstructions::CB_SRL_H:
        
    case GBPrefixedInstructions::CB_SRL_L:
        
    case GBPrefixedInstructions::CB_SRL_HL:
        
    case GBPrefixedInstructions::CB_SRL_A:
        

    case GBPrefixedInstructions::CB_BIT0_B:
        
    case GBPrefixedInstructions::CB_BIT0_C:
        
    case GBPrefixedInstructions::CB_BIT0_D:
        
    case GBPrefixedInstructions::CB_BIT0_E:
        
    case GBPrefixedInstructions::CB_BIT0_H:
        
    case GBPrefixedInstructions::CB_BIT0_L:
        
    case GBPrefixedInstructions::CB_BIT0_HL:
        
    case GBPrefixedInstructions::CB_BIT0_A:
        

    case GBPrefixedInstructions::CB_BIT1_B:
        
    case GBPrefixedInstructions::CB_BIT1_C:
        
    case GBPrefixedInstructions::CB_BIT1_D:
        
    case GBPrefixedInstructions::CB_BIT1_E:
        
    case GBPrefixedInstructions::CB_BIT1_H:
        
    case GBPrefixedInstructions::CB_BIT1_L:
        
    case GBPrefixedInstructions::CB_BIT1_HL:
        
    case GBPrefixedInstructions::CB_BIT1_A:
        

    case GBPrefixedInstructions::CB_BIT2_B:
        
    case GBPrefixedInstructions::CB_BIT2_C:
        
    case GBPrefixedInstructions::CB_BIT2_D:
        
    case GBPrefixedInstructions::CB_BIT2_E:
        
    case GBPrefixedInstructions::CB_BIT2_H:
        
    case GBPrefixedInstructions::CB_BIT2_L:
        
    case GBPrefixedInstructions::CB_BIT2_HL:
        
    case GBPrefixedInstructions::CB_BIT2_A:
        

    case GBPrefixedInstructions::CB_BIT3_B:
        
    case GBPrefixedInstructions::CB_BIT3_C:
        
    case GBPrefixedInstructions::CB_BIT3_D:
        
    case GBPrefixedInstructions::CB_BIT3_E:
        
    case GBPrefixedInstructions::CB_BIT3_H:
        
    case GBPrefixedInstructions::CB_BIT3_L:
        
    case GBPrefixedInstructions::CB_BIT3_HL:
        
    case GBPrefixedInstructions::CB_BIT3_A:
        

    case GBPrefixedInstructions::CB_BIT4_B:
        
    case GBPrefixedInstructions::CB_BIT4_C:
        
    case GBPrefixedInstructions::CB_BIT4_D:
        
    case GBPrefixedInstructions::CB_BIT4_E:
        
    case GBPrefixedInstructions::CB_BIT4_H:
        
    case GBPrefixedInstructions::CB_BIT4_L:
        
    case GBPrefixedInstructions::CB_BIT4_HL:
        
    case GBPrefixedInstructions::CB_BIT4_A:
        

    case GBPrefixedInstructions::CB_BIT5_B:
        
    case GBPrefixedInstructions::CB_BIT5_C:
        
    case GBPrefixedInstructions::CB_BIT5_D:
        
    case GBPrefixedInstructions::CB_BIT5_E:
        
    case GBPrefixedInstructions::CB_BIT5_H:
        
    case GBPrefixedInstructions::CB_BIT5_L:
        
    case GBPrefixedInstructions::CB_BIT5_HL:
        
    case GBPrefixedInstructions::CB_BIT5_A:
        

    case GBPrefixedInstructions::CB_BIT6_B:
        
    case GBPrefixedInstructions::CB_BIT6_C:
        
    case GBPrefixedInstructions::CB_BIT6_D:
        
    case GBPrefixedInstructions::CB_BIT6_E:
        
    case GBPrefixedInstructions::CB_BIT6_H:
        
    case GBPrefixedInstructions::CB_BIT6_L:
        
    case GBPrefixedInstructions::CB_BIT6_HL:
        
    case GBPrefixedInstructions::CB_BIT6_A:
        

    case GBPrefixedInstructions::CB_BIT7_B:
        
    case GBPrefixedInstructions::CB_BIT7_C:
        
    case GBPrefixedInstructions::CB_BIT7_D:
        
    case GBPrefixedInstructions::CB_BIT7_E:
        
    case GBPrefixedInstructions::CB_BIT7_H:
        
    case GBPrefixedInstructions::CB_BIT7_L:
        
    case GBPrefixedInstructions::CB_BIT7_HL:
        
    case GBPrefixedInstructions::CB_BIT7_A:
        

    case GBPrefixedInstructions::CB_RES0_B:
        
    case GBPrefixedInstructions::CB_RES0_C:
        
    case GBPrefixedInstructions::CB_RES0_D:
        
    case GBPrefixedInstructions::CB_RES0_E:
        
    case GBPrefixedInstructions::CB_RES0_H:
        
    case GBPrefixedInstructions::CB_RES0_L:
        
    case GBPrefixedInstructions::CB_RES0_HL:
        
    case GBPrefixedInstructions::CB_RES0_A:
        

    case GBPrefixedInstructions::CB_RES1_B:
        
    case GBPrefixedInstructions::CB_RES1_C:
        
    case GBPrefixedInstructions::CB_RES1_D:
        
    case GBPrefixedInstructions::CB_RES1_E:
        
    case GBPrefixedInstructions::CB_RES1_H:
        
    case GBPrefixedInstructions::CB_RES1_L:
        
    case GBPrefixedInstructions::CB_RES1_HL:
        
    case GBPrefixedInstructions::CB_RES1_A:
        

    case GBPrefixedInstructions::CB_RES2_B:
        
    case GBPrefixedInstructions::CB_RES2_C:
        
    case GBPrefixedInstructions::CB_RES2_D:
        
    case GBPrefixedInstructions::CB_RES2_E:
        
    case GBPrefixedInstructions::CB_RES2_H:
        
    case GBPrefixedInstructions::CB_RES2_L:
        
    case GBPrefixedInstructions::CB_RES2_HL:
        
    case GBPrefixedInstructions::CB_RES2_A:
        

    case GBPrefixedInstructions::CB_RES3_B:
        
    case GBPrefixedInstructions::CB_RES3_C:
        
    case GBPrefixedInstructions::CB_RES3_D:
        
    case GBPrefixedInstructions::CB_RES3_E:
        
    case GBPrefixedInstructions::CB_RES3_H:
        
    case GBPrefixedInstructions::CB_RES3_L:
        
    case GBPrefixedInstructions::CB_RES3_HL:
        
    case GBPrefixedInstructions::CB_RES3_A:
        

    case GBPrefixedInstructions::CB_RES4_B:
        
    case GBPrefixedInstructions::CB_RES4_C:
        
    case GBPrefixedInstructions::CB_RES4_D:
        
    case GBPrefixedInstructions::CB_RES4_E:
        
    case GBPrefixedInstructions::CB_RES4_H:
        
    case GBPrefixedInstructions::CB_RES4_L:
        
    case GBPrefixedInstructions::CB_RES4_HL:
        
    case GBPrefixedInstructions::CB_RES4_A:
        

    case GBPrefixedInstructions::CB_RES5_B:
        
    case GBPrefixedInstructions::CB_RES5_C:
        
    case GBPrefixedInstructions::CB_RES5_D:
        
    case GBPrefixedInstructions::CB_RES5_E:
        
    case GBPrefixedInstructions::CB_RES5_H:
        
    case GBPrefixedInstructions::CB_RES5_L:
        
    case GBPrefixedInstructions::CB_RES5_HL:
        
    case GBPrefixedInstructions::CB_RES5_A:
        

    case GBPrefixedInstructions::CB_RES6_B:
        
    case GBPrefixedInstructions::CB_RES6_C:
        
    case GBPrefixedInstructions::CB_RES6_D:
        
    case GBPrefixedInstructions::CB_RES6_E:
        
    case GBPrefixedInstructions::CB_RES6_H:
        
    case GBPrefixedInstructions::CB_RES6_L:
        
    case GBPrefixedInstructions::CB_RES6_HL:
        
    case GBPrefixedInstructions::CB_RES6_A:
        

    case GBPrefixedInstructions::CB_RES7_B:
        
    case GBPrefixedInstructions::CB_RES7_C:
        
    case GBPrefixedInstructions::CB_RES7_D:
        
    case GBPrefixedInstructions::CB_RES7_E:
        
    case GBPrefixedInstructions::CB_RES7_H:
        
    case GBPrefixedInstructions::CB_RES7_L:
        
    case GBPrefixedInstructions::CB_RES7_HL:
        
    case GBPrefixedInstructions::CB_RES7_A:
        

    case GBPrefixedInstructions::CB_SET0_B:
        
    case GBPrefixedInstructions::CB_SET0_C:
        
    case GBPrefixedInstructions::CB_SET0_D:
        
    case GBPrefixedInstructions::CB_SET0_E:
        
    case GBPrefixedInstructions::CB_SET0_H:
        
    case GBPrefixedInstructions::CB_SET0_L:
        
    case GBPrefixedInstructions::CB_SET0_HL:
        
    case GBPrefixedInstructions::CB_SET0_A:
        

    case GBPrefixedInstructions::CB_SET1_B:
        
    case GBPrefixedInstructions::CB_SET1_C:
        
    case GBPrefixedInstructions::CB_SET1_D:
        
    case GBPrefixedInstructions::CB_SET1_E:
        
    case GBPrefixedInstructions::CB_SET1_H:
        
    case GBPrefixedInstructions::CB_SET1_L:
        
    case GBPrefixedInstructions::CB_SET1_HL:
        
    case GBPrefixedInstructions::CB_SET1_A:
        

    case GBPrefixedInstructions::CB_SET2_B:
        
    case GBPrefixedInstructions::CB_SET2_C:
        
    case GBPrefixedInstructions::CB_SET2_D:
        
    case GBPrefixedInstructions::CB_SET2_E:
        
    case GBPrefixedInstructions::CB_SET2_H:
        
    case GBPrefixedInstructions::CB_SET2_L:
        
    case GBPrefixedInstructions::CB_SET2_HL:
        
    case GBPrefixedInstructions::CB_SET2_A:
        

    case GBPrefixedInstructions::CB_SET3_B:
        
    case GBPrefixedInstructions::CB_SET3_C:
        
    case GBPrefixedInstructions::CB_SET3_D:
        
    case GBPrefixedInstructions::CB_SET3_E:
        
    case GBPrefixedInstructions::CB_SET3_H:
        
    case GBPrefixedInstructions::CB_SET3_L:
        
    case GBPrefixedInstructions::CB_SET3_HL:
        
    case GBPrefixedInstructions::CB_SET3_A:
        

    case GBPrefixedInstructions::CB_SET4_B:
        
    case GBPrefixedInstructions::CB_SET4_C:
        
    case GBPrefixedInstructions::CB_SET4_D:
        
    case GBPrefixedInstructions::CB_SET4_E:
        
    case GBPrefixedInstructions::CB_SET4_H:
        
    case GBPrefixedInstructions::CB_SET4_L:
        
    case GBPrefixedInstructions::CB_SET4_HL:
        
    case GBPrefixedInstructions::CB_SET4_A:
        

    case GBPrefixedInstructions::CB_SET5_B:
        
    case GBPrefixedInstructions::CB_SET5_C:
        
    case GBPrefixedInstructions::CB_SET5_D:
        
    case GBPrefixedInstructions::CB_SET5_E:
        
    case GBPrefixedInstructions::CB_SET5_H:
        
    case GBPrefixedInstructions::CB_SET5_L:
        
    case GBPrefixedInstructions::CB_SET5_HL:
        
    case GBPrefixedInstructions::CB_SET5_A:
        

    case GBPrefixedInstructions::CB_SET6_B:
        
    case GBPrefixedInstructions::CB_SET6_C:
        
    case GBPrefixedInstructions::CB_SET6_D:
        
    case GBPrefixedInstructions::CB_SET6_E:
        
    case GBPrefixedInstructions::CB_SET6_H:
        
    case GBPrefixedInstructions::CB_SET6_L:
        
    case GBPrefixedInstructions::CB_SET6_HL:
        
    case GBPrefixedInstructions::CB_SET6_A:
        

    case GBPrefixedInstructions::CB_SET7_B:
        
    case GBPrefixedInstructions::CB_SET7_C:
        
    case GBPrefixedInstructions::CB_SET7_D:
        
    case GBPrefixedInstructions::CB_SET7_E:
        
    case GBPrefixedInstructions::CB_SET7_H:
        
    case GBPrefixedInstructions::CB_SET7_L:
        
    case GBPrefixedInstructions::CB_SET7_HL:
        
    case GBPrefixedInstructions::CB_SET7_A:
        

    default:
        std::cerr << std::format("[ERROR @ CPU::run()] Invalid opcode, {:x2}\n", m_opcode);
        break;
    }

    return cycles_consumed;
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