| Repository Status | ESPHome Community |
| :--- | :--- |
| [![last commit time][github-last-commit]][github-master] [![GitHub Activity][commits-shield]][commits] | [![Discord][discord-shield]][discord] [![Home Assistant Forum][forum-shield]][forum]  | 

# My ESPHome Devices
Configuration files for my ESP8266 / ESP32 plugs and boards for use with Home Assistant.

## Devices

### bluetooth_hub.yaml
I started with the [ESP32 Bluetooth Low Energy Tracker Hub][esphome-ble-hub] example on esphome.io, and added Xiaomi temperature plant sensors.

### dog_water.yaml
A **FAILED** attempt at making a dog water bowl sensor with an ESP8266 board. By inserting two insulated wires (cut at the end) into the bowl I hoped it would become a "switch" that would turn on and off when submerged in the water or dry. It did not work, someday I will try to find a more reliable way to sense water.

### Standard plugs: plug01.yaml - plug03.yaml
#### ZooZee brand Tuya plugs
These are simple round wall plug were flashed with over the air with tasmota-convert, then ESPHome was uploaded via the Tasmota UI. The ESPHome code attempts to recreate their original functionality.

### Hot Water Pump: plug05.yaml
This plug controls the whole house hot water recirculation pump. When we turn this on we don't want it to keep running forever. So I set a timeout that turns the pump off after 10 minutes. This timeout is a backup to the Home Assistant automation that automatically turns it off after 5 minutes.

### Standard plugs: plug06.yaml - plug08.yaml
#### Luntak brand Tuya plugs
These are simple round wall plugs were flashed with over the air with tasmota-convert, then ESPHome was uploaded via the Tasmota UI. The ESPHome code attempts to recreate their original functionality.

### Shelly1's
These devices are great for shoving in a box behind a light switch to add smarts.

#### Dining Room Wall Switch: shelly1_01.yaml
I coded this to be create a smart switch that is compatible with a chandelier with 9 hue bulbs. It's relay is disabled, unless Home Assistant is unavailable. This allows it to operate as a virtual 3-way switch with Home Assistant, as well as failing gracefully should Home Assistant be offline to act as a dumb toggle switch.

#### Upstairs Bathroom Fan: shelly1_02.yaml
This allows users to manually turn on or off the fan. If they turn it on while the humidity is below 50% then it will turn off after 15 minutes. If the humidity is above 50% when the manual switch is turned on, it will start a 60 minute timer which will absolutely turn the fan off at that time.

The ESPHome code gets the humidity from Home Assistant and handles all automations internally. When the humidity goes above 55% it automatically turns on, until the humidity falls below 50%.

The switch will also fail gracefully when Home Assistant is not available to act as a dumb toggle switch.

### Standard plugs: sonoff_basic_01.yaml, sonoff_basic_02.yaml
These are Sonoff Basics, with plugs on either side. One is used to switch on a floor fan, and the other is being reserved possibly to control a bathroom vent fan.

### Power monitoring ONLY plugs: sonoff_s31_01.yaml, sonoff_s31_02.yaml
These are Sonoff S31 plugs are set to power on a boot, their physical "power" push buttons are disabled, and the virtual button hidden from Home Assistant. They are being used to monitor the power usage of a clothes washing machine and my wife's Glowforge laser cutter. With this data, I can create automations to alert us when the wash cycle or the laser cycle is complete.

### Power monitoring plugs: sonoff_pow_01.yaml, sonoff_pow_02.yaml, sonoff_s31_03.yaml - sonoff_s31_06.yaml
These are Sonoff POWs and Sonoff S31s. The code attempts to recreate their functionality.


## Questions?
Ask on the [ESPHome #general channel on Discord][discord]. Use `#BrianHanifin` to tag me.



[commits-shield]: https://img.shields.io/github/commit-activity/m/brianhanifin/esphome-config.svg
[commits]: https://github.com/brianhanifin/esphome-config/commits/master
[github-last-commit]: https://img.shields.io/github/last-commit/BrianHanifin/esphome-config.svg?style=plasticr
[github-master]: https://github.com/BrianHanifin/esphome-config/commits/master

[discord-shield]: https://img.shields.io/discord/429907082951524364.svg
[discord]: https://discord.gg/A7SaaSC

[forum-shield]: https://img.shields.io/badge/home_assistant-forum-brightgreen.svg
[forum]: https://community.home-assistant.io/u/brianhanifin/summary


[esphome-ble-hub]:https://esphome.io/components/esp32_ble_tracker.html
[esphome-sonoff-basic]:https://esphome.io/devices/sonoff_basic.html
