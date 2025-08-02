/*
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/display/cfb.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(white_screen, CONFIG_LOG_DEFAULT_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_DISPLAY)

#define DISPLAY_NODE DT_CHOSEN(zephyr_display)

static const struct device *display_dev;

static int white_screen_init(void) {
    display_dev = DEVICE_DT_GET(DISPLAY_NODE);
    
    if (!device_is_ready(display_dev)) {
        LOG_ERR("Display device not ready");
        return -ENODEV;
    }

    LOG_INF("Display device ready");

    // Get display capabilities
    struct display_capabilities caps;
    display_get_capabilities(display_dev, &caps);
    
    LOG_INF("Display: %dx%d, %d bpp", caps.x_resolution, caps.y_resolution, caps.supported_pixel_formats);

    // Clear display with white
    display_blanking_off(display_dev);
    
    // Fill entire screen with white pixels
    uint8_t *white_buffer = k_malloc(caps.x_resolution * caps.y_resolution / 8); // 1 bit per pixel
    if (white_buffer) {
        // Set all bits to 1 for white (for monochrome displays)
        memset(white_buffer, 0xFF, caps.x_resolution * caps.y_resolution / 8);
        
        struct display_buffer_descriptor desc = {
            .buf_size = caps.x_resolution * caps.y_resolution / 8,
            .width = caps.x_resolution,
            .height = caps.y_resolution,
            .pitch = caps.x_resolution,
        };
        
        int ret = display_write(display_dev, 0, 0, &desc, white_buffer);
        if (ret < 0) {
            LOG_ERR("Failed to write to display: %d", ret);
        } else {
            LOG_INF("White screen displayed successfully");
        }
        
        k_free(white_buffer);
    } else {
        LOG_ERR("Failed to allocate display buffer");
        return -ENOMEM;
    }
    
    return 0;
}

SYS_INIT(white_screen_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

#endif /* IS_ENABLED(CONFIG_ZMK_DISPLAY) */