# ESP32-CAM Internet Radio + Bluetooth Speaker

An ESP32-CAM AI-Thinker turned into a combined **internet radio** and
**Bluetooth A2DP speaker**, with a **PCM5102A I2S DAC**, a **KY-040 rotary
encoder**, and a **320x240 ST7789 display** wired through the camera FPC
connector.

Only one audio source is active at a time:

- **Radio mode** — streams MP3 stations over HTTP/HTTPS from an editable list
  and plays the first station automatically after boot.
- **Bluetooth mode** — acts as a classic Bluetooth A2DP sink named
  `ESP32-CAM Radio`; a phone pairs and streams audio to the same I2S DAC.

The encoder or the web UI switches between the two modes.

## Features

- MP3 streaming over `http://` and `https://` (TLS 1.2, built-in CA bundle,
  HTTP redirects followed)
- 44.1 kHz and 48 kHz streams; the I2S clock is reconfigured per stream
- Bluetooth classic A2DP sink + AVRCP (play/pause, absolute volume)
- Editable station list in `/spiffs/stations.txt`
- Web UI: play / stop / next / previous / volume / mode / BT play-pause
- Rotary encoder:
  - rotate = volume
  - short press = next station (radio) or play/pause (Bluetooth)
  - long press (~0.7 s) = toggle radio/Bluetooth
- ST7789 320x240 display: clock, weather, source/station, Russian date, IP
- Serial console (single-key commands on UART0)
- Multi-network WiFi: scans and joins the configured SSID with the best signal
- NTP clock with Israel local time (IST/IDT, automatic daylight saving)
- Current weather for a configurable location from Open-Meteo (no API key)
- Status LED: on = playing/connected, slow blink = discoverable/error,
  off = stopped
- 96 KB PCM ring buffer in PSRAM with pre-buffering to absorb network jitter
- PSRAM is used for the audio ring buffer and WiFi/LwIP allocations
- Flash and PSRAM both run at **80 MHz** (`CONFIG_ESPTOOLPY_FLASHFREQ_80M`,
  `CONFIG_SPIRAM_SPEED_80M`) for maximum performance
- **OTA updates** from the web UI (dual-bank layout, automatic rollback of a
  bad image)

## Hardware

Board: **ESP32-CAM AI-Thinker** (ESP32-D0WD, 4 MB flash, 8 MB PSRAM chip of
which 4 MB is mapped). Schematic: `ESP32-CAM-AI-Thinker-schematic-diagram.png`.

The camera is **not used**. The 24-pin camera FPC connector is repurposed
through a 24-pin-to-2.54 mm adapter for the LCD.

### Pin map

| Function | GPIO | Where |
|---|---|---|
| I2S BCK | 12 | left header |
| I2S WS / LRCK | 13 | left header |
| I2S DOUT / DIN | 4 | left header |
| Encoder A | 2 | left header |
| Encoder B | 15 | left header |
| Encoder SW | 14 | left header |
| LCD SCLK | 18 | camera FPC, pin 4 |
| LCD MOSI | 23 | camera FPC, pin 16 |
| LCD CS | 5 | camera FPC, pin 6 |
| LCD DC | 19 | camera FPC, pin 3 |
| LCD RST | 21 | camera FPC, pin 5 |
| LCD BL | 22 | camera FPC, pin 8 |
| Status LED (red, on-board) | 33 | on-board, active low |
| PSRAM CS | 16 | on-board, do not use |

Notes:

- GPIO16 is used by the on-board PSRAM. Do not connect anything to it.
- GPIO0 and EN are driven by the FTDI auto-reset circuit. Do not use them.
- GPIO12 and GPIO15 are boot strapping pins. They are used as I2S output
  (high-Z at boot) and encoder input (the KY-040 pull-ups hold them high,
  which is the required boot state).
- GPIO4 drove the white flash LED through transistor Q1 and resistor **R13**.
  R13 has been removed, so GPIO4 is free for I2S data and the flash LED stays
  off.
- The SD card slot is not used. Do not insert a card: its pins are shared with
  GPIO2/4/12/13/14/15.

### PCM5102A I2S DAC

| DAC signal | Connect to |
|---|---|
| BCK | GPIO12 |
| WS / LRCK | GPIO13 |
| DIN | GPIO4 |
| VIN | 3V3 or 5V (module has its own regulator) |
| GND | GND |
| SCK | GND (use the internal PLL) |
| FMT | GND (Philips I2S) |
| XSMT | 3V3 (unmuted) |
| FLT / DMP | GND |

