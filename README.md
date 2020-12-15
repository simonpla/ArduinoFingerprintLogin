## Log in with your arduino
Using a fingerprint sensor, you can log in into any website you want. You just have to adjust that in the arduino code.

## How it works
The Add-on linked here sends the Website you are visiting now over websockets to the Go code ```main.go```.
For recieving the data from websockets, it uses the library ```websocket``` by gorilla.
The recieved data will be transfered to the Arduino using jacobsa's library ```go-serial```.
After that, the Arduino recognizes which website you are visiting and if he knows that one, he will type in the username and password using ```Keyboard.h```.
For that you will need an Arduino Pro Mini or Arduino Leonardo.
