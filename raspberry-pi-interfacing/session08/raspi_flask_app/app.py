from flask import Flask, render_template, jsonify
from gpiozero import Button

app = Flask(__name__, template_folder='templates')

# Set up the button on GPIO 26
button = Button(26, bounce_time=0.05)


@app.route("/")
def index():
    """
    Renders the main HTML page, which extends base.html.
    """
    return render_template("index.html")

@app.route("/push-button")
def push_button():
    """
    An endpoint to return JSON with the current button state.
    For example, { "pressed": true } or { "pressed": false }.
    """
    is_pressed = button.is_pressed
    return jsonify({"pressed": is_pressed})


if __name__ == "__main__":
    # Serve on all addresses so it's reachable on the network
    app.run(host="0.0.0.0", port=5000, debug=False)
