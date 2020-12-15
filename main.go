package main

import (
  "fmt"
  "log"
  "net/http"
  "github.com/gorilla/websocket"
  "github.com/jacobsa/go-serial/serial"
)

var upgrader = websocket.Upgrader{
  ReadBufferSize: 1024,
  WriteBufferSize: 1024,
}


func sendArduino(msg string) {
  options:= serial.OpenOptions {
    PortName: "/dev/ttyACM0",
    BaudRate: 9600,
    DataBits: 8,
    StopBits: 1,
    MinimumReadSize: 4,
  }

  port, err := serial.Open(options)
  if err != nil {
    log.Fatalf("serial.Open: %v", err)
  }

  defer port.Close()

  b := []byte(msg)
  n, err := port.Write(b)
  if err != nil {
    log.Fatalf("port.Write: %v", err)
  }

  fmt.Println(n, " bytes wrote to Arduino")
}

func reader(conn *websocket.Conn) {
  for {
    messageType, p, err := conn.ReadMessage()
    if err != nil {
      log.Println(err)
      return
    }
    fmt.Println(string(p))
    sendArduino(string(p))

    if err := conn.WriteMessage(messageType, p); err != nil {
      log.Println(err)
      return
    }
  }
}

func homePage(w http.ResponseWriter, r *http.Request) {
  fmt.Fprintf(w, "Home Page")
}

func wsEndpoint(w http.ResponseWriter, r *http.Request) {
  upgrader.CheckOrigin = func(r *http.Request) bool {return true}

  ws, err := upgrader.Upgrade(w, r, nil)
  if err != nil {
    log.Println(err)
  }

  log.Println("Client Connected")
  err = ws.WriteMessage(1, []byte("Hi Client!"))
  if err != nil {
    log.Println(err)
  }

  reader(ws)
}

func setupRoutes() {
  http.HandleFunc("/", homePage)
  http.HandleFunc("/ws", wsEndpoint)
}

func main() {
  fmt.Println("Hello World")
  setupRoutes()
  log.Fatal(http.ListenAndServe(":8080", nil))
}
