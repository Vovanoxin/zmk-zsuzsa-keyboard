/*
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>

#if IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM)

static lv_obj_t *screen;

lv_obj_t *zmk_display_status_screen(void) {
    if (screen == NULL) {
        screen = lv_obj_create(NULL);
        
        // Set the screen background to white
        lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
        
        LOG_INF("Custom white screen created");
    }
    
    return screen;
}

#endif /* IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM) */