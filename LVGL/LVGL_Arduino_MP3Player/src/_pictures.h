#ifndef _PICTURES_H_
#define _PICTURES_H_

LV_IMAGE_DECLARE(DETOX);
LV_IMAGE_DECLARE(Eye_of_the_Storm);
LV_IMAGE_DECLARE(Gravity);
LV_IMAGE_DECLARE(Niche);
LV_IMAGE_DECLARE(Past_Lives);
LV_IMAGE_DECLARE(SUPER_EUROBEAT);
LV_IMAGE_DECLARE(a_nation_vol2);
LV_IMAGE_DECLARE(Amazing);

const lv_image_dsc_t *pictures[] = {
  /*  0 */  & img_album,
  /*  1 */  & DETOX,
  /*  2 */  & Eye_of_the_Storm,
  /*  3 */  & Gravity,
  /*  4 */  & Niche,
  /*  5 */  & Past_Lives,
  /*  6 */  & SUPER_EUROBEAT,
  /*  7 */  & a_nation_vol2,
  /*  8 */  & Amazing,
};

#define N_PICTURES  (sizeof(pictures) / sizeof(lv_image_dsc_t *))

#endif // _PICTURES_H_