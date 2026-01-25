# Hardware Wiring – Arduino ↔ EC200U

This document describes the hardware connections and power requirements
for interfacing an Arduino with the Quectel EC200U LTE module.

---

## ⚠️ Power Requirements (IMPORTANT)

- EC200U operates at **~4.0V**
- Peak current can reach **2A during LTE transmission**
- **DO NOT** power EC200U from Arduino 5V or 3.3V pin
- Use a **dedicated 4V power supply**
- Arduino and EC200U **must share common ground**

---

## UART Connections

This project uses UART communication via `SoftwareSerial`
(for testing and demonstration only).

| EC200U Pin | Arduino Pin | Description |
|----------|------------|-------------|
| TXD      | D9         | Data from EC200U to Arduino |
| RXD      | D5         | Data from Arduino to EC200U |
| GND      | GND        | Common ground |

> ⚠️ **Note:**  
> `SoftwareSerial` at 115200 baud is unreliable.
> For production, use a hardware UART (`Serial1`, USART, etc.).

---

## SIM & Antenna

- Insert a valid LTE SIM card with SMS & data enabled
- Connect LTE antenna **before powering the module**
- Connect GPS antenna for location fix
- Powering EC200U without antenna may damage RF circuitry

---

## Recommended Production Setup

- Hardware UART communication
- Proper power sequencing
- EMI filtering and decoupling capacitors
- Watchdog and brown-out detection

---

## Summary

- UART-based AT command interface
- External power supply mandatory
- Hardware UART strongly recommended