The DAC is used in Philips I2S mode. The firmware configures it as a standard
16-bit stereo I2S master.

### KY-040 rotary encoder

| Encoder signal | Connect to |
|---|---|
| A / CLK | GPIO2 |
| B / DT | GPIO15 |
| SW | GPIO14 |
| + | 3V3 |
| GND | GND |

The KY-040 board provides the pull-ups for A, B and SW. A/B are decoded with a
full quadrature state machine in a GPIO interrupt, so fast turns are not
missed. If the direction feels reversed, flip `ENC_DIR` in `main/encoder.c`.

The switch is debounced in two stages: the interrupt drops edges within 30 ms
of the previous one, and the task classifies the press on release as short
(< 0.7 s) or long (>= 0.7 s).

### ST7789 320x240 display via the camera FPC adapter

The LCD signals are wired to the camera connector pins that carry the former
camera data/clock nets:

| Cam1 FPC pin | Camera net | GPIO | LCD signal |
|---|---|---|---|
| 3 | Y4 / CSI_D2 | 19 | DC |
| 4 | Y3 / CSI_D1 | 18 | SCLK |
| 5 | Y5 / CSI_D3 | 21 | RST |
| 6 | Y2 / CSI_D0 | 5 | CS |
| 8 | PCLK / CSI_PCLK | 22 | BL |
| 16 | HREF / CSI_HSYNC | 23 | MOSI |
| 10 | DGND | GND | GND |

**LCD VCC must come from the board's 3V3 header pin**, not from the camera
connector: `DOVDD`/`AVDD` there are 2.8 V and `DVDD` is 1.2 V. Use the board
3V3 and GND pins for the LCD supply and ground.

The panel is driven over SPI2 at 26 MHz through the ESP-IDF `esp_lcd` ST7789
driver. The backlight is on a 5 kHz PWM channel (`LEDC` timer 1 / channel 1;
the status LED uses timer 0 / channel 0).

Panel tuning lives in `main/board.h`:

| Define | Meaning |
|---|---|
| `BOARD_LCD_SWAP_XY` | landscape/portrait (1 = landscape) |
| `BOARD_LCD_MIRROR_X` / `_Y` | flip the image if it is mirrored |
| `BOARD_LCD_INVERT` | 1 for IPS panels that show a negative image |
| `BOARD_LCD_BGR` | 1 if red and blue are swapped |
| `BOARD_LCD_X_OFFSET` / `_Y_OFFSET` | shift the visible window |
| `BOARD_LCD_SELFTEST` | R/G/B flash at boot to check wiring |

The strip buffer holds little-endian RGB565 words, so the panel is configured
with `data_endian = LCD_RGB_DATA_ENDIAN_LITTLE` and `BOARD_LCD_BGR = 0`.

### Status LED

The on-board red LED on GPIO33 is active low. Patterns:

- on = radio playing / Bluetooth connected or playing
- slow blink = Bluetooth discoverable, or radio error
- off = stopped / Bluetooth off

### Power (important)

The ESP32-CAM needs a **stable 5 V supply of at least 1 A**. WiFi and Bluetooth
RF calibration draw short current peaks that a small FTDI 5 V pin cannot
sustain; with a weak supply the board browns out and reboots during boot or
while streaming. A marginal rail can also show up as short audio dropouts
while the radio plays, or as a boot loop at the RF-calibration step (the
calibration data write is corrupted, so every boot tries a full recalibration
and the interrupt watchdog resets it). If the serial log shows
`TG0WDT_SYS_RESET` / `TG1WDT_SYS_RESET` right after `phy_init: phy_version`,
check the supply before suspecting the firmware.

The current `sdkconfig.defaults` has the brownout detector **temporarily
disabled** so the board can be tested on the FTDI supply:

```
# CONFIG_ESP_BROWNOUT_DET is not set
```

Once the board is powered from a proper 5 V supply (separate supply or a
powered hub, thick short wires, a large electrolytic capacitor near the 5 V
pins), remove that line and rebuild to re-enable the detector.

## Display UI

The screen is laid out for 320x240 landscape:

```
                 10:47
          19°C Перем. облач.
        1: Radio Paradise
      playing 128 kbps 44100 Hz
         Сб 14 ноя 2026
           IP 192.168.1.50
```

In Bluetooth mode the source line becomes `Bluetooth` or `BT: <phone name>`,
and the detail line shows `discoverable`, `connected, paused` or
`playing 44.1 kHz`.

- The clock is drawn at 4x in green, without seconds.
- Weather is drawn at 2x (Open-Meteo, WMO codes mapped to short Russian labels).
- The source line is 2x when the whole label fits in 19 characters, 1x
  otherwise.
