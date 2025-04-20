#pragma once

#include <LovyanGFX.hpp>

// ESP32-2432S028R で LovyanGFX を独自設定で利用する場合の設定
// ファイル名例：LGFX_ESP32_2432S028R_CYD_1USB.hpp
//
// ピン設定は、以下を元にしています
// ボードタイプ：ESP32_2432S028R CYD
// https://github.com/espressif/arduino-esp32/blob/master/variants/jczn_2432s028r/pins_arduino.h

/// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9341   _panel_instance;  // 接続するパネルの型にあったインスタンスを用意します。
  lgfx::Bus_SPI         _bus_instance;    // SPIバスのインスタンス
  lgfx::Light_PWM       _light_instance;  // バックライト制御が可能な場合はインスタンスを用意します。
  lgfx::Touch_XPT2046   _touch_instance;  // タッチスクリーンの型にあったインスタンスを用意します。

public:
  // コンストラクタを作成し、ここで各種設定を行います。
  LGFX(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();  // バス設定用の構造体を取得します。

      cfg.spi_host = HSPI_HOST;           // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      cfg.spi_mode = 0;                   // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;          // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;          // 受信時のSPIクロック
      cfg.spi_3wire  = false;             // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock   = true;              // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = SPI_DMA_CH_AUTO;  // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
      cfg.pin_sclk = CYD_TFT_SCK;         // SPIのSCLKピン番号を設定 (14)
      cfg.pin_mosi = CYD_TFT_MOSI;        // SPIのMOSIピン番号を設定 (13)
      cfg.pin_miso = CYD_TFT_MISO;        // SPIのMISOピン番号を設定 (12)
      cfg.pin_dc   = CYD_TFT_DC;          // SPIのD/Cピン番号を設定  (2)

      _bus_instance.config(cfg);          // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance); // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();  // 表示パネル設定用の構造体を取得します。

      cfg.pin_cs           = CYD_TFT_CS;    // CSが接続されているピン番号   (15)
      cfg.pin_rst          = -1;            // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy         = -1;            // BUSYが接続されているピン番号 (-1 = disable)

      cfg.panel_width      =   240;  // 実際に表示可能な幅
      cfg.panel_height     =   320;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     2;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       = false;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   320;  // ドライバICがサポートしている最大の高さ

      _panel_instance.config(cfg);
    }

    { // バックライト制御の設定を行います。
      auto cfg = _light_instance.config();  // バックライト設定用の構造体を取得します。

      cfg.pin_bl = CYD_TFT_BL;      // バックライトが接続されているピン番号 (21)
      cfg.invert = false;           // バックライトの輝度を反転させる場合 true
      cfg.freq   = 12000;           // バックライトのPWM周波数
      cfg.pwm_channel = 7;          // 使用するPWMのチャンネル番号

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);  // バックライトをパネルにセットします。
    }

    { // タッチスクリーン制御の設定を行います。
      auto cfg = _touch_instance.config();

      cfg.x_min      =  240;        // タッチスクリーンから得られる最小のX値(生の値)
      cfg.x_max      = 3800;        // タッチスクリーンから得られる最大のX値(生の値)
      cfg.y_min      = 3700;        // タッチスクリーンから得られる最小のY値(生の値)
      cfg.y_max      =  200;        // タッチスクリーンから得られる最大のY値(生の値)
      cfg.pin_int    = CYD_TP_IRQ;  // INTが接続されているピン番号 (36)
      cfg.bus_shared = false;       // 画面と共通のバスを使用している場合 trueを設定
      cfg.offset_rotation = 0;      // 表示とタッチの向きのが一致しない場合の調整 0~7の値で設定

      cfg.spi_host = -1;            // 使用するSPIを選択 (HSPI_HOST or VSPI_HOST)
      cfg.freq = 1000000;           // SPIクロックを設定
      cfg.pin_sclk = CYD_TP_CLK;    // SCLKが接続されているピン番号 (25)
      cfg.pin_mosi = CYD_TP_MOSI;   // MOSIが接続されているピン番号 (32)
      cfg.pin_miso = CYD_TP_MISO;   // MISOが接続されているピン番号 (39)
      cfg.pin_cs   = CYD_TP_CS;     //   CSが接続されているピン番号 (33)

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);  // タッチスクリーンをパネルにセットします。
    }

    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};