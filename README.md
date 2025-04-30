# Remote PC Controller Server

## 📌 Description

This project is a basic **PC control server** that allows a remote client to send commands to a computer over a TCP socket connection. It is written in C++ and intended to run on a Linux-based system. The server listens for user commands and performs various control operations on the machine, including opening applications, shutting down the system, and retrieving battery or email information.

The server supports command recognition using regular expressions and keyword parsing to trigger specific actions.

---

## ✅ Features & Controls

Here are the main control features the server currently supports:

### 🔌 1. Shutdown Commands
- `shutdown now`: Immediately shuts down the PC.
- `shutdown after <minutes>`: Schedules a shutdown after a specified number of minutes.
- `shutdown at hh:mm`: Schedules shutdown at a specific 24-hour format time.

⚠️ **Note**: The shutdown commands require superuser privileges (`sudo`), and currently the password must be manually typed in the terminal.

---

### 📬 2. Seen Emails

This feature is powered by a **Python script** that uses `pyautogui` and image recognition to simulate mouse clicks on Gmail's web interface. Here's what happens:
- The script opens [Gmail](https://gmail.com) in the default browser.
- It waits until the Gmail UI is fully loaded by locating a known image (e.g., "select_all.png").
- Once loaded, it clicks the "Select All" checkbox.
- Then it clicks "Mark as read" to mark all visible emails as seen.

This script is triggered remotely by the command `seen emails`.

---

### 🌐 3. Web Search

- `search web:<query>`: Opens the browser and searches Google for the specified query.

---

### ⚙️ 4. Application Launchers

- `open whatsapp`: Opens the installed WhatsApp desktop app.
- `open tilix`: Launches the Tilix terminal.
- `open edge`: Opens Microsoft Edge browser.
- `open code`: Launches Visual Studio Code.

---

### 🔋 5. Battery Info

- `battery info`: Returns basic battery status information using Linux system files or `upower`.

---

### ❌ 6. Close Server

- `close`: Disconnects the client and optionally terminates the server loop.

---

## ⚠️ Limitations & Issues

This is an early version with some known limitations:

- ❌ **Single Client Only**: The server can only handle one client at a time.
- 🔓 **No Security**: There is no encryption, authentication, or authorization mechanism.
- 🔑 **Manual Sudo Password**: For shutdown commands, the user must manually enter their sudo password on the host PC.
- 🔁 **Too Many Else-Ifs**: The code uses many `else if` statements for command dispatch, which is not scalable or maintainable for larger systems.

---

## 🚀 Future Improvements

Here are some of the enhancements planned for the future:

- 🔐 Add multi-user support with authentication (e.g., username/password or tokens).
- 🔒 Secure communication over the network
- ✅ Implement password-less `sudo` with proper security considerations.
- 💡 Refactor command handling to use a dispatch map (e.g., `std::map<std::string, std::function<void()>>`) instead of long chains of conditionals.
- 📦 Add more controls (e.g., file transfer, media control, system monitoring).


---

## 👤 Author

Eng/Adel Elnimr  
Email: adelelnimr32@gmail.com  
GitHub: adel-hesham

---


