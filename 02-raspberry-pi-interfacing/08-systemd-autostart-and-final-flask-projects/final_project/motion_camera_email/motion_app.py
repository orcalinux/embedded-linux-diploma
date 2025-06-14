#!/usr/bin/env python3

import time
import os
from signal import pause
from gpiozero import MotionSensor, LED

from camera_manager import CameraManager
from email_manager import EmailManager

# ------------------
# Global Constants
# ------------------
MOVEMENT_DETECTED_THRESHOLD = 5.0
MIN_DURATION_BETWEEN_PHOTOS = 30.0
CAMERA_FOLDER_PATH = "/home/pi/photos_final_project"
LOG_FILE_NAME = os.path.join(CAMERA_FOLDER_PATH, "photo_logs.txt")

# ------------------
# Global Variables
# ------------------
time_motion_started = time.time()
last_time_photo_taken = 0

# ------------------
# Helper Functions
# ------------------
def update_photo_log(photo_file_name: str):
    """
    Append the new photo path to the photo log file.
    """
    with open(LOG_FILE_NAME, "a") as f:
        f.write(photo_file_name + "\n")

# ------------------
# Main Setup
# ------------------
if not os.path.exists(CAMERA_FOLDER_PATH):
    os.makedirs(CAMERA_FOLDER_PATH)
    print(f"Created folder: {CAMERA_FOLDER_PATH}")

# Remove old log file if it exists
if os.path.exists(LOG_FILE_NAME):
    os.remove(LOG_FILE_NAME)
    print("Old photo_logs.txt removed.")

# Setup Camera
print("Setting up camera...")
camera_manager = CameraManager(CAMERA_FOLDER_PATH)
print("Camera setup OK")

# Setup Email
print("Setting up email client...")
config_file_path = os.path.join("config", "secrets.json")  # Adjust if needed
email_manager = EmailManager(config_file_path)
print("Email setup OK")

print("Setting up GPIO for PIR and LED...")
pir = MotionSensor(4)  # PIR sensor on GPIO pin 4
led = LED(17)          # LED indicator on GPIO pin 17
print("GPIO setup OK")

# ------------------
# Callbacks
# ------------------
def motion_detected():
    global time_motion_started
    time_motion_started = time.time()
    led.on()

def motion_finished():
    global last_time_photo_taken
    led.off()

    motion_duration = time.time() - time_motion_started
    if motion_duration > MOVEMENT_DETECTED_THRESHOLD:
        now = time.time()
        if now - last_time_photo_taken > MIN_DURATION_BETWEEN_PHOTOS:
            last_time_photo_taken = now
            print(">>> Movement > 5s & no photo in last 30s: Taking photo, logging, sending email...")
            photo_file_name = camera_manager.take_photo()
            update_photo_log(photo_file_name)
            email_manager.send_photo(photo_file_name)

# Assign callbacks
pir.when_motion = motion_detected
pir.when_no_motion = motion_finished

print("Motion detection + camera + email system is running. Press Ctrl+C to stop.")
pause()
