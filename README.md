# GC9x DC power meter TTL readout for Arduino

Adapted version of https://github.com/tiefpunkt/gc9x-reader for Arduino. See https://github.com/tiefpunkt/gc9x-reader/blob/master/README.md for detailled information on the protocol etc. Support GC90 and GC91 power meters, other models of the GC9x have not been tested yet.

Uses Software Serial library on Pins 8 (RX) and 9 (TX). Should work on pretty much any Arduino IDE supported board.

If you want to transmit your readings using LoRaWAN, check out this project, which is based on this work: https://github.com/makervan/powermeter-lorawan-connector
