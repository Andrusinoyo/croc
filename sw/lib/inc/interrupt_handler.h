


#pragma once

#include "util.h"
#include "print.h"
#include <stdint.h>

#define MTVEC_BASE_ADRR 0X10000000

void install_exception_handler_vec(uint32_t dst_addr, void (*handler)(void));
void install_exception_handler_dir(void (*handler)(void));