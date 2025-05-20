// #include "rtc.h"
// #include "util.h"
// //#include "time_utils.h"
// #include "timer.h"
// #include "time_utils.h"
// #include "config.h"

// static volatile uint64_t rtc_ms_counter = 0;

// static volatile uint64_t rtc_alarm_time = 0;

// static volatile bool rtc_enabled = false;
// static volatile bool alarm_set = false;

// void rtc_enable(void) {
//     rtc_enabled = true;
//     //timer_start(); // usa el timer del CROC
// }

// void rtc_disable(void) {
//     rtc_enabled = false;
//     //timer_stop();
// }

// void rtc_reset(void) {
//     rtc_ms_counter = 0;
// }

// struct tm rtc_get_time(void) {
//     struct tm t;
//     epoch_ms_to_tm(rtc_ms_counter, &t);
//     return t;
// }

// void rtc_set_time(struct tm* t) {
//     rtc_ms_counter = tm_to_epoch_ms(t);
// }

// int rtc_set_new_alarm(struct tm* alarm_time) {
//     rtc_alarm_time = tm_to_epoch_ms(alarm_time);
//     alarm_set = true;
//     return 0;
// }

// /* void rtc_interrupt_handler(void) __attribute__((interrupt));
// void rtc_interrupt_handler(void) {

//     if (!rtc_enabled) return;

//     rtc_ms_counter++;

//     if (alarm_set && rtc_ms_counter >= rtc_alarm_time) {
//         alarm_set = false;
//         extern void rtc_interrupt_handler(void);
//         rtc_interrupt_handler(); // la aplicación define esta función
//     }   

// } */

// /*
// void rtc_enable_interrupts(void) {
//     timer_enable_interrupts();  // conecta ISR del timer
// }

// // Función que debe ser llamada por la ISR del timer
// void rtc_tick_handler(void) {
//     if (!rtc_enabled) return;

//     rtc_ms_counter++;

//     if (alarm_set && rtc_ms_counter >= rtc_alarm_time) {
//         alarm_set = false;
//         extern void rtc_interrupt_handler(void);
//         rtc_interrupt_handler(); // la aplicación define esta función
//     }
// }
// */