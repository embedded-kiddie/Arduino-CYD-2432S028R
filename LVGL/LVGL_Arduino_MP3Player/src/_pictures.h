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
LV_IMAGE_DECLARE(MF_GHOST);
LV_IMAGE_DECLARE(Avril_Lavigne_Greatest_Hits);
LV_IMAGE_DECLARE(ballads);
LV_IMAGE_DECLARE(globe_cruise_record_1995_2000);
LV_IMAGE_DECLARE(delicious_way);
LV_IMAGE_DECLARE(DEEP_RIVER);
LV_IMAGE_DECLARE(HEART_STATION);
LV_IMAGE_DECLARE(Mrs10);
LV_IMAGE_DECLARE(Winter_Into_Spring);
LV_IMAGE_DECLARE(BEST_OF_SOUL);
LV_IMAGE_DECLARE(Twilight);

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
  /*  9 */  & MF_GHOST,
  /* 10 */  & Avril_Lavigne_Greatest_Hits,
  /* 11 */  & ballads,
  /* 12 */  & globe_cruise_record_1995_2000,
  /* 13 */  & delicious_way,
  /* 14 */  & DEEP_RIVER,
  /* 15 */  & HEART_STATION,
  /* 16 */  & Mrs10,
  /* 17 */  & Winter_Into_Spring,
  /* 18 */  & BEST_OF_SOUL,
  /* 19 */  & Twilight,
};

#define N_PICTURES  (sizeof(pictures) / sizeof(lv_image_dsc_t *))

#endif // _PICTURES_H_