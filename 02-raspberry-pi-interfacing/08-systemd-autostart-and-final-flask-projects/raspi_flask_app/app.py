import threading
from flask import Flask, render_template, jsonify
from gpiozero import Button, LED

# Check current thread
print("Starting on thread:", threading.current_thread().name)

# Initialize GPIO devices directly (default pin factory)
button = Button(26, bounce_time=0.05)
led_list = [LED(17), LED(27), LED(22)]

for led in led_list:
    led.off()

app = Flask(__name__, template_folder="templates")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/push-button")
def check_push_button_state():
    return jsonify({"pressed": button.is_pressed})

@app.route("/led-control")
def led_control_page():
    return render_template("led_control.html")

@app.route("/led/<int:led_number>/state/<int:state>")
def switch_led(led_number, state):
    if led_number < 0 or led_number >= len(led_list):
        return jsonify({"error": "Invalid LED number"}), 400
    if state not in [0, 1]:
        return jsonify({"error": "Invalid state (0 or 1)"}), 400

    if state == 1:
        led_list[led_number].on()
    else:
        led_list[led_number].off()

    return jsonify({"success": True, "led": led_number, "state": state})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False, use_reloader=False)
