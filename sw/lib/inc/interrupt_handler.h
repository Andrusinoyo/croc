


#pragma once

#include "util.h"
#include <stdint.h>

#define MTVEC_BASE_ADRR 0X10000000

void install_exception_handler(uintptr_t dst_addr, void (*handler)(void));