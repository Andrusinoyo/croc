
#include <stdint.h>
#include "util.h"

#define MTVEC_BASE_ADRR 0X10000000

// static inline void write_mtvec(void* base, uint32_t mode) {
    
//         uintptr_t val = ((uintptr_t)base & ~0x3) | (mode & 0x3);
    
//     asm volatile("csrw mtvec, %0" :: "r"(val) : "memory");
    
// }

void install_exception_handler_vec(uint32_t dst_addr, void (*handler)(void)) {

    uint32_t mtvec = read_mtvec();
    uint32_t base = mtvec & ~0x3; // quitar los 2 bits de modo

    uint32_t handler_addr = base + 4 * dst_addr; // 7 = timer interrupt

    uint32_t offset = (uint32_t)handler - handler_addr;

    if ((offset >= (1 << 20)) || (offset < -(1 << 19))) {
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

    //asm volatile("fence.i" ::: "memory");
}

void install_exception_handler_dir(void (*handler)(void)) {

    uintptr_t mtvec = read_mtvec();
    uintptr_t base = mtvec & ~0x3; // quitar los 2 bits de modo

    uintptr_t val = ((uintptr_t)handler & ~0x3) | (0 & 0x3);
    
    asm volatile("csrw mtvec, %0" :: "r"(val) : "memory");

    //asm volatile("fence.i" ::: "memory");

}

