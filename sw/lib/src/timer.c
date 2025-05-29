// Copyright 2024 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Philippe Sauter <phsauter@iis.ee.ethz.ch>

#include "timer.h"
#include "util.h"
#include "config.h"

void sleep_ms(uint32_t ms) {
    uint32_t config = \
        (1 << CFG_LOW_REG_CLOCK_SOURCE_BIT) | // from 32.768 kHz ref clock
        (1 << CFG_LOW_REG_PRESC_ENABLE_BIT) | // enable prescaler
        (31 << CFG_LOW_REG_PRESC_VALUE_BIT) | // prescaler value
        (1 << CFG_LOW_REG_CMP_CLR_BIT)      | // auto-clear
        (1 << CFG_LOW_REG_IRQ_ENABLE_BIT)   | // enable IRQ
        (1 << CFG_LOW_REG_ENABLE_BIT);        // enable timer

    // disable timer
    *reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) = 0;

    *reg32(TIMER_BASE_ADDR, TIMER_CMP_LOW_REG_OFFSET) = ms;

    set_mtie(1);  // Machine Timer Interrupt Enable
    set_mie(1);  // Global Interrupt Enable

    // start timer
    *reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) = config;

    asm volatile("wfi");

    // turn off timer
    *reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) &= ~(1 << CFG_LOW_REG_ENABLE_BIT);

    // disable timer interrupt
    set_mtie(0);
}

 void sleep_ms_2(uint32_t ms) {
    uint32_t config = \
        (1 << CFG_LOW_REG_CLOCK_SOURCE_BIT) | // from 32.768 kHz ref clock
        (1 << CFG_LOW_REG_PRESC_ENABLE_BIT) | // enable prescaler
        (31 << CFG_LOW_REG_PRESC_VALUE_BIT) | // prescaler value
        (1 << CFG_LOW_REG_CMP_CLR_BIT)      | // auto-clear
        (1 << CFG_LOW_REG_IRQ_ENABLE_BIT)   | // enable IRQ
        (1 << CFG_LOW_REG_ENABLE_BIT);        // enable timer

    // disable timer
    *reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) = 0;

    *reg32(TIMER_BASE_ADDR, TIMER_CMP_LOW_REG_OFFSET) = ms;

    // set_mtie(1);  // Machine Timer Interrupt Enable
    // set_mie(1);  // Global Interrupt Enable

    // start timer
    *reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) = config;

    asm volatile("wfi");

    // turn off timer
    //*reg32(TIMER_BASE_ADDR, CFG_LOW_REG_OFFSET) &= ~(1 << CFG_LOW_REG_ENABLE_BIT);

    // disable timer interrupt
    // set_mtie(0);
} 

void enable_interrupt(){

    set_mtie(1);  // Machine Timer Interrupt Enable
    set_mie(1);  // Global Interrupt Enable

}

void all_interrupt_enable(){

    set_ssie(1); // 1

    set_vsie(1); // 2

    set_msie(1); // 3

    set_stie(1); // 5

    set_vstie(1); // 6

    set_mtie(1);  // 7 Machine Timer Interrupt Enable

    set_seie(1); // 9

    set_vseie(1); // 10

    set_meie(1); // 11

    set_sgeie(1); // 12

    set_lcofie(1); // 13
         
    set_mie(1);  // Global Interrupt Enable

}

void disable_interrupt(){

    set_mtie(0);  // Machine Timer Interrupt Enable
    set_mie(0);  // Global Interrupt Enable

}
