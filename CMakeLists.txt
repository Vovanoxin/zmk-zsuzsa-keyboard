# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM AND (BOARD STREQUAL "zsuzsa_left" OR BOARD STREQUAL "zsuzsa_right"))
  target_sources(app PRIVATE boards/arm/zsuzsa/white_screen_widget.c)
endif()