# Remote PC Controller Server

## 📌 Description

This project is a basic **PC control server** that allows a remote client to send commands to a computer over a TCP socket connection. It is written in C++ and intended to run on a Linux-based system. The server listens for user commands and performs various control operations on the machine, including opening applications, shutting down the system, and retrieving battery or email information.

The server supports command recognition using regular expressions and keyword parsing to trigger specific actions.

### Used server with android phone:
https://play.google.com/store/apps/details?id=tcpudpserverclient.steffenrvs.tcpudpserverclient&hl=en

---

⚠️ **Note**: The server uses case-insensitive pattern matching for commands.

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
### 🧾 3. Send terminal commands and receive their live output.

-  send a terminal command ad you will receive the output


### 🌐 4. Web Search

- `search web:<query>`: Opens the browser and searches Google for the specified query.

---

### ⚙️ 5. Application Launchers

- `open whatsapp`: Opens the installed WhatsApp desktop app.
- `open tilix`: Launches the Tilix terminal.
- `open browser`: Opens the default browser.
- `open code`: Launches Visual Studio Code.
- `open terminal` : Opens gnome-terminal.
## Open websites like:
- `open youtube`
- `open github`
- `open linkedin`
- `open facebook`

---

### 🔋 6. Battery Info

- `battery info`: Returns basic battery status information using Linux system files or `upower`.

---

### ❌ 7. Close Server

- `close`: Disconnects the client and optionally terminates the server loop and safely closes the used resources like the socket..

---

### 🛡 8 Signal Handling
The project includes a signal handler module to handle safe exits and safely free the resources (RAII) on system signals:

SIGINT (Ctrl+C)

SIGTERM (kill command)

## ⚠️ Limitations & Issues

This is an early version with some known limitations:

- 🔓 **No Security**: There is no encryption, authentication, or authorization mechanism.
- 🔑 **Manual Sudo Password**: For shutdown commands, the user must manually enter their sudo password on the host PC.

---

## 🚀 Future Improvements

Here are some of the enhancements planned for the future:

- 🔒 Secure communication over the network
- ✅ Implement password-less `sudo` with proper security considerations.
- 📦 Add more controls (e.g., file transfer, media control, system monitoring).


## To Compile 

g++ server.cpp command.cpp main.cpp signal_handler.cpp -o server

## To Run

./server

---

## 👤 Author

Eng/Adel Elnimr  
Email: adelelnimr32@gmail.com
linkedin: https://www.linkedin.com/in/adel-elnimr-0552ba225/
GitHub: adel-hesham

---
