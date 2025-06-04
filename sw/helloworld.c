// Copyright (c) 2024 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0/
//
// Authors:
// - Philippe Sauter <phsauter@iis.ee.ethz.ch>

#include "uart.h"
#include "print.h"
#include "timer.h"
#include "gpio.h"
#include "util.h"
#include "rtc.h"
#include "interrupt_handler.h"

/// @brief Example integer square root
/// @return integer square root of n
uint32_t isqrt(uint32_t n) {
    uint32_t res = 0;
    uint32_t bit = (uint32_t)1 << 30;

    while (bit > n) bit >>= 2;

    while (bit) {
        if (n >= res + bit) {
            n -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return res;
}


volatile int handled = 0; 

// Declara que esta funcion va a ser usada como manejador de interrupciones
//void timer_interrupt_handler(void) __attribute__((interrupt)); // Deberia funcionar

 __attribute__((interrupt))
void timer_interrupt_handler(void) {
    printf("Soy el manejador de interrupciones y funciono, que pereza, soy la polla\n");
    handled = 1;
    uart_write_flush();
}

int main() {
    uart_init(); // setup the uart peripheral

    // simple printf support (only prints text and hex numbers)
    // printf("Hello World!\n");
    // printf("Hola soy el primer dia de 155 sobre el tfm\n");
    // printf("Prueba tm\n");
    // //print_tm(&loco);
    // // wait until uart has finished sending
    // uart_write_flush();
 

    // // toggling some GPIOs
    // gpio_set_direction(0xFFFF, 0x000F); // lowest four as outputs
    // gpio_write(0x0A);  // ready output pattern
    // gpio_enable(0xFF); // enable lowest eight
    // // wait a few cycles to give GPIO signal time to propagate
    // asm volatile ("nop; nop; nop; nop; nop;");
    // printf("GPIO (expect 0xA0): 0x%x\n", gpio_read());

    // gpio_toggle(0x0F); // toggle lower 8 GPIOs
    // asm volatile ("nop; nop; nop; nop; nop;");
    // printf("GPIO (expect 0x50): 0x%x\n", gpio_read());
    // uart_write_flush();

    // // doing some compute
    // uint32_t start = get_mcycle();
    // uint32_t res   = isqrt(1234567890UL);
    // uint32_t end   = get_mcycle();
    // printf("Result: 0x%x, Cycles: 0x%x\n", res, end - start);
    // uart_write_flush();


    //install_exception_handler_vec(7, &timer_interrupt_handler);

    //all_interrupt_enable();

    printf("mtvec antes de modifdfgdsdstfgsaaicarrrs<r ");
    print_mtvec();

    // install_exception_handler_vec(1, &timer_interrupt_handler);
    // install_exception_handler_vec(2, &timer_interrupt_handler);
    // install_exception_handler_vec(3, &timer_interrupt_handler);
    // install_exception_handler_vec(5, &timer_interrupt_handler);
    // install_exception_handler_vec(6, &timer_interrupt_handler);
    
    // install_exception_handler_vec(9, &timer_interrupt_handler);
    // install_exception_handler_vec(10, &timer_interrupt_handler);
    // install_exception_handler_vec(11, &timer_interrupt_handler);
    // install_exception_handler_vec(12, &timer_interrupt_handler);
    // install_exception_handler_vec(13, &timer_interrupt_handler);


    enable_interrupt();

    install_exception_handler_vec(7, &timer_interrupt_handler);

    printf("Handles instanciado ");

    print_mtvec();

    printf("Manejador de interrupciones instanciado, pasamos a sleep\n");
    uart_write_flush();
    sleep_ms_2(2);
    while (!handled)
    {
    
    }
    
    handled = 0;
    printf("Saliendo del sleep con manejador de interrupciones\n");
    uart_write_flush();


    // PRUEBA DE INTERRUPCIONES. 
    // CON INTERRUPCIONES DESHABILITADAS NUNCA SALIMOS DEL TIMER

    printf("Prueba de interrupciones\n");
    uart_write_flush();

    printf("Habilitamos interrupciones\n");
    uart_write_flush();

    enable_interrupt();
    printf("Entrando en sleep CON interrupciones\n");
    uart_write_flush();

    sleep_ms_2(2);
    while (!handled)
    {
    
    }

    printf("Saliendo de sleep CON interrupciones\n");
    uart_write_flush();
    
    disable_interrupt();

    // printf("Deshabilitamos interrupciones\n");
    // uart_write_flush();
    // disable_interrupt();
    // printf("Entrando en sleep SIN interrupciones\n");
    // sleep_ms_2(2);
    // printf("Saliendo de sleep SIN interrupciones???\n");

    
    // PRUEBA MANEJADOR DE INTERRUPCIONES

    // Instalamos el manejador de instrucciones para el puerto 7 (mtie)
    //install_exception_handler(7, &timer_interrupt_handler);
    //interrupt_set_handler(7, &timer_interrupt_handler);




    

    // using the timer
    uint32_t counter_timer = 0;
    while(counter_timer < 20) {
    printf("Tick\n");
    sleep_ms(1);
    printf("Tock\n");
    sleep_ms(1);
    counter_timer++;
    uart_write_flush();
    }
    return 1;
}
