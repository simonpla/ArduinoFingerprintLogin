## Log in with your arduino
Using a fingerprint sensor, you can log in into any website you want. You just have to adjust the arduino code for your needs.

## How it works
The Add-on linked here sends the Website you are visiting now over websockets to the Go code ```main.go```.
For recieving the data from websockets, it uses the [library](https://www.github.com/gorilla/websocket "Link to gorilla's library") ```websocket``` by gorilla.
The recieved data will be transfered to the Arduino using jacobsa's [library](https://www.github.com/jacobsa/go-serial "Link to jacobsa's library")  ```go-serial```.
After that, the Arduino recognizes which website you are visiting and if he knows that one, he will type in the username and password using ```Keyboard.h```.
For that you will need an Arduino Pro Mini or Arduino Leonardo.

## Installation
1. Install the browser extension
2. If you use Linux, use the install script. If using Windows, download the executable, press Windows-Key + R and type ```shell:startup```. Copy the executable file in there.
3. Connect the Fingerprint sensor to the Arduino and save your Fingerprint as ```1``` with the ```EnrollFingerprint``` example.
4. Adjust the Arduino code to your needs and upload it to an Arduino Leonardo / Pro Micro.
