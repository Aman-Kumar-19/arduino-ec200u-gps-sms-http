# EC200U GPS Tracking with SMS & Google Sheets (Arduino)

This project demonstrates how to use the **Quectel EC200U LTE module**
with an Arduino to:

- Acquire GPS location (latitude, longitude, UTC time)
- Send location via **SMS**
- Upload GPS data to **Google Sheets** using HTTP GET
- Generate a **Google Maps link** automatically
---
## EC200U GPS • SMS • HTTP Flow
<img width="4368" height="8192" alt="Mermaid Chart - Create complex, visual diagrams with text -2026-01-30-095700" src="https://github.com/user-attachments/assets/ca558a88-9eb9-4806-8750-a85b4c9e7ff4" />


---

## 🚀 Features

- GPS location acquisition using `AT+QGPSLOC?`
- SMS alerts with live Google Maps link
- HTTP GET request to Google Apps Script
- Periodic location updates (every 1 minute)
- Serial debug output for monitoring

---

## 🧰 Hardware Requirements

- Arduino (Uno / Nano / Mega)
- Quectel EC200U LTE module
- LTE SIM card with:
  - SMS support
  - Data plan
- External **4V power supply (2A peak)**
- LTE + GPS antennas

---

## 🔌 UART Connections

| EC200U | Arduino |
|------|--------|
| TXD  | D9 |
| RXD  | D5 |
| GND  | GND |

> ⚠️ **Note:**  
> `SoftwareSerial` at 115200 baud is used **only for demonstration**.  
> For production or reliability, use **hardware UART**.

---

## 📡 Network Configuration

- APN used in this project:
