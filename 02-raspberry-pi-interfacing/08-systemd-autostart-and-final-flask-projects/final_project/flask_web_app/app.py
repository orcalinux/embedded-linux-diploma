#!/usr/bin/env python3
"""
Flask App for Professional Front-End:
-------------------------------------
 - Home route:    '/'
 - Photo logs:    '/photos'
 - Check route:   '/check-photos'
"""

from flask import Flask, render_template
import os

# Use the same folder structure for photos/log file as your motion app
CAMERA_FOLDER_PATH = "/home/pi/photos_final_project"
LOG_FILE_NAME = os.path.join(CAMERA_FOLDER_PATH, "photo_logs.txt")

# This time we serve images from the same folder
app = Flask(__name__,
            static_url_path=CAMERA_FOLDER_PATH,
            static_folder=CAMERA_FOLDER_PATH)

# Keep track of how many lines we’ve read previously
previous_line_counter = 0

@app.route("/")
def index():
    """
    Home route: Just a welcome page with a short description.
    """
    return render_template("index.html")

@app.route("/photos")
def display_photos():
    """
    Reads the photo log and displays the existing photos in a
    user-friendly layout (e.g., table or cards).
    """
    photo_list = []
    if os.path.exists(LOG_FILE_NAME):
        with open(LOG_FILE_NAME, "r") as f:
            for line in f:
                line = line.strip()
                if line:
                    photo_list.append(line)

    # Render the photos.html template, passing the list of photos
    return render_template("photos.html", photos=photo_list)

@app.route("/check-photos")
def check_photos():
    """
    Route that updates the difference in new photos
    since last time it was called. Also shows the last photo.
    """
    global previous_line_counter
    line_counter = 0
    if os.path.exists(LOG_FILE_NAME):
        last_photo_file_name = ""
        with open(LOG_FILE_NAME, "r") as f:
            for line in f:
                line_counter += 1
                last_photo_file_name = line.strip()

        difference = line_counter - previous_line_counter
        previous_line_counter = line_counter

        if line_counter == 0:
            return "No photos in log yet."

        message = f"{difference} new photos since last check.<br>"
        message += f"Last photo: {last_photo_file_name}<br>"
        message += f'<img src="{last_photo_file_name}" style="max-width:400px;" />'
        return message
    else:
        return "No log file found. Possibly no photos yet."

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False)
