#!/usr/bin/env python3

import yagmail
import json

class EmailManager:
    """
    Sends emails via Yagmail using credentials in a JSON config.

    Example 'secrets.json':
    {
      "sender_email": "my_sender_email@example.com",
      "password": "mypassword123",
      "recipient_email": "recipient@example.com"
    }
    """
    def __init__(self, config_file: str):
        with open(config_file, "r") as f:
            config_data = json.load(f)
        self.sender_email = config_data["sender_email"]
        self.password = config_data["password"]
        self.recipient_email = config_data["recipient_email"]

        # Initialize the yagmail SMTP client
        self.yag = yagmail.SMTP(self.sender_email, self.password)

    def send_photo(self, file_name: str):
        """
        Sends an email with the photo as an attachment.
        """
        self.yag.send(
            to=self.recipient_email,
            subject="New photo from Raspberry Pi",
            contents="Check out the new photo!",
            attachments=file_name
        )
        print(f"Email sent to {self.recipient_email} with attachment {file_name}")
