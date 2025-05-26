


#pragma once

#include "util.h"
#include <stdint.h>

#define MTVEC_BASE_ADRR 0X10000000

void install_exception_handler_vec(uintptr_t dst_addr, void (*handler)(void));
void install_exception_handler_dir(void (*handler)(void));