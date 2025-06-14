# Raspberry Pi GPIO, UART, and SPI Examples

This README contains multiple **Python** code examples for the **Raspberry Pi**, demonstrating:

1. How to **set up** and **enable** the UART on a Raspberry Pi.
2. How to **control LEDs** with a **button** using **gpiozero**.
3. How to **read/write** data via **UART** using **pyserial**.
4. How to **communicate** using **SPI** via the **spidev** library.
5. How to **minimize CPU usage** with event-driven callbacks.
6. How to **handle switch bouncing** with software debouncing.

---

## Table of Contents

- [Raspberry Pi GPIO, UART, and SPI Examples](#raspberry-pi-gpio-uart-and-spi-examples)
  - [Table of Contents](#table-of-contents)
  - [1. Raspberry Pi Setup](#1-raspberry-pi-setup)
  - [2. GPIO Event-Driven Example (Single Button, Three LEDs)](#2-gpio-event-driven-example-single-button-three-leds)
    - [Only One LED On at a Time](#only-one-led-on-at-a-time)
    - [Debouncing: Handling the Bouncing Problem](#debouncing-handling-the-bouncing-problem)
      - [Example with Debouncing](#example-with-debouncing)
      - [Explanation](#explanation)
  - [3. UART Communication on Raspberry Pi](#3-uart-communication-on-raspberry-pi)
    - [UART Receiver Python Script](#uart-receiver-python-script)
    - [Testing and Understanding UART on the Pi](#testing-and-understanding-uart-on-the-pi)
  - [4. SPI Communication on Raspberry Pi](#4-spi-communication-on-raspberry-pi)
    - [SPI Python Example Using spidev](#spi-python-example-using-spidev)
    - [Explanation](#explanation-1)

---

## 1. Raspberry Pi Setup

Before running these examples, ensure your Raspberry Pi is ready:

1. **Enable UART and SPI Interfaces:**

   - Run:
     ```bash
     sudo raspi-config
     ```
   - Under **Interface Options**, enable both **Serial** (disable login shell over serial, but enable hardware serial) and **SPI**.
   - Reboot your Raspberry Pi.

2. **Install Required Packages:**

   Make sure Python 3 and pip are installed:

   ```bash
   sudo apt-get update
   sudo apt-get install python3 python3-pip
   ```

   Then install the necessary Python libraries:

   ```bash
   pip install gpiozero pyserial spidev
   ```

3. **Wiring:**

   - **GPIO Example:** Connect three LEDs (with appropriate current-limiting resistors) to GPIO pins (e.g., 17, 27, 22) and a button to another GPIO pin (e.g., 26).
   - **UART Example:**
     - **UART TX:** GPIO14 (Pin 8)
     - **UART RX:** GPIO15 (Pin 10)  
       You can connect these to your serial device or create a loopback for testing.
   - **SPI Example:**
     - **MOSI:** GPIO10 (Pin 19)
     - **MISO:** GPIO9 (Pin 21)
     - **SCLK:** GPIO11 (Pin 23)
     - **CE0:** GPIO8 (Pin 24)
     - **CE1:** GPIO7 (Pin 26)  
       Connect an SPI device or, for testing, loop MOSI and MISO together.

---

## 2. GPIO Event-Driven Example (Single Button, Three LEDs)

This example uses **gpiozero** to control three LEDs with a single button. Each time the button is pressed, only one LED (in sequence) is lit.

### Only One LED On at a Time

```python
#!/usr/bin/env python3
from gpiozero import LED, Button
from signal import pause

# Define the GPIO pins for three LEDs (adjust as needed)
led_pins = [17, 27, 22]
leds = [LED(pin) for pin in led_pins]

# Define the button pin (adjust as needed)
button = Button(26)

# Keep track of which LED to light next
current_index = 0

def on_button_pressed():
    global current_index
    # Turn off all LEDs to ensure only one is on at a time
    for led in leds:
        led.off()
    # Turn on the LED at the current index
    leds[current_index].on()
    # Move to the next LED, cycling back after the last one
    current_index = (current_index + 1) % len(leds)

# Set the button press callback
button.when_pressed = on_button_pressed

# Keep the program running, listening for button events
pause()
```

### Debouncing: Handling the Bouncing Problem

Mechanical switches can produce multiple rapid on/off signals (bouncing) when pressed. To prevent multiple unwanted triggers, you can use software debouncing. With **gpiozero**, you can set the `bounce_time` parameter for a Button. This parameter specifies a period during which further changes are ignored after an initial event.

#### Example with Debouncing

```python
#!/usr/bin/env python3
from gpiozero import LED, Button
from signal import pause

# Define the GPIO pins for three LEDs (adjust as needed)
led_pins = [17, 27, 22]
leds = [LED(pin) for pin in led_pins]

# Define the button pin with debouncing (bounce_time in seconds)
button = Button(26, bounce_time=0.05)

# Keep track of which LED to light next
current_index = 0

def on_button_pressed():
    global current_index
    # Turn off all LEDs to ensure only one is on at a time
    for led in leds:
        led.off()
    # Turn on the LED at the current index
    leds[current_index].on()
    # Move to the next LED, cycling back after the last one
    current_index = (current_index + 1) % len(leds)

# Set the button press callback
button.when_pressed = on_button_pressed

# Keep the program running, listening for button events
pause()
```

#### Explanation

- **Bounce Time:**  
  By setting `bounce_time=0.2`, the button ignores any further changes for 200 milliseconds after a press. This helps to eliminate false triggers due to mechanical bouncing.

- **Event-Driven Model:**  
  Using `button.when_pressed` ensures the callback is only invoked once per valid press, significantly reducing CPU usage compared to a busy-wait loop.

---

## 3. UART Communication on Raspberry Pi

UART (Universal Asynchronous Receiver/Transmitter) is used for serial communication. On the Raspberry Pi:

- **Primary UART:**  
  `/dev/serial0` is typically a symlink to the primary UART. On many models, it points to either `/dev/ttyAMA0` (the full-featured PL011 UART) or `/dev/ttyS0` (the mini UART).
- **Secondary UART:**  
  Some configurations may expose a second UART (e.g., `/dev/serial1`), though this depends on the model and settings.
- **Physical Pins:**
  - **TX:** GPIO14 (Pin 8)
  - **RX:** GPIO15 (Pin 10)

### UART Receiver Python Script

```python
#!/usr/bin/env python3
import serial
import time

def main():
    # Open the UART port (usually /dev/serial0 on Raspberry Pi)
    try:
        ser = serial.Serial('/dev/serial0', baudrate=9600, timeout=1)
        print("UART port opened successfully!")
    except Exception as e:
        print("Error opening UART port:", e)
        return

    # Write a test message to UART
    test_message = "Hello, UART!\n"
    ser.write(test_message.encode('utf-8'))
    print(f"Sent: {test_message.strip()}")

    try:
        while True:
            # If data is available, read and print it
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                print("Received:", data, end='')
            time.sleep(0.1)  # Delay to reduce CPU usage
    except KeyboardInterrupt:
        print("Exiting UART communication.")
    finally:
        ser.close()
        print("UART port closed.")

if __name__ == "__main__":
    main()
```

### Testing and Understanding UART on the Pi

- **Testing:**  
  Run the script on your Raspberry Pi:

  ```bash
  python3 uart_receiver.py
  ```

  You should see the test message sent and any received data printed.

- **Differences between serial0 and serial1:**
  - **`/dev/serial0`:** A symlink to the primary UART interface.
  - **`/dev/serial1`:** May refer to a secondary UART, but its availability depends on your Pi model and configuration.
- **Physical UART Pins:**  
  Refer to your Raspberry Pi pinout diagram:
  - **TX (Transmit):** GPIO14 (Pin 8)
  - **RX (Receive):** GPIO15 (Pin 10)

---

## 4. SPI Communication on Raspberry Pi

SPI (Serial Peripheral Interface) is another communication protocol used to interface with various peripherals.

- **SPI Device Files:**
  - `/dev/spidev0.0` is typically used for Chip Select 0.
  - `/dev/spidev0.1` is used for Chip Select 1.
- **Physical SPI Pins:**
  - **MOSI:** GPIO10 (Pin 19)
  - **MISO:** GPIO9 (Pin 21)
  - **SCLK:** GPIO11 (Pin 23)
  - **CE0:** GPIO8 (Pin 24)
  - **CE1:** GPIO7 (Pin 26)

### SPI Python Example Using spidev

```python
#!/usr/bin/env python3
import spidev
import time

def main():
    # Create an SPI instance
    spi = spidev.SpiDev()
    # Open SPI bus 0, device (chip select) 0
    spi.open(0, 0)
    # Set SPI speed (adjust as needed)
    spi.max_speed_hz = 50000
    print("SPI interface opened on /dev/spidev0.0")

    # Prepare data to send (example: three bytes)
    to_send = [0x01, 0x02, 0x03]
    print("Sending data:", to_send)
    # Send data and read response simultaneously
    response = spi.xfer2(to_send)
    print("Received response:", response)

    # Close SPI connection
    spi.close()
    print("SPI interface closed.")

if __name__ == "__main__":
    main()
```

### Explanation

- **SPI Initialization:**  
  The SPI device is opened on bus 0, chip select 0 (`/dev/spidev0.0`).
- **Data Transfer:**  
  The example sends three bytes and simultaneously reads back data using `xfer2()`.
- **Testing SPI:**  
  Ensure that SPI is enabled via `raspi-config` and your wiring matches the SPI pinout. For testing, you can connect a loopback (MOSI connected to MISO) to verify data transmission.
