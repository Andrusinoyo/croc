
#include <stdint.h>
#include "util.h"

#define MTVEC_BASE_ADRR 0X10000000

void install_exception_handler(uintptr_t dst_addr, void (*handler)(void)) {

    uintptr_t mtvec = read_mtvec();
    uintptr_t base = mtvec & ~0x3; // quitar los 2 bits de modo

    uintptr_t handler_addr = base + 4 * dst_addr; // 7 = timer interrupt

    uintptr_t offset = (uintptr_t)handler - handler_addr;

    if ((offset >= (1 << 19)) || (offset < -(1 << 19))) {
        // offset fuera del rango de la instrucción JAL
        return;
    }

    uint32_t imm = (uint32_t)offset;

    uint32_t instr =
        ((imm & 0x100000) << 11) |  // bit 20 -> 31
        ((imm & 0xFF000))        |  // bits 19:12 -> 19:12
        ((imm & 0x800) << 9)     |  // bit 11 -> 20
        ((imm & 0x7FE) << 20)    |  // bits 10:1 -> 30:21
        0x6F;                       // opcode for JAL

    *(volatile uint32_t*)dst_addr = instr;

    asm volatile("fence.i" ::: "memory");
}