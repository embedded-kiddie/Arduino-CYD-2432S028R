## LVGL font converter
 - [https://lvgl.io/tools/fontconverter][1]

### Settings

#### Name
  - noto_sans_jp_4bit_jis1_12
  - noto_sans_jp_4bit_jis1_14

#### Size
  - 12
  - 14

#### Bpp
  - 4 bit-per-pixel

#### Fallback
  - lv_font_montserrat_12
  - lv_font_montserrat_14

#### Output format
  - C file

#### TTF/WOFF font
  - [NotoSansJP-Regular.ttf][2]

#### Range
  - Symbols, Hiragana, Katakana
    - `0x00A1-0x27A1,0x3001-0x30FF,0xFF01-0xFF9F`

#### Symbols (additional)
  - Level 1 Kanji
  - Level 2 Kanji
    - `栞騙彗翳蜃`

### Optimize font height

Fix the font size and compatibility.

#### `noto_sans_jp_4bit_jis1_12.c`
```
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
...
//  .static_bitmap = 0,
```

#### `noto_sans_jp_4bit_jis1_14.c`
```
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
...
//  .static_bitmap = 0,
```

[1]: https://lvgl.io/tools/fontconverter "Font Converter - LVGL"
[2]: https://fonts.google.com/noto/specimen/Noto+Sans+JP "Noto Sans Japanese - Google Fonts"
