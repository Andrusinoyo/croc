// Copyright 2022 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Nicole Narr <narrn@student.ethz.ch>
// Christopher Reinwardt <creinwar@student.ethz.ch>
// Paul Scheffler <paulsc@iis.ee.ethz.ch>

#pragma once

#include <stdint.h>

#define MTVEC_BASE_ADRR 0X10000000

static inline volatile uint8_t *reg8(const unsigned int base, int offs) {
    return (volatile uint8_t *)(base + offs);
}

static inline volatile uint32_t *reg32(const unsigned int base, int offs) {
    return (volatile uint32_t *)(base + offs);
}

static inline void fence() {
    asm volatile("fence" ::: "memory");
}

static inline void fencei() {
    asm volatile("fence.i" ::: "memory");
}

static inline void wfi() {
    asm volatile("wfi" ::: "memory");
}

static inline void set_ssie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(2) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(2) : "memory");
}

static inline void set_vsie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(4) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(4) : "memory");
}

static inline void set_msie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(8) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(8) : "memory");
}

static inline void set_stie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(32) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(32) : "memory");
}

static inline void set_vstie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(64) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(64) : "memory");
}

// Enables or disables M-mode timer interrupts.
static inline void set_mtie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(128) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(128) : "memory");
}

static inline void set_seie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(512) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(512) : "memory");
}

static inline void set_vseie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(1024) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(1024) : "memory");
}

static inline void set_meie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(2058) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(2058) : "memory");
}

static inline void set_sgeie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(4096) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(4096) : "memory");
}

static inline void set_lcofie(int enable) {
    if (enable)
        asm volatile("csrs mie, %0" ::"r"(8192) : "memory");
    else
        asm volatile("csrc mie, %0" ::"r"(8192) : "memory");
}

// Enables or disables M-mode global interrupts.
static inline void set_mie(int enable) {
    if (enable)
        asm volatile("csrsi mstatus, 8" ::: "memory");
    else
        asm volatile("csrci mstatus, 8" ::: "memory");
}
//#################################

//#################################

//#################################
static inline int get_mtie() {
    unsigned int mie;
    asm volatile("csrr %0, mie" : "=r"(mie));
    return (mie >> 7) & 1;
}
//#################################

// Leer el vector de interrupciones
static inline uint32_t read_mtvec(void) {
    uint32_t val;
    asm volatile("csrr %0, mtvec" : "=r"(val) :: "memory");
    return val;
}

// Get cycle count since reset
static inline uint64_t get_mcycle() {
    uint64_t mcycle;
    asm volatile("csrr %0, mcycle" : "=r"(mcycle)::"memory");
    return mcycle;
}

// This may also be used to invoke code that does not return.
static inline uint64_t invoke(void *code) {
    uint64_t (*code_fun_ptr)(void) = code;
    fencei();
    return code_fun_ptr();
}

//#################################
// 1 -> vectored, 0 -> direct
static inline void set_mtvec_mode(int vectored) {
    uint32_t mtvec;
    asm volatile("csrr %0, mtvec" : "=r"(mtvec));


    // Borra los bits [1:0] y agrega el nuevo modo
    mtvec = (mtvec & ~0x3) | (vectored & 0x1);

    //asm volatile("csrw mtvec, %0" :: "r"(mtvec));
    asm volatile("csrw mtvec, %0" :: "r"(0x10000000));
}
//#################################

// Set global pointer and return prior value. Use with caution.
static inline void *gprw(void *gp) {
    void *ret;
    asm volatile("mv %0, gp" : "=r"(ret)::"memory");
    if (gp) asm volatile("mv gp, %0" ::"r"(gp) : "memory", "gp");
    return ret;
}

// If a call yields a nonzero return, return that immediately as an int.
#define CHECK_CALL(call) \
    { \
        int __ccret = (volatile int)(call); \
        if (__ccret) return __ccret; \
    }

// If a condition; if it is untrue, ummediately return an error code.
#define CHECK_ASSERT(ret, cond) \
    if (!(cond)) return (ret);

#define MIN(a, b) (((a) <= (b)) ? (a) : (b))
