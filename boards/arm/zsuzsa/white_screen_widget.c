/*
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display/status_screen.h>

#if IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM)

static lv_obj_t *screen;

lv_obj_t *zmk_display_status_screen(void) {
    LOG_WRN("zmk_display_status_screen() called - CUSTOM SCREEN FUNCTION ACTIVE!");
    
    if (screen == NULL) {
        LOG_WRN("Creating new custom screen object");
        screen = lv_obj_create(NULL);
        
        // Set explicit white color for SSD1681 tricolor driver
        // Driver interprets: 0x0000=black, 0xF800=red, anything else=white
        // Try using a specific non-red, non-black value
        lv_color_t white_color = lv_color_hex(0x7FFF);  // Use 0x7FFF instead of 0xFFFF
        
        LOG_WRN("Setting background color to 0x%04X", lv_color_to16(white_color));
        lv_obj_set_style_bg_color(screen, white_color, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
        
        LOG_WRN("Custom white screen created successfully!");
    } else {
        LOG_WRN("Returning existing screen object");
    }
    
    return screen;
}

#endif /* IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM) */