#pragma once

#include <pebble.h>

#include "data.h"

#include "../windows/main_window.h"

void comm_init(uint32_t inbox, uint32_t outbox);

void comm_deinit();
