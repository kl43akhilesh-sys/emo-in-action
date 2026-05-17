# 🤖 EMO-ON-ACTION: Futuristic AI Companion

**A cybernetic personality interface combining advanced OLED expression rendering, AI voice interaction, real-time weather integration, and smart alarm systems on an ESP32-WROOM platform.**

## 🎯 Project Overview

EMO-ON-ACTION is a sophisticated companion device that brings artificial emotion and intelligence to a compact 1.3" OLED display through minimalist pixel-art animation, voice interaction, and environmental awareness.

### Key Features

✨ **12+ Emotional Expressions**
- Neutral/Idle, Happy, Excited, Sad, Tired, Sleep, Surprised, Scared, Nervous, Confused, Wink, Love, Laughing, Angry, Frustrated, Proud, Goodbye, Listening, Speaking, Processing, Updating, Charging, Low Battery, Error, Curious, Thinking, Focused, Serious

🎨 **Advanced OLED Animation Engine**
- Smooth 30 FPS pixel animation with easing curves
- Dynamic pupil tracking and micro-expressions
- Context-aware blinking with overshoot/rebound
- Glow intensity based on processing load
- Sub-pixel mouth animation synced to audio

🗣️ **AI Voice Interaction**
- Whisper STT (speech-to-text) recognition
- Gemini LLM for intelligent responses
- ElevenLabs TTS with voice variety
- Real-time emotion detection from sentiment
- Phoneme-synced mouth animation

🌤️ **Weather Intelligence**
- 4-day forecast with animated icons
- Temperature/humidity/wind tracking
- Dynamic animation response to weather
- Chart visualization on OLED

⏰ **Smart Alarm System**
- 3 independent alarm configurations
- Realistic alarm sounds through Bluetooth speaker
- Emotional wake-up messages
- Snooze + dismiss controls

