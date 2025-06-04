
#include <stdint.h>
#include "util.h"
#include "print.h"


#define MTVEC_BASE_ADRR 0X10000000

// static inline void write_mtvec(void* base, uint32_t mode) {
    
//         uintptr_t val = ((uintptr_t)base & ~0x3) | (mode & 0x3);
    
//     asm volatile("csrw mtvec, %0" :: "r"(val) : "memory");
    
// }

void install_exception_handler_vec(uint32_t dst_addr, void (*handler)(void)) {

    uint32_t mtvec = read_mtvec();
    uint32_t base = mtvec & ~0x3; // quitar los 2 bits de modo

    printf("base: %" PRIxPTR "\n", base);

    // uint32_t handler_addr = base + 4 * dst_addr; // 7 = timer interrupt
    uint32_t *handler_addr = (uint32_t*) (base + 4 * dst_addr); // 7 = timer interrupt

    printf("handler_addr: %" PRIxPTR "\n", handler_addr);
    printf("handler: %" PRIxPTR "\n", (uint32_t)handler);

    int32_t offset = (uint32_t)handler - (uint32_t) handler_addr;

    printf("Offset (handles - handlr addrs): %" PRIxPTR "\n", offset);

    if ((offset >= (1 << 19)) || (offset < -(1 << 19))) {
    return;
    }

    uint32_t offset_uimm = offset;

    uint32_t jmp_ins = ((offset_uimm & 0x7fe) << 20) |     // imm[10:1] -> 21
                     ((offset_uimm & 0x800) << 9) |      // imm[11] -> 20
                     (offset_uimm & 0xff000) |           // imm[19:12] -> 12
                     ((offset_uimm & 0x100000) << 11) |  // imm[20] -> 31
                     0x6f;                               // J opcode



    *handler_addr = jmp_ins;

    //fencei();

}

void install_exception_handler_dir(void (*handler)(void)) {

    uintptr_t mtvec = read_mtvec();
    uintptr_t base = mtvec & ~0x3; // quitar los 2 bits de modo

    uintptr_t val = ((uintptr_t)handler & ~0x3) | (0 & 0x3);
    
    asm volatile("csrw mtvec, %0" :: "r"(val) : "memory");

    //asm volatile("fence.i" ::: "memory");

}

