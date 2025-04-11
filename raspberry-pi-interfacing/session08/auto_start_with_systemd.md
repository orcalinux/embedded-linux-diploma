# Launching Your Program on Boot with systemd

This document explains how to automatically start your custom Python application on boot using **systemd**. It gives an overview of systemd essentials for Linux users, plus a concrete example for launching a Flask app located in `flask_web_app/`.

---

## 1. What is systemd?

**systemd** is the default init system (process #1) on many modern Linux distributions (e.g., Ubuntu, Debian, Raspbian, Fedora). It manages services, mount points, devices, sockets, and other system resources. Key points:

- **Service Files**: systemd reads unit files (e.g., `*.service`) that describe how to start/stop a service, dependencies, environment, etc.
- **Targets**: systemd organizes boot targets (similar to runlevels in older systems). The usual ones are `multi-user.target` (for server-like environments) or `graphical.target` (for desktop).
- **Commands**: You interact with systemd via commands like `systemctl start`, `systemctl enable`, `systemctl status`, and so on.

### Where do services live?

1. **`/lib/systemd/system/`**

   - Contains system or distribution-provided services installed by packages. You generally **don’t** modify files here directly, because package updates can overwrite your changes.

2. **`/etc/systemd/system/`**

   - The canonical location for **local (custom) systemd services** you create or override. This is where you typically place your `.service` files (e.g., `my_program.service`).

3. **`/run/systemd/system/`**
   - For runtime unit files, typically auto-generated or temporary. Not persistent across reboots.

When you create your own service, you almost always do so in **`/etc/systemd/system/`**.

---

## 2. Creating a systemd Service

1. **Write a Service File**: Typically placed in `/etc/systemd/system/`. For example, create a file named `/etc/systemd/system/my_program.service`.

2. **Basic Structure**: Below is a generic template. Replace placeholders (`/path/to/script.py`, `User=`, etc.) as needed:

   ```ini
   [Unit]
   Description=My Custom Python Program
   After=network.target

   [Service]
   Type=simple
   ExecStart=/usr/bin/python3 /path/to/your_script.py
   WorkingDirectory=/path/to
   User=pi
   Group=pi
   # Environment="MY_VAR=some_value"

   [Install]
   WantedBy=multi-user.target
   ```

   - **[Unit]**:
     - `Description`: A short description of your service.
     - `After=network.target`: Means the service should start after the network is up, if your script depends on internet access.
   - **[Service]**:
     - `Type=simple`: The default; systemd assumes your service starts a process that stays running.
     - `ExecStart`: The command to run your script.
     - `WorkingDirectory`: Where the script will run from.
     - `User` and `Group`: The user context in which the service runs. For Raspberry Pi, often `User=pi` or some other limited user.
     - `Environment`: An optional list of environment variables. If you have a `.env` file, carefully load them or reference them with a path.
   - **[Install]**:
     - `WantedBy=multi-user.target`: Ensures your service starts by default in a normal multi-user environment (non-graphical or server mode).

3. **Permissions**:

   ```bash
   sudo chmod 644 /etc/systemd/system/my_program.service
   ```

   This ensures the service file is readable by systemd but not world-writable.

4. **Reload systemd** so it picks up the new service:

   ```bash
   sudo systemctl daemon-reload
   ```

5. **Enable** your service (so it starts on boot):

   ```bash
   sudo systemctl enable my_program.service
   ```

6. **Start** your service right away (to test it):

   ```bash
   sudo systemctl start my_program.service
   ```

7. **Check status**:
   ```bash
   sudo systemctl status my_program.service
   ```
   This displays logs, whether it’s running, or if there are errors.

---

## 3. Checking Logs and Troubleshooting

1. **View service logs** with:

   ```bash
   journalctl -u my_program.service
   ```

   Press `q` to quit the logs.

2. If your script fails:

   - Ensure `ExecStart` references the correct Python path (e.g., `/usr/bin/python3`).
   - Check that the script is **executable** if needed (otherwise, systemd tries to run it with the interpreter in `ExecStart` anyway).
   - Confirm user permissions. If the script needs special hardware access (e.g., GPIO on Raspberry Pi), you may need to run under `root` or a user in the `gpio` group.

3. If the service never starts:

   - Make sure the `.service` file is placed in `/etc/systemd/system/`, spelled correctly, and you reloaded systemd via `systemctl daemon-reload`.
   - Check for typos in `[Unit]`, `[Service]` sections.

4. Once everything works, the service will auto-start on every reboot.

---

## 4. Updating the Service File

When you change your `.service` file:

1. Edit the file (e.g., `sudo nano /etc/systemd/system/my_program.service`).
2. Run:
   ```bash
   sudo systemctl daemon-reload
   ```
3. Restart the service:
   ```bash
   sudo systemctl restart my_program.service
   ```
4. Check status again:
   ```bash
   sudo systemctl status my_program.service
   ```

---

## 5. Example of a Full Workflow

```bash
# 1) Create the service file
sudo nano /etc/systemd/system/my_program.service

# (Paste in the template, fill in ExecStart, etc.)

# 2) Reload systemd
sudo systemctl daemon-reload

# 3) Enable service on boot
sudo systemctl enable my_program.service

# 4) Start manually to test
sudo systemctl start my_program.service

# 5) Check status
sudo systemctl status my_program.service
```

If everything is good, your script will run automatically every time your system boots.

---

## 6. Best Practices & Common Pitfalls

- **Write robust scripts**: If your Python script crashes, systemd might keep restarting it. Consider adding `Restart=on-failure` in `[Service]` if you want it to restart on crashes. Or set `Restart=no` if you only want a single run.
- **OneShot Services**: For scripts that run once at boot and then exit, you can use `Type=oneshot` and `RemainAfterExit=yes`.
- **Logging**: Use Python’s logging library or print statements to confirm the script’s progress. Systemd captures these logs in `journalctl`.
- **Security**:
  - If the script deals with sensitive data (e.g., email credentials), run it under a limited user.
  - Ensure your `.service` file is not writable by others and that any secrets remain private.

---

## 7. Additional systemd Features

- **Timers**: Instead of cron jobs, systemd can schedule tasks with “timer units” (e.g., run every hour or once a day).
- **Dependencies**: You can define `Requires=` or `Wants=` in the `[Unit]` section if your script depends on a different service being up first.
- **Env Files**: Use `EnvironmentFile=/etc/my_program_env` to load environment variables from a separate file. Then in `[Service]`, reference them as `$VAR_NAME`.

---

## 8. Example: Running Your Flask Web App at Boot

Suppose you have a Flask app located at `/home/pi/flask_web_app/app.py`. You want it to start on boot. Here’s a sample `.service` file:

```ini
[Unit]
Description=My Flask WebApp
After=network.target

[Service]
Type=simple
ExecStart=/usr/bin/python3 /home/pi/flask_web_app/app.py
WorkingDirectory=/home/pi/flask_web_app
User=pi
Group=pi
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

### Steps to Deploy

1. **Create** `/etc/systemd/system/my_flask_app.service` (name it as you like).
2. **Paste** the above content, adjusting paths/users if needed.
3. **Set permissions**:
   ```bash
   sudo chmod 644 /etc/systemd/system/my_flask_app.service
   ```
4. **Reload** systemd:
   ```bash
   sudo systemctl daemon-reload
   ```
5. **Enable** on boot:
   ```bash
   sudo systemctl enable my_flask_app.service
   ```
6. **Start** (test manually):
   ```bash
   sudo systemctl start my_flask_app.service
   ```
7. **Check** logs/status:
   ```bash
   sudo systemctl status my_flask_app.service
   ```
   or
   ```bash
   journalctl -u my_flask_app.service
   ```
8. **Verify** if your Flask app is running by visiting `http://<rpi-ip>:5000` (assuming your `app.py` uses `app.run(host="0.0.0.0", port=5000)`).

---

## 9. Conclusion

Using systemd is a **clean and reliable** way to start your program automatically on boot. The main steps are:

1. Write a `.service` file with `ExecStart` pointing to your Python script.
2. Place it in `/etc/systemd/system/` with correct permissions.
3. Reload systemd, enable, and start your service.
4. Check logs via `systemctl status` or `journalctl -u your_service_name`.
