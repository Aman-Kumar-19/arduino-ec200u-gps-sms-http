This document explains the GPS data returned by the EC200U module
using the `AT+QGPSLOC?` command.

---

## Raw Response Format

```text
+QGPSLOC: hhmmss.s,lat,N,lon,E,hdop,alt,fix,cog,spkm,spkn


| Field    | Description            |
| -------- | ---------------------- |
| hhmmss.s | UTC time               |
| lat      | Latitude (DDMM.MMMM)   |
| N/S      | Latitude direction     |
| lon      | Longitude (DDDMM.MMMM) |
| E/W      | Longitude direction    |
| hdop     | Horizontal dilution    |
| alt      | Altitude (meters)      |
| fix      | GPS fix status         |
| cog      | Course over ground     |
| spkm     | Speed (km/h)           |
| spkn     | Speed (knots)          |


Example Response
+QGPSLOC: 092536.0,1304.5678,N,07735.9876,E,1.2,50.0,1,0.9,0.8,0.7

Time Parsing

UTC Time:

092536 → 09:25:36

Coordinate Conversion
Latitude Conversion
1304.5678
Degrees = 13
Minutes = 04.5678
Decimal = 13 + (4.5678 / 60)

Longitude Conversion
07735.9876
Degrees = 77
Minutes = 35.9876
Decimal = 77 + (35.9876 / 60)

Decimal Output Example
Latitude  : 13.076130
Longitude : 77.599796

Notes

GPS fix may take several minutes on cold start

Ensure GPS antenna is connected

Outdoor environment improves fix speed
