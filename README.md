# Toggle external relay if internet connection lost

### Arduino_NetworkConnection_Reboot-router.ino
Once I had a 4G router with sim-card that needed to reboot once the operator "limited" the connection due to inactivity. Instead of reboot the router manually each day, I connected the router to an Arduino relay that cut the power to the router in case of ping lost. One major issue with this code is that the code will keep rebooting as long as internet is lost, which means it will reboot the router forever in whorst case.

## Extra

### Arduino_UART_SerialRead
Read serial data
