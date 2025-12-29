//================================================================================
// ESP32 Print memory usage for debugging
//================================================================================
#ifndef _ESP32_HPP_
#define _ESP32_HPP_

#include "Esp.h"

#if ESP_ARDUINO_VERSION_MAJOR >= 3
#include "chip-debug-report.h"  // void printBeforeSetupInfo(void); void printAfterSetupInfo(void);
#include "freertos_stats.h"     // void printRunningTasks(Print &printer);
#endif

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
typedef struct {
//size_t sketch_space;
//size_t sketch_size;
  size_t total;
  size_t free;
  size_t allocated;
  size_t minimum;
  size_t largest;
} ESP32MemInfo_t;

// https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Esp.cpp
// https://github.com/espressif/esp-idf/blob/master/components/heap/include/esp_heap_caps.h#L32-L51
// MALLOC_CAP_DMA     : Memory must be able to accessed by DMA
// MALLOC_CAP_SPIRAM  : Memory must be in SPI RAM
// MALLOC_CAP_INTERNAL: Memory must be internal; specifically it should not disappear when flash/spiram cache is switched off
// MALLOC_CAP_DEFAULT : Memory can be returned in a non-capability-specific memory allocation (e.g. malloc(), calloc()) call
// https://github.com/espressif/esp-idf/blob/master/components/heap/heap_caps.c#L408-L427

//--------------------------------------------------------------------------------
// MALLOC_CAP_DEFAULT
//--------------------------------------------------------------------------------
#define HEAP_MEM_CAPS (MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL)

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
class ESP32Info {
private:
  static void get_mem_info(ESP32MemInfo_t *mem) {
    multi_heap_info_t info;
    heap_caps_get_info(&info, HEAP_MEM_CAPS);
//  mem->sketch_space = ESP.getFreeSketchSpace();
//  mem->sketch_size  = ESP.getSketchSize();
    mem->total        = heap_caps_get_total_size(HEAP_MEM_CAPS);
    mem->free         = info.total_free_bytes;
    mem->allocated    = info.total_allocated_bytes;
    mem->minimum      = info.minimum_free_bytes;
    mem->largest      = info.largest_free_block;
  }

  static void print_mem_info(ESP32MemInfo_t *mem) {
    printf("============ Memory Usage =============\n");
//  printf("Sketch space           :%7lu\n", mem->sketch_space);
//  printf("Sketch size            :%7lu\n", mem->sketch_size);
    printf("Heap total size        :%7lu\n", mem->total);
    printf("Heap total free        :%7lu\n", mem->free);
    printf("Heap total allocated   :%7lu\n", mem->allocated);
    printf("Heap free minimum      :%7lu\n", mem->minimum);
    printf("Heap free largest block:%7lu\n", mem->largest);
  }

  static void print_diff(ESP32MemInfo_t *start, ESP32MemInfo_t *end) {
    printf("Heap total size        :%7lu (%7lu ==> %7lu)\n", end->total     - start->total,     start->total,     end->total    );
    printf("Heap total free        :%7lu (%7lu ==> %7lu)\n", end->free      - start->free,      start->free,      end->free     );
    printf("Heap total allocated   :%7lu (%7lu ==> %7lu)\n", end->allocated - start->allocated, start->allocated, end->allocated);
    printf("Heap free minimum      :%7lu (%7lu ==> %7lu)\n", end->minimum   - start->minimum,   start->minimum,   end->minimum  );
    printf("Heap free largest block:%7lu (%7lu ==> %7lu)\n", end->largest   - start->largest,   start->largest,   end->largest  );
  }

public:
  static void print_heap(void) {
    ESP32MemInfo_t mem;
    get_mem_info(&mem);
    print_mem_info(&mem);

    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/heap_debug.html
    // https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/mem_alloc.html
    if (psramFound()) {
      printf("PSRAM total size       :%7lu\n", ESP.getPsramSize());     // heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
      printf("PSRAM free  size       :%7lu\n", ESP.getFreePsram());     // heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
      printf("PSRAM free  minimum    :%7lu\n", ESP.getMinFreePsram());  // heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM);
    }

#if __has_include(<lvgl.h>)
    // LVGL memory usage
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    uint32_t used = mon.total_size - mon.max_used;
    printf("LVGL free size         :%7lu (Used: %lu %%)\n", mon.free_size, mon.used_pct);
    printf("LVGL maximum used size :%7lu (Rest: %lu %%)\n", used, (100 * used) / mon.total_size);
#endif
  }

  //--------------------------------------------------------------------------------
  // Usage:
  //  static ESP32MemInfo_t heap;
  //  ESP32Info::heap_begin(&heap);
  //  ...
  //  ESP32Info::heap_end(&heap);
  //--------------------------------------------------------------------------------
  static void heap_begin(ESP32MemInfo_t *start) {
    get_mem_info(start);
  }
  
  static void heap_end(ESP32MemInfo_t *start) {
    ESP32MemInfo_t end;
    get_mem_info(&end);
    print_diff(start, &end);
  }

