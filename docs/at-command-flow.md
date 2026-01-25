# AT Command Flow – EC200U GPS, SMS & HTTP

This document explains the sequence of AT commands used to:

1. Initialize the EC200U module
2. Enable GPS and acquire location
3. Send SMS with location
4. Upload data to Google Sheets via HTTP

---

## 1️⃣ Basic Communication Check

```text
AT
Purpose:
Verify UART communication with EC200U.

Expected Response:

OK

2️⃣ SIM & Network Checks
AT+CPIN?
AT+CSQ
AT+CREG?
AT+CGATT?


Purpose:
Ensure SIM readiness, signal quality, network registration,
and packet service availability.

3️⃣ Configure PDP Context (APN)
AT+QICSGP=1,1,"airtelgprs.com","","",1


Purpose:
Configure APN for mobile data connection.

Replace airtelgprs.com if using another network provider.

4️⃣ Activate PDP Context
AT+QIACT=1


Purpose:
Activate data context and obtain IP address.

5️⃣ Enable GPS
AT+QGPS=1


Purpose:
Power on the GNSS engine inside EC200U.

6️⃣ Read GPS Location
AT+QGPSLOC?


Purpose:
Retrieve current GPS location, UTC time, and fix status.

7️⃣ Send SMS
AT+CMGF=1
AT+CMGS="+91XXXXXXXXXX"


Then send message text and terminate with:

Ctrl + Z (0x1A)


Purpose:
Send GPS location via SMS.

8️⃣ HTTP Upload to Google Sheets
AT+QHTTPURL=<length>,80
AT+QHTTPGET=80


Purpose:
Send GPS data to Google Apps Script using HTTP GET.

🔁 Flow Summary
AT
 ↓
SIM / Network Check
 ↓
PDP Context Setup
 ↓
Enable GPS
 ↓
Get GPS Fix
 ↓
Send SMS
 ↓
HTTP Upload
 ↓
Delay → Repeat
