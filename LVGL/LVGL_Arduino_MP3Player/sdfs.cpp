/*--------------------------------------------------------------------------------
 * LVGL file system interfaces for handling an image file on SD card
 * https://github.com/lvgl/lvgl/blob/master/src/libs/fsdrv/lv_fs_arduino_sd.cpp
 * NOTE: uncomment the followings to use SdFat
 *  "#define SDFATFS_USED" in CYD_Audio.h
 *  "#define USE_UTF8_LONG_NAMES 1" in SdFatConfig.h
 *--------------------------------------------------------------------------------*/
#include "lvgl.h"
#include "sdfs.h"

#ifdef  LV_MEM_POOL_ALLOC // defined in lv_cong.h
#define MY_MALLOC(size) lv_malloc(size)
#define MY_FREE(addr)   lv_free(addr)
#else
#define MY_MALLOC(size) heap_caps_malloc(size, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
#define MY_FREE(addr)   free(addr)
#endif

#if MY_USE_FS_ARDUINO_SD == 1
/*--------------------------------------------------------------------------------
 * Without cache
 *--------------------------------------------------------------------------------*/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

#ifdef USE_SDFAT

#define FS_MODE int
static File my_file;

#else

#define FS_MODE const char *
typedef struct MyFile {
    File file;
} MyFile;

// alternative to FS.h definition
enum SeekMode {
  SeekSet = 0,
  SeekCur = 1,
  SeekEnd = 2
};

#endif

void lv_fs_clear_cache(void) {}

/**
 * Register a driver for the SD File System interface
 */
void lv_fs_arduino_sd_init(void)
{
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    fs_drv.letter = MY_FS_ARDUINO_SD_LETTER;
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = NULL;
    fs_drv.dir_open_cb = NULL;
    fs_drv.dir_read_cb = NULL;

    lv_fs_drv_register(&fs_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);

    FS_MODE flags;
    if(mode == LV_FS_MODE_WR)
        flags = FILE_WRITE;
    else if(mode == LV_FS_MODE_RD)
        flags = FILE_READ;
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = FILE_WRITE;

#ifdef USE_SDFAT
    my_file = SD.open(path, flags);
    if(!my_file) {
        return NULL;
    }

    return (void *)&my_file;
#else
    File my_file = SD.open(path, flags);
    if(!my_file) {
        return NULL;
    }

    MyFile * lf = new MyFile{my_file};
    return (void *)lf;
#endif
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    LV_UNUSED(drv);

#ifdef USE_SDFAT
    my_file.close();
#else
    MyFile * lf = (MyFile *)file_p;
    lf->file.close();
    delete lf;
#endif

    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    LV_UNUSED(drv);

#ifdef USE_SDFAT
    *br = my_file.read((uint8_t *)buf, btr);
#else
    MyFile * lf = (MyFile *)file_p;
    *br = lf->file.read((uint8_t *)buf, btr);
#endif

    return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btw       Bytes To Write
 * @param bw        the number of real written bytes (Bytes Written)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    LV_UNUSED(drv);

#ifdef USE_SDFAT
    *bw = my_file.write((uint8_t *)buf, btw);
#else
    MyFile * lf = (MyFile *)file_p;
    *bw = lf->file.write((uint8_t *)buf, btw);
#endif

    return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);

    SeekMode mode = SeekSet;
    if(whence == LV_FS_SEEK_SET)
        mode = SeekSet;
    else if(whence == LV_FS_SEEK_CUR)
        mode = SeekCur;
    else if(whence == LV_FS_SEEK_END)
        mode = SeekEnd;

#ifdef USE_SDFAT
    int rc;
    switch (mode) {
      case SeekSet:
        rc = my_file.seekSet(pos);
        break;
      case SeekCur:
        rc = my_file.seekCur(pos);
        break;
      case SeekEnd:
        rc = my_file.seekEnd(pos);
        break;
    }
#else
    MyFile * lf = (MyFile *)file_p;
    int rc = lf->file.seek(pos, mode);
#endif

    return rc < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_p variable
 * @param pos_p     pointer to store the result
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    LV_UNUSED(drv);

#ifdef USE_SDFAT
    *pos_p = my_file.curPosition();
#else
    MyFile * lf = (MyFile *)file_p;
    *pos_p = lf->file.position();
#endif

    return (int32_t)(*pos_p) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

#elif MY_USE_FS_ARDUINO_SD == 2
/*--------------------------------------------------------------------------------
 * With cache
 *--------------------------------------------------------------------------------*/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

typedef struct {
  char *    path;
  char *    buffer;
  size_t    size;
  uint32_t  position;
} FsCache_t;

static FsCache_t fs_cache = {};
static lv_fs_drv_t fs_drv;

void lv_fs_clear_cache(void) {
  if (fs_cache.path) {
    MY_FREE(fs_cache.path);
    fs_cache.path = 0;
  }

  if (fs_cache.buffer) {
    MY_FREE(fs_cache.buffer);
    fs_cache.buffer = 0;
  }
}

/**
 * Register a driver for the SD File System interface
 */
void lv_fs_arduino_sd_init(void)
{
    lv_fs_drv_init(&fs_drv);

    fs_drv.letter = MY_FS_ARDUINO_SD_LETTER;
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = NULL;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = NULL;
    fs_drv.dir_open_cb = NULL;
    fs_drv.dir_read_cb = NULL;

    lv_fs_drv_register(&fs_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);
    LV_UNUSED(mode);

    if (fs_cache.path && strcmp(fs_cache.path, path) != 0) {
      lv_fs_clear_cache();
    }

    if (!fs_cache.path) {
      size_t size = strlen(path);
      fs_cache.path = (char *)MY_MALLOC(size + 1);
      assert(fs_cache.path);
      if (fs_cache.path) {
        strcpy(fs_cache.path, path);
      }

      File file = SD.open(path, FILE_READ);
#ifdef USE_SDFAT
      size = file.fileSize();
#else
      size = file.size();
#endif
      fs_cache.buffer = (char *)MY_MALLOC(size);
      assert(fs_cache.buffer);
      if (fs_cache.buffer) {
        fs_cache.size = file.read((uint8_t *)fs_cache.buffer, size);
        assert(fs_cache.size == size);
      }
      file.close();
    }

    fs_cache.position = 0;
    return (void *)drv;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    if (fs_cache.position + btr > fs_cache.size) {
      btr = fs_cache.size - fs_cache.position;
    }

    memcpy(buf, &fs_cache.buffer[fs_cache.position], btr);
    fs_cache.position += (*br = btr);

    return LV_FS_RES_OK;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    switch (whence) {
      case LV_FS_SEEK_CUR:
        fs_cache.position += pos;
        break;
      case LV_FS_SEEK_END:
        fs_cache.position = (fs_cache.size - 1) - pos;
        break;
      case LV_FS_SEEK_SET:
      default:
        fs_cache.position = pos;
        break;
    }

    if (fs_cache.position < 0) {
      fs_cache.position = 0;
    } else if (fs_cache.position >= fs_cache.size) {
      fs_cache.position = fs_cache.size - 1;
    }

    return LV_FS_RES_OK;
}

/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_p variable
 * @param pos_p     pointer to store the result
 * @return          LV_FS_RES_OK: no error or any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    *pos_p = fs_cache.position;
    return LV_FS_RES_OK;
}

#endif // MY_USE_FS_ARDUINO_SD