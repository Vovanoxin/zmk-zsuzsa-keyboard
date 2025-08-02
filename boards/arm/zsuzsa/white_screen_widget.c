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
    if (screen == NULL) {
        screen = lv_obj_create(NULL);
        
        // Set explicit white color (anything except 0x0000 black or 0xF800 red should be white)
        lv_color_t white_color = lv_color_make(0xFF, 0xFF, 0xFF);  // Explicit white
        lv_obj_set_style_bg_color(screen, white_color, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
        
        LOG_INF("Custom white screen created with explicit white color");
    }
    
    return screen;
}

#endif /* IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM) */