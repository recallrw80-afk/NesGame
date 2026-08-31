#include "basic/types.h"
#include "nes/CPU.h"
#include "nes/Bus.h"

// 指令项((256 项目)
const CPU::Instruction CPU::table[256] = {
    // 0x00
    {&CPU::IMP, &CPU::BRK, "BRK", 7}, {&CPU::IZX, &CPU::ORA, "ORA", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 3}, {&CPU::ZP0, &CPU::ORA, "ORA", 3},
    {&CPU::ZP0, &CPU::ASL, "ASL", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::PHP, "PHP", 3}, {&CPU::IMM, &CPU::ORA, "ORA", 2},
    {&CPU::ACC, &CPU::ASL, "ASL", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABS, &CPU::ORA, "ORA", 4},
    {&CPU::ABS, &CPU::ASL, "ASL", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0x10
    {&CPU::REL, &CPU::BPL, "BPL", 2}, {&CPU::IZY, &CPU::ORA, "ORA", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::ORA, "ORA", 4},
    {&CPU::ZPX, &CPU::ASL, "ASL", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::CLC, "CLC", 2}, {&CPU::ABY, &CPU::ORA, "ORA", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::ORA, "ORA", 4},
    {&CPU::ABX, &CPU::ASL, "ASL", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    // 0x20
    {&CPU::ABS, &CPU::JSR, "JSR", 6}, {&CPU::IZX, &CPU::AND, "AND", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::ZP0, &CPU::BIT, "BIT", 3}, {&CPU::ZP0, &CPU::AND, "AND", 3},
    {&CPU::ZP0, &CPU::ROL, "ROL", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::PLP, "PLP", 4}, {&CPU::IMM, &CPU::AND, "AND", 2},
    {&CPU::ACC, &CPU::ROL, "ROL", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::BIT, "BIT", 4}, {&CPU::ABS, &CPU::AND, "AND", 4},
    {&CPU::ABS, &CPU::ROL, "ROL", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0x30
    {&CPU::REL, &CPU::BMI, "BMI", 2}, {&CPU::IZY, &CPU::AND, "AND", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::AND, "AND", 4},
    {&CPU::ZPX, &CPU::ROL, "ROL", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::SEC, "SEC", 2}, {&CPU::ABY, &CPU::AND, "AND", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::AND, "AND", 4},
    {&CPU::ABX, &CPU::ROL, "ROL", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    // 0x40
    {&CPU::IMP, &CPU::RTI, "RTI", 6}, {&CPU::IZX, &CPU::EOR, "EOR", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 3}, {&CPU::ZP0, &CPU::EOR, "EOR", 3},
    {&CPU::ZP0, &CPU::LSR, "LSR", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::PHA, "PHA", 3}, {&CPU::IMM, &CPU::EOR, "EOR", 2},
    {&CPU::ACC, &CPU::LSR, "LSR", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::JMP, "JMP", 3}, {&CPU::ABS, &CPU::EOR, "EOR", 4},
    {&CPU::ABS, &CPU::LSR, "LSR", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0x50
    {&CPU::REL, &CPU::BVC, "BVC", 2}, {&CPU::IZY, &CPU::EOR, "EOR", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::EOR, "EOR", 4},
    {&CPU::ZPX, &CPU::LSR, "LSR", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::CLI, "CLI", 2}, {&CPU::ABY, &CPU::EOR, "EOR", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::EOR, "EOR", 4},
    {&CPU::ABX, &CPU::LSR, "LSR", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    // 0x60
    {&CPU::IMP, &CPU::RTS, "RTS", 6}, {&CPU::IZX, &CPU::ADC, "ADC", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 3}, {&CPU::ZP0, &CPU::ADC, "ADC", 3},
    {&CPU::ZP0, &CPU::ROR, "ROR", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::PLA, "PLA", 4}, {&CPU::IMM, &CPU::ADC, "ADC", 2},
    {&CPU::ACC, &CPU::ROR, "ROR", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::IND, &CPU::JMP, "JMP", 5}, {&CPU::ABS, &CPU::ADC, "ADC", 4},
    {&CPU::ABS, &CPU::ROR, "ROR", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0x70
    {&CPU::REL, &CPU::BVS, "BVS", 2}, {&CPU::IZY, &CPU::ADC, "ADC", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::ADC, "ADC", 4},
    {&CPU::ZPX, &CPU::ROR, "ROR", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::SEI, "SEI", 2}, {&CPU::ABY, &CPU::ADC, "ADC", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::ADC, "ADC", 4},
    {&CPU::ABX, &CPU::ROR, "ROR", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    // 0x80
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::IZX, &CPU::STA, "STA", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::ZP0, &CPU::STY, "STY", 3}, {&CPU::ZP0, &CPU::STA, "STA", 3},
    {&CPU::ZP0, &CPU::STX, "STX", 3}, {&CPU::XXX, &CPU::XXX, "XXX", 3},
    {&CPU::IMP, &CPU::DEY, "DEY", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::IMP, &CPU::TXA, "TXA", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::STY, "STY", 4}, {&CPU::ABS, &CPU::STA, "STA", 4},
    {&CPU::ABS, &CPU::STX, "STX", 4}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    // 0x90
    {&CPU::REL, &CPU::BCC, "BCC", 2}, {&CPU::IZY, &CPU::STA, "STA", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::ZPX, &CPU::STY, "STY", 4}, {&CPU::ZPX, &CPU::STA, "STA", 4},
    {&CPU::ZPY, &CPU::STX, "STX", 4}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    {&CPU::IMP, &CPU::TYA, "TYA", 2}, {&CPU::ABY, &CPU::STA, "STA", 5},
    {&CPU::IMP, &CPU::TXS, "TXS", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 5}, {&CPU::ABX, &CPU::STA, "STA", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    // 0xA0
    {&CPU::IMM, &CPU::LDY, "LDY", 2}, {&CPU::IZX, &CPU::LDA, "LDA", 6},
    {&CPU::IMM, &CPU::LDX, "LDX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::ZP0, &CPU::LDY, "LDY", 3}, {&CPU::ZP0, &CPU::LDA, "LDA", 3},
    {&CPU::ZP0, &CPU::LDX, "LDX", 3}, {&CPU::XXX, &CPU::XXX, "XXX", 3},
    {&CPU::IMP, &CPU::TAY, "TAY", 2}, {&CPU::IMM, &CPU::LDA, "LDA", 2},
    {&CPU::IMP, &CPU::TAX, "TAX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::LDY, "LDY", 4}, {&CPU::ABS, &CPU::LDA, "LDA", 4},
    {&CPU::ABS, &CPU::LDX, "LDX", 4}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    // 0xB0
    {&CPU::REL, &CPU::BCS, "BCS", 2}, {&CPU::IZY, &CPU::LDA, "LDA", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::ZPX, &CPU::LDY, "LDY", 4}, {&CPU::ZPX, &CPU::LDA, "LDA", 4},
    {&CPU::ZPY, &CPU::LDX, "LDX", 4}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    {&CPU::IMP, &CPU::CLV, "CLV", 2}, {&CPU::ABY, &CPU::LDA, "LDA", 4},
    {&CPU::IMP, &CPU::TSX, "TSX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    {&CPU::ABX, &CPU::LDY, "LDY", 4}, {&CPU::ABX, &CPU::LDA, "LDA", 4},
    {&CPU::ABY, &CPU::LDX, "LDX", 4}, {&CPU::XXX, &CPU::XXX, "XXX", 4},
    // 0xC0
    {&CPU::IMM, &CPU::CPY, "CPY", 2}, {&CPU::IZX, &CPU::CMP, "CMP", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::ZP0, &CPU::CPY, "CPY", 3}, {&CPU::ZP0, &CPU::CMP, "CMP", 3},
    {&CPU::ZP0, &CPU::DEC, "DEC", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::INY, "INY", 2}, {&CPU::IMM, &CPU::CMP, "CMP", 2},
    {&CPU::IMP, &CPU::DEX, "DEX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::CPY, "CPY", 4}, {&CPU::ABS, &CPU::CMP, "CMP", 4},
    {&CPU::ABS, &CPU::DEC, "DEC", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0xD0
    {&CPU::REL, &CPU::BNE, "BNE", 2}, {&CPU::IZY, &CPU::CMP, "CMP", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::CMP, "CMP", 4},
    {&CPU::ZPX, &CPU::DEC, "DEC", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::CLD, "CLD", 2}, {&CPU::ABY, &CPU::CMP, "CMP", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::CMP, "CMP", 4},
    {&CPU::ABX, &CPU::DEC, "DEC", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    // 0xE0
    {&CPU::IMM, &CPU::CPX, "CPX", 2}, {&CPU::IZX, &CPU::SBC, "SBC", 6},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::ZP0, &CPU::CPX, "CPX", 3}, {&CPU::ZP0, &CPU::SBC, "SBC", 3},
    {&CPU::ZP0, &CPU::INC, "INC", 5}, {&CPU::XXX, &CPU::XXX, "XXX", 5},
    {&CPU::IMP, &CPU::INX, "INX", 2}, {&CPU::IMM, &CPU::SBC, "SBC", 2},
    {&CPU::IMP, &CPU::NOP, "NOP", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 2},
    {&CPU::ABS, &CPU::CPX, "CPX", 4}, {&CPU::ABS, &CPU::SBC, "SBC", 4},
    {&CPU::ABS, &CPU::INC, "INC", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    // 0xF0
    {&CPU::REL, &CPU::BEQ, "BEQ", 2}, {&CPU::IZY, &CPU::SBC, "SBC", 5},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 8},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ZPX, &CPU::SBC, "SBC", 4},
    {&CPU::ZPX, &CPU::INC, "INC", 6}, {&CPU::XXX, &CPU::XXX, "XXX", 6},
    {&CPU::IMP, &CPU::SED, "SED", 2}, {&CPU::ABY, &CPU::SBC, "SBC", 4},
    {&CPU::XXX, &CPU::XXX, "XXX", 2}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
    {&CPU::XXX, &CPU::XXX, "XXX", 4}, {&CPU::ABX, &CPU::SBC, "SBC", 4},
    {&CPU::ABX, &CPU::INC, "INC", 7}, {&CPU::XXX, &CPU::XXX, "XXX", 7},
};

// 构造函数
CPU::CPU()
    : a(0), x(0), y(0), pc(0x0000), sp(0xFD), opcode(0x00)
      , flag_c(false), flag_z(false), flag_i(false), flag_d(false)
      , flag_b(false), flag_v(false), flag_n(false)
      , bus(nullptr)
      , addr_abs(0x0000), addr_rel(0x0000), fetched(0x00), cycles(0)
{
}

//连接
void CPU::connect_bus(Bus* bus_ptr)
{
    bus = bus_ptr;
}

u32 CPU::get_cycles() const
{
    return cycles;
}


// 内存读
u8 CPU::read_mem(u16 addr)
{
    return bus ? bus->cpu_read(addr) : 0x00;
}

//内存写
void CPU::write_mem(u16 addr, u8 data)
{
    if (bus)
        bus->cpu_write(addr, data);
}


u8 CPU::fetch()
{
    if (table[opcode].mode != &CPU::IMP && table[opcode].mode != &CPU::ACC)
    {
        fetched = read_mem(addr_abs);
    }
    return fetched;
}


//栈操作
void CPU::push(u8 value)
{
    write_mem(0x0100 + sp, value);
    sp--;
}

u8 CPU::pull()
{
    sp++;
    return read_mem(0x0100 + sp);
}

// 标致位编码
u8 CPU::get_flags()
{
    u8 p = 0x00;
    if (flag_c) p |= 0x01;
    if (flag_z) p |= 0x02;
    if (flag_i) p |= 0x04;
    if (flag_d) p |= 0x08;
    p |= 0x20;
    if (flag_v) p |= 0x40;
    if (flag_n) p |= 0x80;
    return p;
}

void CPU::set_flags(u8 value)
{
    flag_c = (value & 0x01);
    flag_z = (value & 0x02);
    flag_i = (value & 0x04);
    flag_d = (value & 0x08);
    flag_v = (value & 0x40);
    flag_n = (value & 0x80);
}

// 寻址模式
// Implied
void CPU::IMP()
{
    fetched = a;
}

// Immediate
void CPU::IMM()
{
    addr_abs = pc++;
}

// Zero Page
void CPU::ZP0()
{
    addr_abs = read_mem(pc++);
    addr_abs &= 0x00FF;
}

// Zero Page X
void CPU::ZPX()
{
    addr_abs = read_mem(pc++) + x;
    addr_abs &= 0x00FF;
}

// Zero Page  Y
void CPU::ZPY()
{
    addr_abs = read_mem(pc++) + y;
    addr_abs &= 0x00FF;
}

// Absolute X
void CPU::ABX()
{
    u8 lo = read_mem(pc++);
    u8 hi = read_mem(pc++);
    addr_abs = ((static_cast<u16>(hi) << 8) | lo) + x;
    //是否发生跨页（page crossing）
    if ((addr_abs & 0xFF00) != (static_cast<u16>(hi) << 8))
        cycles++;
}

// Absolute Y
void CPU::ABY()
{
    u8 lo = read_mem(pc++);
    u8 hi = read_mem(pc++);
    addr_abs = ((static_cast<u16>(hi) << 8) | lo) + y;
    //是否发生跨页（page crossing）
    if ((addr_abs & 0xFF00) != (static_cast<u16>(hi) << 8))
        cycles++;
}

// Absolute
void CPU::ABS()
{
    u8 lo = read_mem(pc++);
    u8 hi = read_mem(pc++);
    addr_abs = ((static_cast<u16>(hi) << 8) | lo);
}

// Indexed Indirect Y: ($nn, Y)
void CPU::IZY()
{
    u8 zp = read_mem(pc++);
    // 读取当前高位的内存地址
    u8 lo = read_mem(zp & 0xFF);
    u8 hi = read_mem((zp + 1) & 0xFF);
    u16 base = (static_cast<u16>(hi) << 8) | lo;
    // 再去 + Y
    addr_abs = base + y;
    if ((addr_abs & 0xFF00) != (base & 0xFF00)) // 用 base 的页，不是 hi
        cycles++;
}

// Indexed Indirect X: ($nn, X)
/*
 * 两个的区别(比对IZY):
 * IZY 则是用一个固定的指针的位置,用Y去偏移到某段数据(Y 相当于偏移值)
 * IZX 一张指针表 挑某个指针 X = 序号
 */
void CPU::IZX()
{
    u8 zp = read_mem(pc++);
    // 读取 +X 后的高位内存地址数据
    u8 lo = read_mem((zp + x) & 0xFF);
    u8 hi = read_mem((zp + x + 1) & 0xFF);
    addr_abs = (static_cast<u16>(hi) << 8) | lo;
}


// 累加器
void CPU::ACC()
{
    fetched = a;
}

void CPU::REL()
{
    addr_rel = read_mem(pc++);
    if (addr_rel & 0x80)
        addr_rel |= 0xFF00;
}

void CPU::IND()
{
    u8 lo = read_mem(pc++);
    u8 hi = read_mem(pc++);
    u16 ptr = (static_cast<u16>(hi) << 8) | lo;

    // 6502 硬件 bug: 当指针低字节 = 0xFF 时，
    // 高字节从 $xx00 读(回绕)，而不是 $xx+1
    u8 p_lo = read_mem(ptr);
    u8 p_hi = read_mem((ptr & 0xFF00) | ((ptr + 1) & 0xFF));
    addr_abs = (static_cast<u16>(p_hi) << 8) | p_lo;
}
//END 寻址模式 13个


// 指令函数
void CPU::LDA()
{
    a = fetch();

}

