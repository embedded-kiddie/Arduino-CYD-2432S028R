#ifndef _PICTURES_H_
#define _PICTURES_H_

LV_IMG_DECLARE(DETOX);
LV_IMG_DECLARE(Eye_of_the_Storm);
LV_IMG_DECLARE(Gravity);
LV_IMG_DECLARE(Niche);
LV_IMG_DECLARE(Past_Lives);
LV_IMG_DECLARE(SUPER_EUROBEAT);

const lv_image_dsc_t *pictures[] = {
  /*  0 */  & ui_img_album_png,
  /*  1 */  & DETOX,
  /*  2 */  & Eye_of_the_Storm,
  /*  3 */  & Gravity,
  /*  4 */  & Niche,
  /*  5 */  & Past_Lives,
  /*  6 */  & SUPER_EUROBEAT,
};

#define N_PICTURES  (sizeof(pictures) / sizeof(lv_image_dsc_t *))

#endif // _PICTURES_H_