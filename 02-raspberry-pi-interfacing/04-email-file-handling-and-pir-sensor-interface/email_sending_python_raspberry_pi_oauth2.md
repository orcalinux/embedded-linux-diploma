# Sending Email from a Raspberry Pi Using Python (Step-by-Step, Including OAuth2)

## Table of Contents

- [Sending Email from a Raspberry Pi Using Python (Step-by-Step, Including OAuth2)](#sending-email-from-a-raspberry-pi-using-python-step-by-step-including-oauth2)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction](#1-introduction)
  - [2. Prerequisites](#2-prerequisites)
  - [3. Install Yagmail](#3-install-yagmail)
  - [4. Step 1: The Simplest Possible Script](#4-step-1-the-simplest-possible-script)
  - [5. Step 2: Storing Your Password Securely](#5-step-2-storing-your-password-securely)
    - [Using a Local File](#using-a-local-file)
    - [Using Environment Variables](#using-environment-variables)
  - [6. Adding Attachments and HTML (Yagmail)](#6-adding-attachments-and-html-yagmail)
  - [7. What Is MIME?](#7-what-is-mime)
  - [8. Optional: Manual MIME with `smtplib`](#8-optional-manual-mime-with-smtplib)
  - [9. Using OAuth2 Instead of an App Password](#9-using-oauth2-instead-of-an-app-password)
    - [9.1 Why OAuth2?](#91-why-oauth2)
    - [9.2 Setting up OAuth2 with Yagmail](#92-setting-up-oauth2-with-yagmail)
    - [9.3 Example Code](#93-example-code)
  - [10. Next Steps \& Additional Tips](#10-next-steps--additional-tips)
  - [11. References](#11-references)

---

## 1. Introduction

This guide teaches you to send emails from a **Raspberry Pi** (or any Python environment) using:

- **Yagmail** (a user-friendly library for Gmail SMTP)
- **App Passwords** (if using Gmail with 2FA), or
- **OAuth2** (the most secure approach, so you never store a password at all).

We’ll start with a basic approach, then enhance security, add attachments, explain MIME, and finally show how to use **OAuth2** for Gmail.

---

## 2. Prerequisites

1. **Raspberry Pi** with Python 3.x (or any machine running Python 3).
2. **pip3** to install libraries.
3. A **Gmail account** (or another SMTP provider).
   - For Gmail, if using 2FA, either an **App Password** or **OAuth2** is needed.
4. (Optional) **Google Cloud Console** access, if you want to create custom OAuth2 credentials (we’ll show a simple Yagmail approach that can handle some OAuth2 steps automatically).

---

## 3. Install Yagmail

In your Raspberry Pi’s terminal, run:

```bash
pip3 install yagmail
```

> If you plan to use OAuth2 with Yagmail, install the extra requirements:
>
> ```bash
> pip3 install yagmail[oauth]
> ```
>
> This brings in libraries needed for handling OAuth2 flows.

---

## 4. Step 1: The Simplest Possible Script

**Warning**: Hardcoding credentials in your script is **insecure** but useful for a quick test.

Create `send_email_simple.py`:

```python
#!/usr/bin/env python3

import yagmail

my_gmail = "your_gmail@gmail.com"
my_password = "your_password_or_app_password"  # If using 2FA, use an App Password

recipient = "recipient@example.com"

yag = yagmail.SMTP(user=my_gmail, password=my_password)
yag.send(
    to=recipient,
    subject="Test Email (Simple Version)",
    contents="Hello! This is the simplest example using Yagmail."
)

print("Email sent!")
```

Run:

```bash
python3 send_email_simple.py
```

Check the recipient’s inbox. If it arrives, you’re all set. Again, **do not** store real credentials like this for production.

---

## 5. Step 2: Storing Your Password Securely

### Using a Local File

1. Create a hidden file for the password:
   ```bash
   echo "my_app_password_or_secret" > /home/pi/.local/share/.email_password
   chmod 600 /home/pi/.local/share/.email_password
   ```
2. Update your script:

   ```python
   #!/usr/bin/env python3

   import yagmail

   with open("/home/pi/.local/share/.email_password", "r") as f:
       password = f.read().strip()

   my_gmail = "your_gmail@gmail.com"
   recipient = "recipient@example.com"

   yag = yagmail.SMTP(user=my_gmail, password=password)
   yag.send(
       to=recipient,
       subject="Test Email (Password from File)",
       contents="Now I'm reading my password from a local file!"
   )
   print("Email sent!")
   ```

### Using Environment Variables

1. Edit `~/.bashrc` (or `~/.profile`) and add:
   ```bash
   export GMAIL_APP_PASSWORD="my_app_password_or_secret"
   ```
2. Reload your profile:
   ```bash
   source ~/.bashrc
   ```
3. In Python:

   ```python
   import os
   import yagmail

   password = os.environ.get("GMAIL_APP_PASSWORD")
   my_gmail = "your_gmail@gmail.com"
   recipient = "recipient@example.com"

   yag = yagmail.SMTP(my_gmail, password)
   yag.send(
       to=recipient,
       subject="Password from Environment Variable",
       contents="Secure approach: reading the password from env vars!"
   )
   print("Email sent!")
   ```

---

## 6. Adding Attachments and HTML (Yagmail)

Yagmail makes it easy to send **attachments** and **HTML**:

```python
#!/usr/bin/env python3

import yagmail

def send_email_with_attachment(gmail_user, gmail_password, recipient, filepath):
    yag = yagmail.SMTP(gmail_user, gmail_password)

    # List items can be text, file paths, or HTML
    contents = [
        "Hello, here's an attachment:",
        filepath,
        "<b>This is some HTML content in bold!</b>"
    ]

    yag.send(
        to=recipient,
        subject="Email with Attachment and HTML",
        contents=contents
    )
    print("Email sent with attachment and HTML!")

if __name__ == "__main__":
    # Example usage
    gmail_address = "your_gmail@gmail.com"
    gmail_password = "your_app_password"
    recipient = "recipient@example.com"

    file_to_attach = "/home/pi/test.txt"

    send_email_with_attachment(gmail_address, gmail_password, recipient, file_to_attach)
```

Under the hood, Yagmail automatically constructs a **MIME** email with multiple parts (text, HTML, attachments).

---

## 7. What Is MIME?

**MIME** stands for **Multipurpose Internet Mail Extensions**. It defines how email clients handle:

- **Multiple parts**: text, HTML, attachments.
- **Headers** describing content type and encoding.

When you attach a file or send HTML, Yagmail (or the standard `email` library) sets up the correct MIME structure. If you want full control, you can manually code MIME parts (see below).

---

## 8. Optional: Manual MIME with `smtplib`

For advanced usage or non-Gmail servers, you can manually create MIME messages:

```python
import smtplib
import ssl
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

sender = "your_gmail@gmail.com"
receiver = "recipient@example.com"
subject = "Manual MIME Example"
body = "Hi, this email is built using MIMEMultipart and MIMEText."

msg = MIMEMultipart()
msg["From"] = sender
msg["To"] = receiver
msg["Subject"] = subject

msg.attach(MIMEText(body, "plain"))

context = ssl.create_default_context()
with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context) as server:
    server.login(sender, "YOUR_APP_PASSWORD")
    server.sendmail(sender, receiver, msg.as_string())
```

This requires more code, but you get total control over headers, multi-part structures, inline images, etc.

---

## 9. Using OAuth2 Instead of an App Password

### 9.1 Why OAuth2?

- **No password stored**: OAuth2 tokens replace your password.
- **Granular permissions**: Google can grant token-based access for sending email, without exposing your full account password.
- **Revocable**: You can revoke OAuth2 credentials at any time without changing your real password.

### 9.2 Setting up OAuth2 with Yagmail

Yagmail supports OAuth2 flows via the **`yagmail[oauth]`** extras:

1. **Install** with OAuth2 extras:
   ```bash
   pip3 install yagmail[oauth]
   ```
2. **Register** your email with Yagmail to generate an OAuth2 token:

   ```python
   import yagmail

   # The first time, you may need to authorize via a browser window
   yagmail.register('your_gmail@gmail.com', oauth2_file='~/oauth2_creds.json')
   ```

   This command-line or script process may prompt you to visit a link in your browser to grant permission. Once complete, your token is saved locally (in `oauth2_creds.json`).

> **Alternatively**: If you have a Google Cloud project with OAuth2 credentials (Client ID & Secret), you can specify them. See [Yagmail docs](https://github.com/kootenpv/yagmail#oauth2) or [google-auth-oauthlib docs](https://google-auth.readthedocs.io/en/stable/) for advanced details.

### 9.3 Example Code

After registering, you can use OAuth2 automatically:

```python
#!/usr/bin/env python3

import yagmail

def send_oauth2_email():
    # No password needed here if you have the token file
    yag = yagmail.SMTP(
        user="your_gmail@gmail.com",
        oauth2_file="~/oauth2_creds.json"
    )
    yag.send(
        to="recipient@example.com",
        subject="Hello via OAuth2",
        contents="This message is sent with OAuth2. No stored password!"
    )
    print("Email sent via OAuth2!")

if __name__ == "__main__":
    send_oauth2_email()
```

**Explanation**:

- Once `oauth2_creds.json` is set up, Yagmail uses it to generate a valid OAuth2 token for sending Gmail.
- If the token expires or is invalid, Yagmail will help you refresh or reauthorize.

---

## 10. Next Steps & Additional Tips

1. **Multiple Recipients**
   - Pass a list to `to`: `yag.send(to=["first@example.com", "second@example.com"], ...)`.
2. **HTML Emails**
   - Use an HTML string in `contents`: `"<h1>Title</h1><p>Paragraph</p>"`.
3. **File Permissions**
   - Keep your local `.email_password` or `oauth2_creds.json` file with `chmod 600`.
4. **Error Handling**
   - Wrap your sending code in `try-except` blocks to handle timeouts or credential errors gracefully.
5. **Other SMTP Providers**
   - Adjust server and port accordingly. For example, `smtp.office365.com` for Outlook with `port 587`.
6. **Revoking OAuth2**
   - If necessary, revoke access in your [Google Account Security settings](https://myaccount.google.com/permissions).

---

## 11. References

- **Yagmail** GitHub:  
  [https://github.com/kootenpv/yagmail](https://github.com/kootenpv/yagmail)
- **Gmail SMTP Settings**:  
  [https://support.google.com/mail/answer/7126229](https://support.google.com/mail/answer/7126229)
- **App Passwords & 2FA**:  
  [https://support.google.com/accounts/answer/185833](https://support.google.com/accounts/answer/185833)
- **Google OAuth2 with Python**:  
  [https://google-auth.readthedocs.io/en/stable/](https://google-auth.readthedocs.io/en/stable/)
- **Python `smtplib` Docs**:  
  [https://docs.python.org/3/library/smtplib.html](https://docs.python.org/3/library/smtplib.html)