🔋 **Dual Display System**
- OLED (1.3", 128×64): Emotional face + weather + notifications
- LCD (16×2): Time, date, connectivity status

🎮 **Intuitive Control**
- Touch sensor interactions (tap, double-tap, long-press)
- 3 physical buttons (MODE, +, −)
- WebSocket-based remote control
- Dashboard app for full system management

💾 **SD Card Storage (8GB)**
- Animation frame caching
- Response cache for faster interactions
- System logs and diagnostics
- User preferences backup

## 🔧 Hardware Specifications

### Main MCU
- **ESP32-WROOM-32** Development Board
- 240 MHz dual-core processor
- 4MB Flash, 520KB SRAM
- Built-in WiFi 802.11 b/g/n
- Bluetooth 4.2 (Classic + BLE)

### Displays
- **OLED SSD1306** (1.3", I2C)
  - 128×64 pixel resolution
  - High contrast deep blacks
  - I2C Address: 0x3C (GPIO 21-SDA, GPIO 22-SCL)

- **LCD HD44780** (16×2, 4-bit parallel via Shield)
  - RS → GPIO 25
  - EN → GPIO 26
  - D4 → GPIO 27, D5 → GPIO 14
  - D6 → GPIO 12, D7 → GPIO 13

### Input/Output
- **TTP223 Touch Sensor** (OLED interactions) → GPIO 4
- **3× Pushbuttons**
  - MODE → GPIO 5
  - Plus (+) → GPIO 32
  - Minus (−) → GPIO 33
- **Microphone ADC** → GPIO 35 (16-bit, 16kHz)
- **Bluetooth A2DP Speaker** (DAC managed by BT chipset)

### Storage & Communication
- **SD Card (SPI, 8GB)**
  - CS → GPIO 15
  - MOSI → GPIO 23, MISO → GPIO 19
  - CLK → GPIO 18
- **WiFi + Bluetooth** (ESP32 internal)

## 📋 GPIO Pinout Summary

| GPIO | Function | Connected To |
|------|----------|---------------|
| 1 | TX (Debug) | Serial |
| 3 | RX (Debug) | Serial |
| 4 | Touch T0 | TTP223 SIS |
| 5 | MODE Button | Pushbutton |
| 12 | LCD D6 | LCD Shield |
| 13 | LCD D7 | LCD Shield |
| 14 | LCD D5 | LCD Shield |
| 15 | SD CS | SD Module |
| 18 | SD CLK | SD Module |
| 19 | SD MISO | SD Module |
| 21 | I2C SDA | OLED + TTP |
| 22 | I2C SCL | OLED + TTP |
| 23 | SD MOSI | SD Module |
| 25 | LCD RS | LCD Shield |
| 26 | LCD EN | LCD Shield |
| 27 | LCD D4 | LCD Shield |
| 32 | Plus Button | Pushbutton |
| 33 | Minus Button | Pushbutton |
| 35 | Microphone ADC | Analog In |

## 🎮 User Interactions

### OLED Touch Sensor (TTP223)

| Action | Duration | Result |
|--------|----------|--------|
| Single Tap | <200ms | HAPPY 😊 (blue eyes glow, smile, sparkles) |
| Double Tap | <400ms | ANGRY 😠 (red overlay, angry sound) |
| Long Press | 1.0s | WEATHER mode (4-day forecast) |
| Long Press | 2.0s | SETTINGS mode (voice chat toggle) |
| Long Press | 3.0s | REBOOT (spinning animation → restart) |

### Physical Buttons

| Button | Action | Function |
|--------|--------|----------|
| MODE | Single | Cycle modes: Voice → Weather → Settings → Face |
| + | Single | Increment alarm / Volume up |
| − | Single | Decrement alarm / Volume down |

### LCD Display

```
Line 1: HH:MM:SS AM/PM  📡 🔋
Line 2: [WiFi●] [BT●] [NTP●]
```

## 📂 Project Structure

```
emo-in-action/
├── firmware/          # ESP32 firmware
│   ├── main/src/     # Source code
│   │   ├── main.cpp
│   │   ├── utils/    # Configuration, WiFi, SD
│   │   ├── display/  # OLED & LCD drivers
│   │   ├── ui/       # Animation engine & companion logic
│   │   ├── buttons/  # Button & touch handling
│   │   ├── cloud/    # AI APIs (Whisper, Gemini, ElevenLabs)
│   │   ├── alarm/    # Alarm system
│   │   └── bluetooth/# BT speaker & voice chat
│   ├── assets/       # Animation frames, sounds
│   └── docs/         # Hardware guides
├── dashboard/        # PyQt6 desktop app
│   ├── app/ui/       # UI pages & widgets
│   ├── app/backend/  # WebSocket, device comm
│   ├── server/       # Flask backend
│   └── assets/       # Icons, images
├── docs/             # Full documentation
└── scripts/          # Helper scripts
```

## 🚀 Quick Start

### Firmware Setup

1. **Install PlatformIO**
   ```bash
   pip install platformio
   ```

2. **Clone and configure**
   ```bash
   git clone https://github.com/kl43akhilesh-sys/emo-in-action.git
   cd emo-in-action/firmware
   ```

3. **Set API keys** (firmware/main/include/api_keys.h)
   - OpenAI Whisper API key
   - Google Gemini API key
   - ElevenLabs API key

4. **Upload firmware**
   ```bash
   pio run -t upload
   ```

### Dashboard Setup

1. **Install dependencies**
   ```bash
   cd dashboard
   pip install -r requirements.txt
   ```

2. **Configure settings** (config.env)
   - Device IP address
   - WiFi SSID/Password
   - API endpoints

3. **Run dashboard**
   ```bash
   python main.py
   ```

## 📚 Documentation

- **COMPLETE_GUIDE.md** - Deep technical documentation
- **WIRING_DIAGRAM.md** - Detailed hardware connections
- **API_SETUP.md** - Cloud service configuration
- **BUTTON_FUNCTIONS.md** - Complete interaction guide
- **TROUBLESHOOTING.md** - Common issues & solutions

## 🎨 Emotional Expression System

The companion uses 24+ emotional states with smooth animations:

- **Idle/Neutral** - Calm breathing, minimal movement
- **Happy** - Lifted eyes, upturned smile, sparkles
- **Excited** - Enlarged eyes, open mouth, vibration
- **Sad** - Downturned eyes, frown, slow animation
- **Angry** - Slanted eyes, firm mouth, red overlay
- **Thinking** - One eye up, rotating iris, thought bubble
- **Listening** - Eyes focused, waveform mouth
- **Speaking** - Mouth synced to audio phonemes
- **Processing** - Rotating pupils, scan lines
- **Sleep** - Closed eyes, "Z" animations
- **Error** - Flicker, red/purple glitch overlay
- **And 13+ more...**

Each expression has:
- Smooth 30 FPS animation
- Context-aware timing
- Micro-expressions for realism
- Audio-synced feedback
- Glow/brightness dynamics

## 🌐 Cloud Integration

- **Whisper API** - Real-time speech recognition
- **Gemini LLM** - Intelligent conversation
- **ElevenLabs TTS** - Natural voice synthesis
- **OpenWeather API** - Real-time weather data

## 🔐 Privacy & Security

- Local SD card caching reduces API calls
- Optional offline mode for core functions
- Encrypted credential storage
- No user data uploaded without consent

## 📜 License

MIT License - Open source for personal & educational use

## 👨‍💻 Author

**Akhilesh Kumar** (kl43akhilesh-sys)
Created: 2026

## 🤝 Contributing

Contributions welcome! Please submit pull requests or issues.

---

**EMO-ON-ACTION: Where pixels become personality. 🤖✨**