- The date (Russian weekday and month) is green and drawn at 2x.
- The UI uses the 8x16 Cyrillic font in `main/font8x16_ru.c`. Text is stored as
  UTF-8 and decoded per character; the font table maps ASCII, Cyrillic А–я and
  the degree sign.
- The source colour follows the state: green = playing/connected, amber =
  connecting/discoverable, red = error, grey = stopped.
- The UI is redrawn only when something changes, so idle CPU use is low.
- Volume 0 turns the backlight off and mutes the audio; volume 1 keeps the
  monitor on but stays silent; sound starts at volume 2.

Rendering uses a single 320x4 RGB565 strip buffer (2.5 KB) reused for every
band of the screen. Each strip is sent with SPI DMA and the task waits for the
transfer-complete callback before reusing the buffer.

## Bluetooth

The classic BT stack is started on the **first** switch to Bluetooth mode.
When the radio is selected, Bluedroid and the A2DP/AVRCP profiles are released,
which returns most of the internal RAM that the HTTPS client needs for its TLS
handshake. The controller itself is brought up once and never torn down: a
full controller deinit/init cycle (and even a disable/enable cycle) succeeds
at the HCI level but leaves the baseband unable to run inquiry scans again, so
the device stops being discoverable on the second switch to Bluetooth. Leaving
the controller enabled costs about 1 KB of internal RAM. Selecting Bluetooth
mode:

1. stops the radio stream and flushes the PCM buffer,
2. starts the BT controller, Bluedroid, A2DP and AVRCP (takes about a second),
3. makes the device discoverable as `ESP32-CAM Radio`,
4. accepts SSP "just works" pairing (legacy PIN `1234` as fallback).

A phone connects as an A2DP source. The sink receives 44.1 kHz stereo 16-bit
PCM and pushes it into the same I2S ring buffer as the radio. AVRCP is enabled
in both directions:

- the encoder/console/web can send play/pause to the phone,
- the phone's absolute volume control changes the local volume.

Switching back to radio disconnects A2DP, releases Bluedroid and the profiles
(returning most of their RAM to the heap) and restarts the last station.

## Web UI

Open `http://<device-ip>/` (the IP is printed on the serial console at boot).

| Path | Method | Purpose |
|---|---|---|
| `/` | GET | Player page: now playing, play/stop/next/prev, volume, mode, station list |
| `/edit` | GET | Edit the station list |
| `/save` | POST | Save the station list (`text=` form field) |
| `/api/status` | GET | JSON: radio state, mode, BT state, volume, WiFi, IP, RSSI, time |
| `/api/cmd` | GET | Commands (see below) |
| `/update` | GET | Firmware update page (version, slots, upload form) |
| `/update` | POST | Upload a `.bin`; body is the raw image (see **Firmware update**) |

Commands for `/api/cmd`:

| Query | Action |
|---|---|
| `c=play&i=N` | switch to radio mode and play station N (0-based) |
| `c=stop` | stop the radio |
| `c=next` / `c=prev` | next / previous station (switches to radio) |
| `c=vol&v=N` | set volume 0–100 |
| `c=mode` | toggle radio/Bluetooth |
| `c=mode_radio` / `c=mode_bt` | select a mode explicitly |
| `c=btplay` | send AVRCP play/pause to the phone |

Example:

```bash
curl http://192.168.1.50/api/status
curl "http://192.168.1.50/api/cmd?c=mode"
```

## Serial console

Send single characters on UART0 (115200 8N1):

| Key | Action |
|---|---|
| `p` | play station 1 |
| `n` | next station |
| `b` | previous station |
| `s` | stop |
| `+` / `-` | volume up / down (±10) |
| `l` | list stations |
| `w` | WiFi status |
| `t` | time and date (Israel) |
| `m` | free heap |
| `i` | mode and Bluetooth status |
| `M` | toggle radio/Bluetooth |
| `B` | Bluetooth play/pause |
| `h` / `?` | help |

## Building and flashing

Requires **ESP-IDF 5.5**.

```bash
. "$IDF_PATH/export.sh"
idf.py build
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB0 monitor
```

If `idf.py monitor` cannot open a TTY in your environment, any serial terminal
at **115200 8N1** works.

The MP3 decoder is the managed component `chmorgan/esp-libhelix-mp3` (helix),
fetched automatically by the component manager.

### Flashing with an FTDI FT232RL

