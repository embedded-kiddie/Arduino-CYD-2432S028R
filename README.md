# Arduino-CYD-2432S028R
Running Cheap Yellow Display with LovyanGFX, TFT_eSPI, and LVGL.

## Auto Detection

### Device Settings

| Device Settings   | ILI9341 (micro-USB x 1 type) | ST7789 (micro-USB x 1 + USB-C x 1 type) |
| ----------------- | ---------------------------- | --------------------------------------- |
| Panel type        | **lgfx::Panel_ILI9341**      | **lgfx::Panel_ST7789**                  |
| Bus type          | lgfx::Bus_SPI                | lgfx::Bus_SPI                           |
| Backlight control | lgfx::Light_PWM              | lgfx::Light_PWM                         |
| Touch screen type | lgfx::Touch_XPT2046          | lgfx::Touch_XPT2046                     |

### SPI Bus Settings

| SPI Bus Settings | ILI9341 (micro-USB x 1 type) | ST7789 (micro-USB x 1 + USB-C x 1 type) |
| ---------------- | ---------------------------- | --------------------------------------- |
| spi_host         | 1 (HSPI_HOST [^1])           | 1 (HSPI_HOST [^1])                      |
| spi_mode         | 0                            | 0                                       |
| freq_write       | **40000000** [^2]            | **80000000** [^2]                       |
| freq_read        | 16000000                     | 16000000                                |
| spi_3wire        | false                        | false                                   |
| use_lock         | true                         | true                                    |
| dma_channel      | 3 (SPI_DMA_CH_AUTO [^3])     | 3 (SPI_DMA_CH_AUTO [^3])                |
| pin_sclk         | 14 (CYD_TFT_SCK [^4])        | 14 (CYD_TFT_SCK [^4])                   |
| pin_mosi         | 13 (CYD_TFT_MOSI [^4])       | 13 (CYD_TFT_MOSI [^4])                  |
| pin_miso         | 12 (CYD_TFT_MISO [^4])       | 12 (CYD_TFT_MISO [^4])                  |
| pin_dc           | 2 (CYD_TFT_DC [^4])          | 2 (CYD_TFT_DC [^4])                     |

### Panel Control Settings

| Panel Control    | ILI9341 (micro-USB x 1 type) | ST7789 (micro-USB x 1 + USB-C x 1 type) |
| ---------------- | ---------------------------- | --------------------------------------- |
| pin_cs           | 15 (CYD_TFT_CS [^4])         | 15 (CYD_TFT_CS [^4])                    |
| pin_rst          | -1 [^5]                      | -1 [^5]                                 |
| pin_busy         | -1                           | -1                                      |
| panel_width      | 240                          | 240                                     |
| panel_height     | 320                          | 320                                     |
| offset_x         | 0                            | 0                                       |
| offset_y         | 0                            | 0                                       |
| offset_rotation  | **2**                        | **0**                                   |
| dummy_read_pixel | **8**                        | **16**                                  |
| dummy_read_bits  | 1                            | 1                                       |
| readable         | true                         | true                                    |
| invert           | false                        | false                                   |
| rgb_order        | false                        | false                                   |
| dlen_16bit       | false                        | false                                   |
| bus_shared       | false                        | false                                   |
| memory_width     | 240                          | 240                                     |
| memory_height    | 320                          | 320                                     |

### Backlight Control Settings

| Backlight Control | ILI9341 (micro-USB x 1 type) | ST7789 (micro-USB x 1 + USB-C x 1 type) |
| ----------------- | ---------------------------- | --------------------------------------- |
| pin_bl            | 21 (CYD_TFT_BL [^4])         | 21 (CYD_TFT_BL [^4])                    |
| invert            | false                        | false                                   |
| freq              | 12000                        | 12000                                   |
| pwm_channel       | 7                            | 7                                       |

### Touch Control Settings

| Touch Control   | ILI9341 (micro-USB x 1 type) | ST7789 (micro-USB x 1 + USB-C x 1 type) |
| --------------- | ---------------------------- | --------------------------------------- |
| x_min           | 300                          | 300                                     |
| x_max           | 3900                         | 3900                                    |
| y_min           | 3700                         | 3700                                    |
| y_max           | 200                          | 200                                     |
| pin_int         | -1 [^5]                      | -1 [^5]                                 |
| bus_shared      | false                        | false                                   |
| offset_rotation | **0**                        | **2**                                   |
| spi_host        | **-1** [^6]                  | **-1** [^6]                             |
| freq            | 1000000                      | 1000000                                 |
| pin_sclk        | 14 (CYD_TP_CLK [^4])         | 14 (CYD_TP_CLK [^4])                    |
| pin_mosi        | 13 (CYD_TP_MOSI [^4])        | 13 (CYD_TP_MOSI [^4])                   |
| pin_miso        | 12 (CYD_TP_MISO [^4])        | 12 (CYD_TP_MISO [^4])                   |
| pin_dc          | 2 (CYD_TP_CS [^4])           | 2 (CYD_TP_CS [^4])                      |

[^1]: a
[^2]: b
[^3]: c
[^4]: d
[^5]: e
[^6]: f
