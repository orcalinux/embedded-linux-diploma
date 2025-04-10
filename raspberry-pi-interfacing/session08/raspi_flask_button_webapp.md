# Raspberry Pi Flask Web App

A simple Flask application running on a Raspberry Pi that serves a **templated** webpage and exposes an API endpoint to read a **push-button** state on GPIO pin 26. Perfect as a starting point for IoT or embedded web interfaces.

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
│       └── script.js    # JavaScript for dynamic fetch, UI updates, etc.
└── templates/
    ├── base.html        # Base layout (common HTML structure)
    └── index.html       # Main page, extends base.html
```

### Explanation

- **app.py**: Contains your Flask routes, GPIO logic, and server config.
- **requirements.txt**: Lists project dependencies for easy installation.
- **static/** folder: Holds your **CSS** and **JavaScript** assets.
- **templates/** folder: Contains **Jinja2 HTML templates**, allowing you to separate HTML from Python code.

---

## 2. Overview

- Runs a Flask server on a Raspberry Pi.
- Reads a **push button** on GPIO 26 using **gpiozero**.
- Renders an HTML page with **Jinja2** templates, **CSS**, and **JavaScript**.
- Optionally expands to more sensors or outputs (e.g., LED control).

---

## 3. Features

- **Template-based** front end (using `base.html` + `index.html`).
- **Static** folder for easily serving `style.css` and `script.js`.
- Real-time button status updates via `/push-button` endpoint.
- Minimal dependencies (`Flask`, `gpiozero`).
- Internal or external pull-down resistor support for the push button.

---

## 4. Hardware Setup

1. **Raspberry Pi** (with GPIO).
2. **Push Button** on GPIO 26:
   - One side → GPIO 26
   - Other side → 3.3 V
   - Internal or external pull-down to ground.

Example schematic:

```
       +3.3V
         |
       [Button]
         |
       GPIO 26
         |
       (Pi GND via internal pull-down)
```

_(Adjust wiring accordingly. Confirm your code’s pin matches your setup.)_

---

## 5. Installation & Requirements

- **Python 3** (most Pi distributions already have it).
- **Flask**:
  ```bash
  sudo apt update
  sudo apt install python3-flask
  ```
- **gpiozero**:
  ```bash
  sudo apt install python3-gpiozero
  ```
- Alternatively, install via pip using `requirements.txt`:
  ```bash
  pip3 install -r requirements.txt
  ```

_(Edit `requirements.txt` to specify Flask, gpiozero versions if necessary.)_

---

## 6. Code Explanation

### 6.1 `app.py`

Below is a simplified example. The routes serve **template** files from `templates/` and static files from `static/`. The `Button` object reads GPIO 26.

```python
from flask import Flask, render_template, jsonify
from gpiozero import Button

button = Button(26, bounce_time=0.05)
app = Flask(__name__)

@app.route("/")
def index():
    # Render the main template (inherits base.html)
    return render_template("index.html")

@app.route("/push-button")
def push_button_state():
    # Return JSON about button state
    return jsonify({"pressed": button.is_pressed})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
```

**Key Points**:

- `render_template("index.html")` uses **Jinja2** to load `index.html` from `templates/`.
- The `/push-button` endpoint returns JSON (e.g., `{"pressed": true}`), which front-end JavaScript can parse.
- `bounce_time` helps debounce the physical button.

---

### 6.2 Templates (Jinja2)

**`base.html`** (common layout):

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>{% block title %}Raspberry Pi App{% endblock %}</title>
    <link
      rel="stylesheet"
      href="{{ url_for('static', filename='css/style.css') }}"
    />
  </head>
  <body>
    <header>
      <h1>Raspberry Pi Flask App</h1>
      <hr />
    </header>

    <section>{% block content %}{% endblock %}</section>

    <footer>
      <hr />
      <p>&copy; 2023 RPi Flask Demo</p>
    </footer>

    <script src="{{ url_for('static', filename='js/script.js') }}"></script>
  </body>
</html>
```

**`index.html`** (extends base):

```html
{% extends "base.html" %} {% block title %}Home - Button Status{% endblock %} {%
block content %}
<h2>Check Push Button</h2>
<div id="button-status">Loading...</div>
<button onclick="updateButtonStatus()">Check Now</button>
{% endblock %}
```

**Key Points**:

- `{% extends "base.html" %}` inherits the shared layout from `base.html`.
- `url_for('static', filename='...')` references static files in `static/`.

---

### 6.3 Static Files (CSS & JS)

**`static/css/style.css`** example:

```css
body {
  font-family: Arial, sans-serif;
  margin: 20px;
}
#button-status {
  color: green;
  font-weight: bold;
}
```

**`static/js/script.js`** example:

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

**Key Points**:

- `fetch("/push-button")` calls our Flask endpoint, which returns JSON.
- We dynamically update the text and color in the `<div id="button-status">`.

---

## 7. How to Run

1. **Clone or Copy**: Download the `raspi_flask_app` folder to your Raspberry Pi.
2. **Install Dependencies**:
   ```bash
   cd raspi_flask_app
   pip3 install -r requirements.txt
   ```
   (Or install manually via `apt` if you prefer.)
3. **Run the App**:
   ```bash
   python3 app.py
   ```
4. **Access**: On the Pi or a device on the same LAN:
   ```
   http://<PI-IP>:5000
   ```
5. You should see the “Raspberry Pi Flask App” header and the button status page.

---

## 8. Usage

- **Check Button**: Press the physical button on GPIO 26.
- **Refresh UI**: Click “Check Now” or automate it (e.g., `setInterval` in `script.js`).
- **Edit HTML**: Update `templates/index.html` to add more sections.
- **Style**: Modify `static/css/style.css`.

---

## 9. Troubleshooting

- **ModuleNotFoundError**: If `flask` or `gpiozero` is missing, install via `sudo apt install python3-flask python3-gpiozero` or use `pip3 install`.
- **Button Always False**: Check wiring or consider specifying `pull_up=False` if using external pull-down.
- **Cannot Reach Page**: Ensure the Pi’s IP is correct. Run `hostname -I` to confirm. Check firewall settings.
- **Permission Error**: Some older Pi OS versions may need `sudo` to access GPIO, or use `gpiozero` which handles permissions more gracefully.

---

## 10. Next Steps

- **Expand** to multiple GPIO inputs or outputs (LED, sensors, motor driver).
- **Secure** the app with user authentication if it’s on a public network.
- **Production**: For long-term or large-scale usage, consider running with `gunicorn` + `nginx`.
- **Advanced UI**: Use frameworks like **Bootstrap** or **Vue.js** for a richer interface.