The board is flashed through the right-side UART header with an FTDI adapter
and an auto-reset circuit on **IO0** and **EN** (DTR/RTS). Port:
`/dev/ttyUSB0`. The FTDI must be set to **3.3 V I/O** (or at least the ESP32
side must not see 5 V on RX/TX).

## Firmware update (OTA)

The 4 MB flash is split into two 1.75 MB application slots plus a 448 KB
SPIFFS partition, so the device can update itself over WiFi:

```
nvs        0x009000   16 KB
otadata    0x00d000    8 KB
phy_init   0x00f000    4 KB
ota_0      0x010000  1.75 MB
ota_1      0x1d0000  1.75 MB
storage    0x390000   448 KB
```

The running image is about 1.5 MB, leaving ~16 % headroom in each slot.

### From the browser

1. Build: `idf.py build`
2. Open `http://<device-ip>/update`
3. Choose `build/esp32_cam_radio.bin` and press **Upload and reboot**

The page shows the running version, the slot it booted from and the slot that
will be written. The image is streamed straight into flash (4 KB chunks), so
no large RAM buffer is needed. The radio is stopped before the write starts.

### From the command line

```bash
curl --data-binary @build/esp32_cam_radio.bin http://192.168.1.50/update
```

The response is `OK`; the device reboots about a second later.

### Rollback

`CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE=y` puts every uploaded image on
probation. The new firmware marks itself valid in `main.c` once WiFi, the web
UI and the display are up. If it crashes before that, the bootloader boots the
previous slot again on the next reset.

The app version comes from `CONFIG_APP_PROJECT_VER` in `sdkconfig.defaults`.
Bump it for each release:

```
CONFIG_APP_PROJECT_VER="1.0.1"
```

The version is printed on the serial console at boot, shown on the `/update`
page and linked from the main page.

### Notes

- `idf.py flash` still works over USB and writes `ota_0`; the first OTA update
  then goes to `ota_1`.
- The station list and WiFi credentials live in SPIFFS and survive updates.
- Changing `partitions.csv` changes the SPIFFS offset. Back up
  `/spiffs/wifi.txt` and `/spiffs/stations.txt` before re-partitioning, or the
  device will come up with the default (placeholder) credentials.
- The upload is unauthenticated. Anyone on the same network can flash the
  device, so keep it on a trusted LAN.
- `CONFIG_ESP_TASK_WDT_TIMEOUT_S=10` and `CONFIG_ESP_INT_WDT_TIMEOUT_MS=10000`:
  a full RF calibration on the first boot after a reset can take several
  seconds, and it runs with interrupts disabled. The 5 s task-watchdog default
  would reset the chip mid-calibration (rolling back a fresh OTA image), and
  the 800 ms interrupt-watchdog default would reset it even earlier. If the
  calibration data in NVS fails its checksum the chip recalibrates on every
  boot; with the short interrupt-watchdog limit it could never finish and save
  the result, which turned a bad checksum into a permanent boot loop.

## Configuration files

All files live on the SPIFFS `storage` partition. `stations.txt` and
`wifi.txt` are created with defaults on first boot; `weather.txt` is optional.

### `/spiffs/stations.txt`

One station per line:

```
# comment
Name|http://stream.example.com/live.mp3
Name2|https://stream.example.com/live.mp3
```

- Blank lines and lines starting with `#` are ignored.
- A line without `|` is treated as a URL; the host name becomes the name.
- Up to 40 stations, names up to 47 chars, URLs up to 199 chars.
- The whole file is limited to 8 KB.

Default stations: Radio Paradise, FIP (plus FIP Jazz and FIP Rock), France
Inter, Dorozhnoe Radio, Evropa Plus, Retro FM, Vesti FM.

### `/spiffs/wifi.txt`

One block per network:

```
# v2
ssid=YOUR_SSID
pass=YOUR_PASSWORD

ssid=AnotherNetwork
pass=AnotherPassword
```

At boot the device scans and joins the configured network with the strongest
signal. If a network fails repeatedly it is skipped for a while and the
next-best is tried.

### `/spiffs/weather.txt` (optional)

Weather location for Open-Meteo, one line:

```
City name|latitude|longitude
```

Example:

```
London|51.5074|-0.1278
```

If the file is missing, the built-in default (`London|51.5074|-0.1278`) is
used. The city name is only shown on the display and in the log; the request
uses the coordinates.

## Time and date (NTP)

The device synchronises its clock over SNTP once WiFi is up. Servers, in order:
`pool.ntp.org`, `time.google.com`, `il.pool.ntp.org`.

