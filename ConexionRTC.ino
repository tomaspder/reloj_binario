#include <SPI.h>
#include <Ethernet.h>
#include <TimeLib.h>
#include <NTPClient.h>

byte mac[] = {
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,2);
EthernetServer server(80);
NTPClient timeClient(ntpUDP, "http://ntp.thetimenow.org", utcOffsetInSeconds);

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  EthernetClient cliente = server.available(); 
  if (cliente) {
    boolean currentLineIsBlank = true;
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        if (c == '\n' && currentLineIsBlank) { 
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");  
          cliente.println("Connection: close"); 
          cliente.println();
          cliente.println("<!DOCTYPE HTML>"); 
          cliente.println("<html>");
          cliente.println("<HEAD>");
          cliente.println("<TITLE>Reloj Binario</TITLE>");
          cliente.println("</head>");
          cliente.println("<body>");
          cliente.println("<h1>Simulación con LEDS</h1>");
          cliente.println("<style>.led{display: inline-block;width: 20px;height: 20px;border-radius: 50%;background-color: #333;transition: all .25s ease-in;}.uno{background-color: #f00;box-shadow: 0 0 15px 1px #f00;transition: all .1s ease-out;}</style>");
          cliente.println("<div id='binario'><div id='horas'><div class='led horas'></div><div class='led horas'></div><div class='led horas'></div><div class='led horas'></div><div class='led horas'></div></div><div id='minutos'><div class='led minutos'></div><div class='led minutos'></div><div class='led minutos'></div><div class='led minutos'></div><div class='led minutos'></div><div class='led minutos'></div></div><div id='segundos'><div class='led segundos'></div><div class='led segundos'></div><div class='led segundos'></div><div class='led segundos'></div><div class='led segundos'></div><div class='led segundos'></div></div></div>");
          cliente.println("<h2>Tiempo real:</h2>");
          cliente.println(timeClient.update(););
          cliente.println("<script>var segundosDiv=document.getElementById('segundos');var minutosDiv=document.getElementById('minutos');var horasDiv=document.getElementById('horas');function lecturaEscritura(){actual=new Date();horas=actual.getHours().toString(2).split('');minutos=actual.getMinutes().toString(2).split('');segundos=actual.getSeconds().toString(2).split('');for (var a=horas.length; 5 > a; a++){horas.unshift('0');}for(var a = minutos.length; 6 > a; a++){minutos.unshift('0');}for(var a=segundos.length; 6 > a; a++){segundos.unshift('0');}for(i in segundos){if(segundos[i]=='1'){segundosDiv.children[i].classList.add('uno');}else{segundosDiv.children[i].classList.remove('uno');}}for(i in minutos){if(minutos[i]=='1'){minutosDiv.children[i].classList.add('uno');}else{minutosDiv.children[i].classList.remove('uno');}}for(i in horas){if(horas[i]=='1'){horasDiv.children[i].classList.add('uno');}else{horasDiv.children[i].classList.remove('uno');}}}window.setInterval(lecturaEscritura,200);<script/>");
          
          cliente.println("</html>");
          break;
        }
        if (c == '\n') {
           currentLineIsBlank = true;
        } 
        else if (c != '\r') {
           currentLineIsBlank = false;
        }
      }
    }
   delay(15);
   cliente.stop();
  }
}
