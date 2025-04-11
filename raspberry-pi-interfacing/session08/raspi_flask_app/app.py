from flask import Flask, render_template, jsonify
from gpiozero import Button, LED

# Raspberry Pi GPIO devices
button = Button(26, bounce_time=0.05)
led_list = [LED(17), LED(27), LED(22)]

# Turn all LEDs off initially
for led in led_list:
    led.off()

app = Flask(__name__, template_folder="templates")

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
    Page to control multiple LEDs.
    Renders 'led_control.html' which extends 'base.html'.
    """
    return render_template("led_control.html")

@app.route("/push-button")
def check_push_button_state():
    """
    Returns JSON with current button state (True/False).
    The front end can call this endpoint to see if the button is pressed.
    """
    return jsonify({"pressed": button.is_pressed})

@app.route("/led/<int:led_number>/state/<int:state>")
def switch_led(led_number, state):
    """
    Endpoint to switch one of our LEDs on/off.
    led_number: index into led_list (0 to len-1).
    state: 1 = ON, 0 = OFF.
    Returns JSON indicating success or error message.
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
    # Run on all addresses, default port 5000
    app.run(host="0.0.0.0", port=5000, debug=True)
