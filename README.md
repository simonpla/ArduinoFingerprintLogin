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
2. You can build the file ```main.go``` with ```go build``` from source or download the compiled file for your operating system and architecture.
   In linux you have run ```chmod +x main_amd64``` (change the name for the architecture you downloaded) and execute the file with ```./main_amd64``` (again, change             the name if you have to). In Windows just execute the file.
 3. Make the program start every time you boot
