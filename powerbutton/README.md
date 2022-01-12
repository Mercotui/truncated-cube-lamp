# Powerbutton service

The powerbutton service allows a person to shutdown the lamp using a physical button.

It requires the following dependency:

```bash
apt install python3 python-is-python3 python3-rpi.gpio
```

Then copy the files over and enable the service:

```bash
cp powerbutton.py /usr/local/bin/
cp powerbutton.service /etc/systemd/system/
systemctl enable powerbutton
```