  static void print_task(void) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/freertos_stats.h
    // https://forum.arduino.cc/t/how-to-make-tasks-and-determine-stack-size-in-freertos/978325/29
    printRunningTasks(Serial);
#else
    printf("Loop Task Stack High Water Mark: %lu/%lu bytes\n", uxTaskGetStackHighWaterMark(NULL), CONFIG_ARDUINO_LOOP_STACK_SIZE);
#endif
  }

  static void print_info(void) {
#if   0
    // https://en.cppreference.com/w/cpp/compiler_support
    // https://forum.arduino.cc/t/which-version-of-c-is-currently-supported/1285868/13
    // https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32/api-guides/cplusplus.html
    // https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#:~:text=__cplusplus,gnu%2B%2B26.
    // 199711 ➜ C++98 or C++03 standards.
    // 201103 ➜ C++11 standard.
    // 201402 ➜ C++14 standard.
    // 201703 ➜ C++17 standard.
    // 202002 ➜ C++20 standard.
    // 202302 ➜ C++23 standard.
    const struct {
      const uint32_t ver;
      const char* std; 
    } cpp[] = {
      {199711, "C++03"},
      {201103, "C++11"},
      {201402, "C++14"},
      {201703, "C++17"},
      {202002, "C++20"},
      {202302, "C++23"},
      {203000, "C++xx"},
    };
    const char *cpp_ver = "";
    for (int i = 0; i < sizeof(cpp) / sizeof(cpp[0]) - 1; ++i) {
      if (cpp[i].ver <= __cplusplus && __cplusplus < cpp[i+1].ver) {
        cpp_ver = cpp[i].std;
        break;
      }
    }
    printf("MCU model   :%s R%d\n", ESP.getChipModel(), ESP.getChipRevision());
    printf("ESP-IDF ver :%d.%d.%d %s\n", ESP_IDF_VERSION_MAJOR, ESP_IDF_VERSION_MINOR, ESP_IDF_VERSION_PATCH, cpp_ver);
#endif

#if   0
    // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/chip-debug-report.cpp
    printAfterSetupInfo();
#endif

    // https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/misc_system_api.html
    static const char* reset_reason_all[] = {
      "reason can not be determined",
      "board power-on",
      "external (pin) reset",
      "software reboot (esp_reset())",
      "exception and/or kernel panic",
      "interrupt watchdog",
      "task watchdog",
      "other watchdog",
      "returning from a deep sleep",
      "brownout (software or hardware)",
      "reset over SDIO",
      "reset by USB peripheral",
      "reset by JTAG",
      "reset due to eFuse error",
      "power glitch detected",
      "CPU lock up (double exception)",
    };
    // https://github.com/espressif/esp-idf/blob/master/components/soc/esp32/include/soc/reset_reasons.h
    static const char* reset_reason_core[] = {
      "",
      "Power on reset",
      "",
      "Software resets the digital core",
      "",
      "Deep sleep resets the digital core",
      "SDIO module resets the digital core",
      "Main watch dog 0 resets digital core",
      "Main watch dog 1 resets digital core",
      "RTC watch dog resets digital core",
      "",
      "Main watch dog resets CPU",
      "Software resets CPU",
      "RTC watch dog resets CPU",
      "CPU0 resets CPU1 by DPORT_APPCPU_RESETTING",
      "Reset when the VDD voltage is not stable",
      "RTC watch dog resets digital core and RTC module",
    };
    // https://docs.espressif.com/projects/esp-idf/en/v5.5.1/esp32/api-reference/system/sleep_modes.html
    static const char* wakeup_cause[] = {
      "ESP_SLEEP_WAKEUP_UNDEFINED",
      "ESP_SLEEP_WAKEUP_ALL",
      "ESP_SLEEP_WAKEUP_EXT0",
      "ESP_SLEEP_WAKEUP_EXT1",
      "ESP_SLEEP_WAKEUP_TIMER",
      "ESP_SLEEP_WAKEUP_TOUCHPAD",
      "ESP_SLEEP_WAKEUP_ULP",
      "ESP_SLEEP_WAKEUP_GPIO",
      "ESP_SLEEP_WAKEUP_UART",
      "ESP_SLEEP_WAKEUP_WIFI",
      "ESP_SLEEP_WAKEUP_COCPU",
      "ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG",
      "ESP_SLEEP_WAKEUP_BT",
      "ESP_SLEEP_WAKEUP_VAD",
      "ESP_SLEEP_WAKEUP_VBAT_UNDER_VOLT",
    };

    uint32_t X = esp_reset_reason();            // overall
    uint32_t Y = esp_rom_get_reset_reason(0);   // core0
    uint32_t Z = esp_rom_get_reset_reason(1);   // core1
    uint32_t W = esp_sleep_get_wakeup_cause();  // overall
    if (X != 1 /* "board power-on" */) {
      printf("============ Reset Reason =============\n");
      printf("Reset reason (overall): %2d (%s)\n", X, reset_reason_all [X]);
      printf("Reset reason (core 0) : %2d (%s)\n", Y, reset_reason_core[Y]);
      printf("Reset reason (core 1) : %2d (%s)\n", Z, reset_reason_core[Z]);
      printf("Sleep wakeup cause    : %2d (%s)\n", W, wakeup_cause     [W]);
    }
  }
};

#endif // _ESP32_HPP_