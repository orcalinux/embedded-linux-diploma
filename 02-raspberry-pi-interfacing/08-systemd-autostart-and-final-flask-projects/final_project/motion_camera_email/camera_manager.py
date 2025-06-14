#!/usr/bin/env python3

import time
import os
from picamzero import Camera

class CameraManager:
    """
    Encapsulates camera setup and photo capture using picamzero.
    """
    def __init__(self, folder_path: str):
        self.folder_path = folder_path
        self.cam = Camera()
        self.cam.still_size = (1640, 1232)
        self.cam.flip_camera(vflip=True, hflip=True)
        time.sleep(2)  # Give camera a moment to warm up

    def take_photo(self) -> str:
        """
        Takes a photo, saves it to 'folder_path',
        returns the file path.
        """
        timestamp = str(time.time())
        filename = os.path.join(self.folder_path, f"img_{timestamp}.jpg")
        self.cam.take_photo(filename)
        print(f"Photo captured: {filename}")
        return filename
