# Raspberry Pi Flask Web App

A simple Flask application running on a Raspberry Pi that serves a **templated** webpage, exposes an API endpoint to read a **push-button** state on GPIO 26, and provides routes to control **multiple LEDs** (e.g., GPIO pins 17, 27, 22). Perfect as a starting point for IoT or embedded web interfaces.

---

## Table of Contents

- [Raspberry Pi Flask Web App](#raspberry-pi-flask-web-app)
  - [Table of Contents](#table-of-contents)
  - [1. Project Structure](#1-project-structure)
    - [Explanation](#explanation)
  - [2. Overview](#2-overview)
  - [3. Features](#3-features)
  - [4. Hardware Setup](#4-hardware-setup)
  - [5. Installation \& Requirements](#5-installation--requirements)
  - [6. Code Explanation](#6-code-explanation)
    - [6.1 `app.py`](#61-apppy)
    - [6.2 Templates (Jinja2)](#62-templates-jinja2)
    - [6.3 Static Files (CSS \& JS)](#63-static-files-css--js)
  - [7. How to Run](#7-how-to-run)
  - [8. Usage](#8-usage)
  - [9. Troubleshooting](#9-troubleshooting)
  - [10. Next Steps](#10-next-steps)

---

## 1. Project Structure

```
raspi_flask_app/
├── app.py               # Main Flask application
├── requirements.txt     # Python dependencies (Flask, gpiozero, etc.)
├── static/
│   ├── css/
│   │   └── style.css    # CSS for styling
│   └── js/
│       ├── script.js    # JS for button status
│       └── led_control.js  # JS for toggling LEDs
└── templates/
    ├── base.html        # Base layout (common HTML structure)
    ├── index.html       # Main page for button status
    └── led_control.html # Additional page for LED control
```

### Explanation

- **app.py**: Contains your Flask routes, GPIO logic, and server config (both button and LED).
- **requirements.txt**: Lists project dependencies for easy installation (Flask, gpiozero, etc.).
- **static/** folder: Holds CSS/JS assets (separated by functionality, e.g., `script.js` for button status, `led_control.js` for LED toggling).
- **templates/** folder: Contains Jinja2 HTML templates, including:
  - **base.html** (common layout).
  - **index.html** for button status.
  - **led_control.html** for controlling multiple LEDs.

---

## 2. Overview

- Runs a Flask server on a Raspberry Pi.
- **Reads** a push button on GPIO 26.
- **Controls** multiple LEDs (e.g., pins 17, 27, 22).
- Renders separate HTML pages for each function (button status vs. LED control).
- Easily expandable to more devices, additional pages, etc.

---

## 3. Features

- **Template-based** front end (using `base.html` + child templates).
- **Static** folder for serving `style.css` and specialized JavaScript files.
- Real-time button status updates via `/push-button` endpoint.
- Routes for toggling specific LEDs: `/led/<led_number>/state/<0_or_1>`.
- Minimal dependencies (`Flask`, `gpiozero`) and straightforward setup on Raspberry Pi.

---

## 4. Hardware Setup

1. **Raspberry Pi** (with GPIO).
2. **Push Button** on GPIO 26:
   - One side → GPIO 26
   - Other side → 3.3 V
   - Optionally an external pull-down, or rely on the Pi’s internal pull-down.
3. **LEDs**: for example, pins 17, 27, and 22:
   - Each LED anode → respective GPIO pin
   - Each LED cathode → resistor → GND

Example schematic for the button:

```
       +3.3V
         |
       [Button]
         |
       GPIO 26
         |
   (Pi GND via internal pull-down)
```

And each LED might be:

```
   GPIO 17 ---[LED]---[Resistor]--- GND
   GPIO 27 ---[LED]---[Resistor]--- GND
   GPIO 22 ---[LED]---[Resistor]--- GND
```

---

## 5. Installation & Requirements

- **Python 3** (pre-installed on most Pi distributions).
- **Flask**:
  ```bash
  sudo apt update
  sudo apt install python3-flask
  ```
- **gpiozero**:
  ```bash
  sudo apt install python3-gpiozero
  ```
- Or install via pip using `requirements.txt`:
  ```bash
  pip3 install -r requirements.txt
  ```

_(Edit `requirements.txt` to specify Flask, gpiozero versions if needed.)_

---

## 6. Code Explanation

### 6.1 `app.py`

Below is a simplified example. It includes **button** logic on GPIO 26 and an **LED list** for toggling multiple pins.

```python
from flask import Flask, render_template, jsonify
from gpiozero import Button, LED

# Setup button on GPIO 26
button = Button(26, bounce_time=0.05)

# Example LED pins 17, 27, 22
led_list = [LED(17), LED(27), LED(22)]
for led in led_list:
    led.off()  # turn off all LEDs initially

app = Flask(__name__)

@app.route("/")
def index():
    """
    Main page (displays button status).
    Renders 'index.html' which extends 'base.html'.
    """
    return render_template("index.html")

@app.route("/led-control")
def led_control_page():
    """
    A separate page for toggling multiple LEDs.
    Renders 'led_control.html' which extends 'base.html'.
    """
    return render_template("led_control.html")

@app.route("/push-button")
def push_button_state():
    """
    Returns JSON with current button state (True/False).
    The front end can call this endpoint to see if the button is pressed.
    """
    return jsonify({"pressed": button.is_pressed})

@app.route("/led/<int:led_number>/state/<int:state>")
def switch_led(led_number, state):
    """
    Endpoint to switch an LED on/off.
    led_number is the index in led_list (0, 1, 2),
    state is 1 = ON, 0 = OFF.
    Returns JSON indicating success or any errors.
    """
    if led_number < 0 or led_number >= len(led_list):
        return jsonify({"error": f"Invalid LED number: {led_number}"})
    if state not in [0, 1]:
        return jsonify({"error": "State must be 0 or 1"})

    if state == 1:
        led_list[led_number].on()
    else:
        led_list[led_number].off()

    return jsonify({"success": True, "led": led_number, "state": state})

if __name__ == "__main__":
    # Run on all addresses, port 5000
    app.run(host="0.0.0.0", port=5000)
```

**Key Points**:

- `index()` route -> returns `index.html` for **button status**.
- `led_control_page()` -> returns `led_control.html` for **LED toggling**.
- `"/push-button"` -> returns JSON, e.g. `{"pressed": true}`.
- `"/led/<int:led_number>/state/<int:state>"` -> toggles the chosen LED pin.
- `bounce_time=0.05` helps debounce the push button.

---

### 6.2 Templates (Jinja2)

**`base.html`** (common layout):

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>{% block title %}RPi Flask App{% endblock %}</title>
    <link
      rel="stylesheet"
      href="{{ url_for('static', filename='css/style.css') }}"
    />
  </head>
  <body>
    <header>
      <h1>Raspberry Pi Flask Web App</h1>
      <nav>
        <!-- Simple nav links -->
        <a href="{{ url_for('index') }}">Home</a> |
        <a href="{{ url_for('led_control_page') }}">LED Control</a>
      </nav>
      <hr />
    </header>

    <section>{% block content %}{% endblock %}</section>

    <footer>
      <hr />
      <p>&copy; 2025 Raspberry Pi Flask Demo</p>
    </footer>
  </body>
</html>
```

**`index.html`** (for button status, extends base):

```html
{% extends "base.html" %} {% block title %}Home - Button Status{% endblock %} {%
block content %}
<h2>Push Button Status</h2>
<p id="button-status">Loading...</p>
<button onclick="updateButtonStatus()">Check Now</button>

<!-- Script for button logic -->
<script src="{{ url_for('static', filename='js/script.js') }}"></script>
{% endblock %}
```

**`led_control.html`** (for multiple LED toggling):

```html
{% extends "base.html" %} {% block title %}LED Control{% endblock %} {% block
content %}
<h2>Control LEDs</h2>
<p>Select which LED to toggle:</p>
<select id="ledSelect">
  <option value="0">LED 0 (GPIO17)</option>
  <option value="1">LED 1 (GPIO27)</option>
  <option value="2">LED 2 (GPIO22)</option>
</select>
<button onclick="turnLedOn()">Turn On</button>
<button onclick="turnLedOff()">Turn Off</button>

<p id="ledMessage"></p>

<!-- Script for LED logic -->
<script src="{{ url_for('static', filename='js/led_control.js') }}"></script>
{% endblock %}
```

**Key Points**:

- We add a **nav** bar in `base.html` linking to Home vs. LED Control.
- Each child template loads its own JS file inside the content block.

---

### 6.3 Static Files (CSS & JS)

**`static/css/style.css`** example:

```css
body {
  font-family: Arial, sans-serif;
  margin: 20px;
}
nav a {
  margin-right: 10px;
  text-decoration: none;
  color: #0066cc;
}
nav a:hover {
  text-decoration: underline;
}
#button-status,
#ledMessage {
  color: green;
  font-weight: bold;
  margin-top: 1em;
}
```

**`static/js/script.js`** (handles button status):

```js
async function updateButtonStatus() {
  try {
    const response = await fetch("/push-button");
    const data = await response.json(); // { "pressed": true/false }
    const statusElem = document.getElementById("button-status");
    if (data.pressed) {
      statusElem.textContent = "Button is pressed!";
      statusElem.style.color = "red";
    } else {
      statusElem.textContent = "Button is not pressed.";
      statusElem.style.color = "green";
    }
  } catch (err) {
    console.error("Error:", err);
  }
}
```

**`static/js/led_control.js`** (handles LED toggling):

```js
const ledSelect = document.getElementById("ledSelect");
const ledMessage = document.getElementById("ledMessage");

async function setLedState(state) {
  try {
    const ledNum = ledSelect.value; // "0", "1", or "2"
    const response = await fetch(`/led/${ledNum}/state/${state}`);
    const data = await response.json(); // e.g. { success: true, led: 0, state: 1 }

    if (data.error) {
      ledMessage.textContent = `Error: ${data.error}`;
      ledMessage.style.color = "red";
    } else {
      const isOn = data.state === 1;
      ledMessage.textContent = `LED ${data.led} is now ${isOn ? "ON" : "OFF"}`;
      ledMessage.style.color = isOn ? "red" : "green";
    }
  } catch (err) {
    console.error("Error:", err);
    ledMessage.textContent = "Error toggling LED.";
    ledMessage.style.color = "red";
  }
}

function turnLedOn() {
  setLedState(1);
}

function turnLedOff() {
  setLedState(0);
}
```

---

## 7. How to Run

1. **Clone or Copy**: Download the `raspi_flask_app` folder to your Raspberry Pi.
2. **Install Dependencies**:
   ```bash
   cd raspi_flask_app
   pip3 install -r requirements.txt
   ```
   (Or install manually via `apt`, if you prefer.)
3. **Run the App**:
   ```bash
   python3 app.py
   ```
4. **Access** the app from your Pi or another device on the same LAN:
   ```
   http://<pi-ip>:5000
   ```
5. You should see a home page displaying the button status. Navigate to `/led-control` (or use the navbar link) to toggle LEDs.

---

## 8. Usage

- **Check Button**: Visit `http://<pi-ip>:5000/`, press the physical button on GPIO 26, then click “Check Now.”
- **Toggle LEDs**: Visit `http://<pi-ip>:5000/led-control`. Choose an LED (0,1,2) and press Turn On/Off. Observe the LED’s state on the Pi.
- **Customize**: Add more pins, advanced logic, or a dynamic UI to suit your needs.

---

## 9. Troubleshooting

- **ModuleNotFoundError**: Ensure `Flask` and `gpiozero` are installed.
- **Button or LED Not Responding**: Double-check wiring (GPIO pins, resistor orientation), code pin references, and pull-up/pull-down config.
- **Cannot Reach Page**: Confirm IP with `hostname -I`. Check if your network or firewall blocks port 5000.
- **Permissions**: Some Pi setups require root for GPIO. Usually, gpiozero is configured to run as a normal user on Raspberry Pi OS, but older distros might differ.

---

## 10. Next Steps

- **Security**: Add authentication if you’re exposing the Pi on a public network.
- **Production**: Deploy with `gunicorn` and `nginx` for a more reliable or large-scale environment.
- **UI Enhancements**: Implement frameworks like **Bootstrap**, **Vue**, or **React** for an enhanced front-end.
- **Multiple Pages**: Add more routes for sensors, data logging, or advanced dashboards.
