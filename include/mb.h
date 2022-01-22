#pragma once

#include "stdint.h"

uint32_t get_vc_firmware_rev(void);
uint8_t* get_board_mac_address(uint8_t* buffer);