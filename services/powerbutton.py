#!/usr/bin/env python
"""
Shutdown script, that waits for a falling edge on a specified GPIO pin
"""
import os

try:
    from RPi import GPIO
except RuntimeError:
    print("Error importing RPi.GPIO, need sudo?")
POWER_BUTTON_PIN = 27
GPIO.setmode(GPIO.BCM)
GPIO.setup(POWER_BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

print('Monitoring shutdown button for falling edge')
while True:
    GPIO.wait_for_edge(POWER_BUTTON_PIN, GPIO.FALLING)
    print('Shutdown button pressed, shutting down, farewell')
    os.system('systemctl poweroff')
