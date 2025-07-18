#include "Esp.h"
#include "chip-debug-report.h"
#include "freertos_stats.h"

void PrintESP32Memory(void) {
  /*
    https://en.cppreference.com/w/cpp/compiler_support
    https://forum.arduino.cc/t/which-version-of-c-is-currently-supported/1285868/13
    https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32/api-guides/cplusplus.html
    https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#:~:text=__cplusplus,gnu%2B%2B26.
    199711 ➜ C++98 or C++03 standards.
    201103 ➜ C++11 standard.
    201402 ➜ C++14 standard.
    201703 ➜ C++17 standard.
    202002 ➜ C++20 standard.
    202302 ➜ C++23 standard.
  */
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

  // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/chip-debug-report.cpp
//printAfterSetupInfo();

  // https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/freertos_stats.h
  // https://forum.arduino.cc/t/how-to-make-tasks-and-determine-stack-size-in-freertos/978325/29
  // uxTaskGetStackHighWaterMark()
//printRunningTasks(Serial);

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

  uint32_t X = esp_reset_reason();          // overall
  uint32_t Y = esp_rom_get_reset_reason(0); // core0
  uint32_t Z = esp_rom_get_reset_reason(1); // core1
  printf("============ Reset Reason =============\n");
  printf("Reset reason (overall): %2d (%s)\n", X, reset_reason_all [X]);
  printf("Reset reason (core 0) : %2d (%s)\n", Y, reset_reason_core[Y]);
  printf("Reset reason (core 1) : %2d (%s)\n", Z, reset_reason_core[Z]);

  printf("============ Memory Usage =============\n");
  printf("Sketch space:%7d\n", ESP.getFreeSketchSpace());
  printf("Sketch size :%7d\n", ESP.getSketchSize());
  printf("Heap total  :%7d\n", ESP.getHeapSize());
  printf("Heap free   :%7d\n", esp_get_free_internal_heap_size());
  printf("Heap remain :%7d\n", ESP.getMinFreeHeap());
  printf("Heap lowest :%7d\n", esp_get_minimum_free_heap_size());

  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/heap_debug.html
  // https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/mem_alloc.html
  if (psramInit()) {
    printf("PSRAM total :%7d\n", ESP.getPsramSize());
    printf("PSRAM lowest:%7d\n", ESP.getMinFreePsram());
  }
  printf("Min MALLOC_CAP_INTERNAL:%7d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL));
  printf("Min MALLOC_CAP_DMA     :%7d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DMA));
  printf("Max MALLOC_CAP_INTERNAL:%7d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
  printf("Max MALLOC_CAP_DMA     :%7d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DMA));
}