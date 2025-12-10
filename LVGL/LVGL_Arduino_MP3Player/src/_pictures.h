#ifndef _PICTURES_H_
#define _PICTURES_H_

LV_IMAGE_DECLARE(img_album);
LV_IMAGE_DECLARE(jess_bailey);
LV_IMAGE_DECLARE(jim_luo);
LV_IMAGE_DECLARE(majed_swan);
LV_IMAGE_DECLARE(steve_busch);
LV_IMAGE_DECLARE(zoshua_colah);

const lv_image_dsc_t *pictures[] = {
  /*  0 */  & img_album,
  /*  1 */  & jess_bailey,
  /*  2 */  & jim_luo,
  /*  3 */  & majed_swan,
  /*  4 */  & steve_busch,
  /*  5 */  & zoshua_colah,
};

#define N_PICTURES  (sizeof(pictures) / sizeof(lv_image_dsc_t *))

#endif // _PICTURES_H_