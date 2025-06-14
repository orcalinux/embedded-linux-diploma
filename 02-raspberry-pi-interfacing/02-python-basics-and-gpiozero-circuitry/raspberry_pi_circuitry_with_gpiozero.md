# Raspberry Pi Circuitry with gpiozero

This repository provides examples, activities, and best practices for controlling Raspberry Pi GPIOs using Python's [`gpiozero`](https://gpiozero.readthedocs.io/) library. Learn how to work with LEDs (including PWM control), push buttons, sensors, and more—all with a simple, intuitive API.

---

## Table of Contents

- [Raspberry Pi Circuitry with gpiozero](#raspberry-pi-circuitry-with-gpiozero)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation and Setup](#installation-and-setup)
  - [Controlling GPIOs with gpiozero](#controlling-gpios-with-gpiozero)
  - [GPIO Basics](#gpio-basics)
  - [Raspberry Pi Pinout \& Pin Modes](#raspberry-pi-pinout--pin-modes)
  - [LED Control Examples](#led-control-examples)
    - [LED Blinking Program](#led-blinking-program)
    - [Activity: Control LED via User Input](#activity-control-led-via-user-input)
    - [Activity: Toggle LED on Button Press](#activity-toggle-led-on-button-press)
    - [Multiple LED Pattern Example](#multiple-led-pattern-example)
  - [PWMLED Examples](#pwmled-examples)
    - [Simple Fade In/Fade Out](#simple-fade-infade-out)
    - [Interactive PWM Control via Button](#interactive-pwm-control-via-button)
  - [Integrating Input Devices](#integrating-input-devices)
    - [Basic Button Detection](#basic-button-detection)
    - [Using Event Handlers with Buttons](#using-event-handlers-with-buttons)
  - [Advanced Projects and Code Optimization](#advanced-projects-and-code-optimization)
    - [Controlling Multiple LEDs with Lists](#controlling-multiple-leds-with-lists)
    - [Using Sensors (Example: Light Sensor)](#using-sensors-example-light-sensor)
    - [Combining Multiple Inputs and Outputs](#combining-multiple-inputs-and-outputs)
  - [Additional Resources](#additional-resources)

---

## Introduction

This project is designed to help you explore Raspberry Pi GPIO programming using the `gpiozero` library. The examples range from simple LED blinking to more complex interactions with buttons, sensors, and multiple outputs—including PWM-based brightness control.

---

## Installation and Setup

Ensure your Raspberry Pi is updated and `gpiozero` is installed:

```bash
sudo apt update
sudo apt install python3-gpiozero
```

If needed, install additional libraries (for sensors, etc.) via pip:

```bash
pip3 install some_sensor_library
```

---

## Controlling GPIOs with gpiozero

The `gpiozero` library provides classes like `LED`, `PWMLED`, `Button`, and `LightSensor` to work with hardware components directly. Its event-driven model makes it easy to write responsive programs.

---

## GPIO Basics

- **Devices & Components**: Use classes such as `LED`, `PWMLED`, `Button`, `Buzzer`, and sensor classes.
- **Initialization**: Instantiate a component with its corresponding GPIO pin number.
- **Cleanup**: gpiozero handles cleanup automatically when your script terminates, though you can use `close()` on devices if needed.

---

## Raspberry Pi Pinout & Pin Modes

Below is an example table of the Raspberry Pi 40-pin header (using BOARD numbering) with common BCM assignments and functions. (Note: For complete details, refer to [pinout.xyz](https://pinout.xyz).)

| Board Pin | BCM GPIO | Function              |
| --------- | -------- | --------------------- |
| 1         | -        | 3.3V Power            |
| 2         | -        | 5V Power              |
| 3         | 2        | SDA1 (I2C)            |
| 4         | -        | 5V Power              |
| 5         | 3        | SCL1 (I2C)            |
| 6         | -        | GND                   |
| 7         | 4        | GPIO 4                |
| 8         | 14       | TXD                   |
| 9         | -        | GND                   |
| 10        | 15       | RXD                   |
| ...       | ...      | ...                   |
| 12        | 18       | GPIO 18 (PWM capable) |
| ...       | ...      | ...                   |
| 13        | 27       | GPIO 27               |
| ...       | ...      | ...                   |
| 15        | 22       | GPIO 22               |

**Pin Modes:**

| Mode    | Description                                                    |
| ------- | -------------------------------------------------------------- |
| `BCM`   | Refers to the Broadcom SOC channel numbers (e.g., GPIO 18).    |
| `BOARD` | Refers to the physical pin numbers on the Raspberry Pi header. |

Use the mode that best fits your project and reference the correct pin numbers accordingly.

---

## LED Control Examples

### LED Blinking Program

A simple example that blinks an LED on GPIO pin 18:

```python
from gpiozero import LED
from time import sleep

led = LED(18)

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
```

---

### Activity: Control LED via User Input

This program prompts the user to turn the LED on or off:

```python
from gpiozero import LED

led = LED(18)

try:
    while True:
        command = input("Enter 'on' to light the LED, 'off' to turn it off, or 'exit' to quit: ").strip().lower()
        if command == "on":
            led.on()
            print("LED is ON")
        elif command == "off":
            led.off()
            print("LED is OFF")
        elif command == "exit":
            break
        else:
            print("Invalid command. Try again.")
except KeyboardInterrupt:
    pass
```

---

### Activity: Toggle LED on Button Press

Toggle the LED state using a button connected to GPIO pin 23:

```python
from gpiozero import LED, Button
from time import sleep

led = LED(18)
button = Button(23)
led_state = False

while True:
    button.wait_for_press()  # Wait for a button press
    led_state = not led_state  # Toggle state
    if led_state:
        led.on()
    else:
        led.off()
    print("LED Toggled:", "ON" if led_state else "OFF")
    sleep(0.5)  # Debounce delay
```

---

### Multiple LED Pattern Example

Control multiple LEDs using a list for a simple chase sequence:

```python
from gpiozero import LED
from time import sleep

LED_PINS = [18, 17, 27]  # Update with your LED GPIO pins
leds = [LED(pin) for pin in LED_PINS]

try:
    while True:
        for led in leds:
            led.on()
            sleep(0.5)
            led.off()
        sleep(0.5)
except KeyboardInterrupt:
    pass
```

---

## PWMLED Examples

### Simple Fade In/Fade Out

Use the `PWMLED` class to smoothly control LED brightness with Pulse-Width Modulation:

```python
from gpiozero import PWMLED
from time import sleep

led = PWMLED(18)

try:
    while True:
        # Fade in
        for brightness in range(0, 101):
            led.value = brightness / 100
            sleep(0.02)
        # Fade out
        for brightness in range(100, -1, -1):
            led.value = brightness / 100
            sleep(0.02)
except KeyboardInterrupt:
    pass
```

---

### Interactive PWM Control via Button

Adjust the LED brightness based on button presses:

```python
from gpiozero import PWMLED, Button
from time import sleep

led = PWMLED(18)
button = Button(23)
brightness = 0.0

def increase_brightness():
    global brightness
    brightness = min(1.0, brightness + 0.1)
    led.value = brightness
    print(f"Brightness increased to {brightness:.1f}")

def decrease_brightness():
    global brightness
    brightness = max(0.0, brightness - 0.1)
    led.value = brightness
    print(f"Brightness decreased to {brightness:.1f}")

# Use button press to increase brightness and release to decrease it.
button.when_pressed = increase_brightness
button.when_released = decrease_brightness

try:
    while True:
        sleep(0.1)
except KeyboardInterrupt:
    pass
```

---

## Integrating Input Devices

### Basic Button Detection

Detect a button press using a simple polling loop:

```python
from gpiozero import Button
from time import sleep

button = Button(23)

while True:
    if button.is_pressed:
        print("Button Pressed!")
    sleep(0.1)
```

---

### Using Event Handlers with Buttons

Take advantage of gpiozero’s event-driven features:

```python
from gpiozero import Button
from signal import pause

button = Button(23)

def on_press():
    print("Button was pressed!")

def on_release():
    print("Button was released!")

button.when_pressed = on_press
button.when_released = on_release

pause()  # Keeps the script running
```

---

## Advanced Projects and Code Optimization

### Controlling Multiple LEDs with Lists

Organize your code for scalability by storing device instances in lists:

```python
from gpiozero import LED
from time import sleep

led_pins = [18, 17, 27, 22]
leds = [LED(pin) for pin in led_pins]

# Turn all LEDs on, then off
for led in leds:
    led.on()
sleep(1)
for led in leds:
    led.off()
sleep(1)
```

---

### Using Sensors (Example: Light Sensor)

Integrate a sensor to react to ambient light. For instance, using a Light Sensor:

```python
from gpiozero import LightSensor
from time import sleep

# Assuming the sensor is connected to an appropriate interface (or ADC)
sensor = LightSensor(4)  # Adjust pin or interface as needed

while True:
    print("Light Level:", sensor.value)
    sleep(0.5)
```

---

### Combining Multiple Inputs and Outputs

Create interactive projects that combine buttons, LEDs, and sensors. For example, adjust LED brightness based on ambient light while toggling via a button:

```python
from gpiozero import PWMLED, Button, LightSensor
from time import sleep

led = PWMLED(18)
button = Button(23)
sensor = LightSensor(4)

def adjust_led():
    # Adjust LED brightness based on ambient light (inverse relation)
    led.value = 1 - sensor.value
    print(f"LED brightness set to {led.value:.2f}")

button.when_pressed = adjust_led

try:
    while True:
        sleep(0.1)
except KeyboardInterrupt:
    pass
```

---

## Additional Resources

- [gpiozero Documentation](https://gpiozero.readthedocs.io)
- [Raspberry Pi GPIO Pinout](https://pinout.xyz)
- [RPi.GPIO vs. gpiozero: Which to Use?](https://www.raspberrypi.org/forums/)
- Tutorials and projects on the [Adafruit Learning System](https://learn.adafruit.com)
