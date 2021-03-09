#!/bin/bash

echo $PATH

arch=$(dpkg --print-architecture)
case "$arch" in
  amd64)
        echo Architecture: amd64
        wget --no-check-certificate https://cdn.statically.io/gh/simonpla/ArduinoFingerprintLogin/main/releases/0.1/linux/main_amd64.afplogin
        ;;
  i386)
        echo Architecture: i386
        wget --no-check-certificate https://cdn.statically.io/gh/simonpla/ArduinoFingerprintLogin/main/releases/0.1/linux/main_386.afplogin
        ;;
  armhf)
        echo Architecture: armhf
        wget --no-check-certificate https://cdn.statically.io/gh/simonpla/ArduinoFingerprintLogin/main/releases/0.1/linux/main_arm.afplogin
        ;;
  arm64)
        echo Architecture: arm64
        wget --no-check-certificate https://cdn.statically.io/gh/simonpla/ArduinoFingerprintLogin/main/releases/0.1/linux/main_arm64.afplogin
        ;;
esac
mv *.afplogin afplogin
cp afplogin /usr/local/bin
rm afplogin
chmod +x /usr/local/bin/afplogin
echo File installed...
if systemctl --version ; then
    echo systemctl recognized
    wget --no-check-certificate https://cdn.statically.io/gh/simonpla/ArduinoFingerprintLogin/main/afplogin.service
    cp afplogin.service /etc/systemd/system
    systemctl enable afplogin.service
    rm afplogin.service
else
    echo No systemctl there: There is currently no support for your init manager. Please open a Github issue or Pull Request.
fi
echo "Finished!"