Timezone: **Asia/Jerusalem** (`IST-2IDT,M3.4.4/2,M10.5.0/2`), so DST switches
automatically. Until the first NTP reply the display shows `--:--` and the
status reports `not synced`.

## Audio path

```
HTTP(S) ──> MP3 decoder (helix) ──PCM──┐
                                       ├──> 96 KB ring (PSRAM) ──> volume ──> I2S ──> PCM5102A
Bluetooth A2DP sink ──────PCM──────────┘
```

- The writer task is pinned to core 1; core 0 handles WiFi and the network
  stack.
- Playback starts only after 48 KB of PCM is buffered (or ~2 s).
- The I2S sample rate follows the source (44.1 kHz or 48 kHz).
- The ring buffer is allocated in PSRAM; the I2S driver copies each chunk into
  its own internal DMA buffers.

## Memory notes

- 96 KB PCM ring buffer in PSRAM (≈500 ms at 48 kHz)
- 16 KB mbedTLS input buffer (needed for servers that send 16 KB TLS records)
- `CONFIG_LWIP_MAX_SOCKETS=8` so the web UI keeps working while a stream is open
- `CONFIG_HTTPD_MAX_REQ_HDR_LEN=3072` (the 512-byte default rejects browser
  POSTs)
- Display: one 2.5 KB strip buffer, synchronous DMA transfers, no frame buffer
- Web UI: the `/edit` handler streams the station file in 128-byte chunks and
  `/save` decodes the form body in place. The httpd task stack is 5 KB because
  the status JSON and the page buffer are built on the stack.
- Bluetooth classic + Bluedroid + A2DP cost roughly 60–90 KB of internal RAM.
  Bluedroid and the profiles are created on the first switch to Bluetooth mode
  and deleted when the radio is selected again, so radio-only operation keeps
  the internal heap for TLS. Only the controller's ~1 KB stays allocated.
- mbedTLS uses the default allocator (`CONFIG_MBEDTLS_DEFAULT_MEM_ALLOC`):
  large TLS buffers land in PSRAM, small ones in internal RAM. With the
  internal-only allocator the 16 KB input buffer did not fit next to WiFi.
- The radio uses `esp_http_client_open()` + `read()` for streaming, and that
  path does not follow redirects by itself, so `radio.c` follows 3xx
  `Location` headers (up to 5 hops). Some stations (e.g. SRG SSR) need it.
- OTA: the upload is received into PSRAM first and only then programmed into
  flash. Programming flash disables the cache for a few milliseconds per 8 KB
  chunk, which starves the WiFi task; with the 5.7 KB TCP window that closes
  the window mid-upload and the sender backs off, stalling the transfer at a
  random offset. Keeping the two phases apart makes the update take a steady
  ~9 s instead of failing about half the time. The image is ~1.5 MB of the
  1.75 MB slot, so the PSRAM buffer is 1.5 MB of the 4 MB available.

## Project layout

```
main/
  main.c        init order, WiFi wait, BT init, autoplay station 0
  board.h       pin map, LCD geometry and camera-adapter mapping
  app_mode.c    radio/Bluetooth mode switch
  bt_audio.c    classic BT controller, A2DP sink, AVRCP, SSP
  audio_out.c   I2S TX, 96 KB PSRAM ring, writer task, volume, beep
  radio.c       HTTP(S) streaming, helix MP3 decode, station switching
  stations.c    station list parse/save, built-in defaults
  wifi.c        multi-network scan, best-signal connect, reconnect
  clock.c       SNTP sync and Israel local time
  encoder.c     KY-040 quadrature decode, volume, short/long press
  weather.c     Open-Meteo fetch over a raw socket (static buffers)
  display.c     ST7789 init, strip renderer and UI refresh task
  webui.c       HTTP server, web pages and OTA upload
  console.c     UART0 command console
  storage.c     SPIFFS mount and file helpers
  status_led.c  on-board LED patterns
  font8x16_ru.c 8x16 Cyrillic font table
  font8x16_ru.h font metrics and glyph layout
tools/
  gen_font.py   font generator helper
```

## Known limitations

- MP3 only for radio (no AAC/OGG/Opus). Bluetooth uses SBC.
- HTTPS validates against the built-in CA bundle; self-signed certificates are
  rejected.
- Volume is not persisted across reboots (always starts at 20).
- Time is only available after the first NTP reply (needs internet access).
- Only one source at a time: Bluetooth mode stops the radio and vice versa.
- OTA upload is unauthenticated and only available over plain HTTP on the
  local network.
- The brownout detector is disabled until the 5 V supply is improved (see
  **Power** above).
