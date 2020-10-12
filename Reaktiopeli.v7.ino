#include <LiquidCrystal.h>      //LCD
#include <SPI.h>
#include <WiFi101.h>


const int pushButton = 2;   //arduino pinni 2
const int pushButton2 = 3;  //arduino pinni 3
const int pushButton3 = 4;  //arduino pinni 4
const int ledPin = 1;       //arduino pinni 1

char ssid[] = "koulu";         // your network SSID (name)
char pass[] = "koulukoulu";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;              // your network key Index number (needed only for WEP)


int status = WL_IDLE_STATUS;

WiFiServer server(80);


LiquidCrystal lcd(6,7,8,9,10,11);   //LCD
int player1score = 0;
int player2score = 0;
int randomnumb;
int randomhold;
int laskuri = 0;
bool kierros = false;
bool kierrosSPAM = false;
bool toisto = true;
bool start = true;
unsigned long previousMillis = 0;
unsigned long reactionTime = 0;
String player1 = "";
String player2 = "";
String player1_new = "";
String player2_new = "";

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin(20,4);   //LCD


  randomSeed(analogRead(0));
  randomnumb = random(2500,5000);
  
  Serial.begin(9600);

   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWiFiStatus();
}

// the loop routine runs over and over again forever:
void loop() {
    // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line

    String line = "";
    String line2 = "";
    bool lukuLippu = 0;
    bool lukuLippu2 = 0;
    String p1 = "";
    String p2 = "";


    
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        line += c;
        line2 += c;
        Serial.write(c);

        
        if(c == '?') lukuLippu = 1;
        if(( c == ' ' || c == '\n' || c == '&' ) && lukuLippu) lukuLippu = 0;

          if(lukuLippu) {
          p1 += c;
          }   


        if(c == '?') lukuLippu2 = 1;
        if(( c == ' ' || c == '\n' ) && lukuLippu2) lukuLippu2 = 0;

          if(lukuLippu2) {
          p2 += c;
          }   

        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println(F("Connection: close"));  // the connection will be closed after completion of the response
          client.println(F(""));
          client.println(F("<!DOCTYPE HTML>"));
          client.println(F("<html>"));
          // output the value of each analog input pin
          client.println(F("<head> \
  <title>Harjoitusty&ouml;</title> \
  <meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" /> \
    <style> \
        html \
        { \
          overflow: hidden; \
          height: 100%; \
         background-image: url('http://www.powerpointhintergrund.com/uploads/blurry-background-25.jpg');\ 
          background-repeat: no-repeat; \
          background-size: cover;\
        \
        }           \
        body \
        { \
          height: 99%; \
          margin: 0; \
          padding: 0; \
          text-align: center; \
        } \
        #input-submit{ \
          background-color: #80BE83; \
        } \
        "));
        client.println(F("\
        #mainContentArea \
        { \
          margin: 0 auto 0 auto;  \
          display: table;  \
          height: 100%;   \
          position: relative;  \
          overflow: hidden;  \
          width: 600px; \
        }"));
        client.println(F("\
        .link,.linkActive \
        { \
        width:95px; \
        margin-right:10px; \
        float: left; \
        margin-top:24px; \
        text-align:center; \
        font-family:Georgia,  \"Times New Roman\", Times, serif; \
        position:relative; bottom:2px; \
        background-color: rgb(231, 237, 248); \
        border-radius: 30px 30px 0px 0px; \
        } \
        .link:hover \
        { \
          background-color: #8A8A8A; \
        }"));
        client.println(F("a{\
        text-decoration:none;\
        }\
        .link a{\
        font-family:Arial, Helvetica, sans-serif;\
        font-size:13px;\
        font-weight:bold;\
        font-color: black;\
        }\
        a:visited, a:link{color: black;}\
        #linkGroup\
        {\
        margin-right:10px;\
        height:40px;\
        width:600px;\
        } \
        \
        ")); \
        client.println(F(" \
        @media screen and (min-width: 480px) { \
        #title\
        { \
        width:230px; \
        height:40px;  \
        margin-right:20px; \
        margin-top:15px; \
        font-family:Verdana, Arial, Helvetica, sans-serif; \
        font-size:20px; \
        font-weight:bold; \
        text-align:center; \
        float:left; \
        } \
        }"));
        client.println(F("\
        .contentTitle \
        { \
        font-family:Verdana, Arial, Helvetica, sans-serif; \
        color:#213E74; \
        font-size:24px;  \
        text-align: center; \
        margin-bottom:12px; \\
        width:573px; \
        }\
        .pageContent \
        { \
        font-family: Arial, Helvetica, sans-serif; \
        color:#000000; \
        font-size:12px; \
        margin-left:20px; \
        margin-right:20px; \
        width:560px; \
        } \
        #blueBox\
        { \
          position: absolute; \
          vertical-align: middle; \
          background-color:rgb(231, 237, 248); \
          width:600px; \
          clear:both; \
          border-radius: 25px; \
        }"));
        client.println(F("\
        #contentBox \
        { \
        margin-top:25px; \
        } \
        html, body { \
        text-align: center; \
        } \
        p {text-align: left;} \
        form { \
           max-width: 600px; \
           text-align: center; \
           margin: 20px auto; \
        }  \
        .half { \
          float: left; \
          width: 48%; \
          margin-bottom: 1em;\
        }\
        \
        .right { width: 50%; }\
        \
        .left {\
             margin-right: 2%; \
        }\
        \
        @media screen and (max-width: 480px) {\
        \
        #footer p{padding-left:10px;}\
          #title\
          {\
          width:230px;\
          margin-top:15px;\
          font-family:Verdana, Arial, Helvetica, sans-serif;\
          font-size:20px;\
          font-weight:bold;\
          }\
          .pageContent h1{margin-left: -320px; font-size:1.6em;} \
        \
          .link,.linkActive\
          {\
          width:85px;\
          float: left;\
          margin-top:24px;\
          text-align:center;\
          font-family:Georgia, \"Times New Roman\", Times, serif;\
          position:relative; bottom:2px;\
          background-color: rgb(231, 237, 248);\
          border-radius: 0px 0px 0px 0px;\
          }\
        \
          #blueBox\
          {\
            position: absolute;\
            vertical-align: middle;\
            background-color:rgb(231, 237, 248);\
            width:600px;\
            clear:both;\
            border-radius: 0px;\
          }\
        \
          .half {\
            margin-left:20px;\
            margin-top:25px;\
            margin-bottom: 1em;\
            \
          }\
        \
            #footer {\
        \
              margin-right:340px;\
            }\
        \
            .contentTitle\
            {\
            font-family:Verdana, Arial, Helvetica, sans-serif;\
            color:#213E74;\
            font-size:24px;\
            margin-left: -150px;\
            margin-bottom:12px;\
            width:573px;\
            }\
        \
        \
        }\
        </style>\
  </head>")); 
client.println(F("<body> \
<div id=\"mainContentArea\">\
  <div id=\"contentBox\">\
               <div id=\"title\">Harjoitusty&ouml;\
               </div>\
                               <div id=\"linkGroup\">\
          <div class=\"link\"> <u> <a>Home</a> </u> </div>\
            <div class=\"link\"><a href=\"#\">Leaderboard</a></div>\
            <div class=\"link\"><a href=\"https://reactiongame.github.io/\" >How to play</a></div>\
        </div>\
        </div>\
        <div id=\"blueBox\"> \
          <div id=\"header\"></div><br>\
          <div class=\"contentTitle\">Welcome to Play.</div>"));
          client.println(F("<div class=\"pageContent\">\
              <h1>Insert player names to play.</h1>\
              <form class=\"cf\" method=\"get\">\
                <div class=\"half left cf\">\
                 <input style=\"width: 17em;\" name=\"name1\" type=\"text\" id=\"Name\" placeholder=\" Player 1 (max lenght 14)\">\
                  <br><br><br>\
                 <input style=\"width: 17em;\" name=\"name2\" type=\"text\" id=\"Name2\" placeholder=\" Player 2 (max lenght 14)\">\
                </div>\
                <div class=\"half right cf\">\
                    <input style=\"    width: 20em;  height: 5em;\" type=\"submit\" value=\"Submit\" id=\"input-submit\" onclick=\"speech()\">\
                </div>  \
                <script>\
                  function speech(){ \
                      if('speechSynthesis' in window){\
                  var speech = new SpeechSynthesisUtterance('Player names inserted successfully');\
                  speech.lang = 'en-US';\
                  window.speechSynthesis.speak(speech);\
                  }\
              }\
              </script>\
              </form>\
            </div>\
              <div id=\"footer\">\
                <marquee direction=\"left\" behavior=\"slide\" ><p style=\"text-align: center;\" >made by: Jonas Terttula, Henri Tulus &amp; Janne Kytölä</p></marquee>\
              </div>\
        </div>\
      </div>\
    </div>\
</body>"));  
          client.println(F("</html>"));
          break;
        }
             
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          //Serial.print(p1);
          if(p1.indexOf("name1") > 0) {
            Serial.println(p1.substring(7));
          }
          line = "";
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(1);
    player1 = (p1.substring(7));
    player1.remove(player1.length(),1);
    int muuttuja = player1.length() + 14;
    player2 = (p2.substring(muuttuja));
    player2.remove(player2.length()-1,1);
    if(player1_new != player1 || player2_new != player2)
      {
      player1score = 0;
      player2score = 0;  
      }
    player1_new = player1;
    player2_new = player2;
    // close the connection:
    client.stop();
    Serial.println("client disconnected");

    if(player1.length()>20)     //ONLY COUNTS 14 FIRST LETTERS
    {
      int jotain = player1.length() - 14;
      player1.remove(14, jotain);  
    }

    if(player2.length()>20)
    {
      int jotain2 = player2.length() - 14;
      player2.remove(14, jotain2);  
    }

    if(player1.length()<1){     //MAKES UNNAMED PLAYERS NAMED
      player1 = "Player1";
    }
    if(player2.length()<1){
      player2 = "Player2";
    }
  }

  
  unsigned long currentMillis = millis();
  // read the input pin:

  if (kierros == false)
  {
    if (kierrosSPAM == false)
    {
      delay (1500);
      if(start == true)
      {
        lcd.print("Press ON to start");   //LCD
        lcd.setCursor(0,1);
        start = false;
      }
      Serial.println("------------------");
      Serial.println("Press ON to start.");
      Serial.println("------------------");
      
      kierrosSPAM = true;
    }
    int buttonState3 = digitalRead(pushButton3);    //lukee ON/OFF buttonin painalluksen
    if (buttonState3 == 0)
    {
      kierros = true; 
      lcd.clear(); 
    }
  }

  
  if(kierros == true)
  {
      if(toisto == true){
        delay(randomnumb); 
        digitalWrite(ledPin, HIGH);
        Serial.println("GO");
        randomSeed(analogRead(0));
        randomhold = randomnumb;
        randomnumb = random(2500,5000);
        toisto = false;
        previousMillis = currentMillis;
      }
    
    
    
      //Serial.println(randomnumb);
      
      int buttonState = digitalRead(pushButton);
      int buttonState2 = digitalRead(pushButton2);
      // print out the state of the button:
      // Serial.println(buttonState);
      
      if(buttonState == 0){       //PLAYER 1 -----------------------------
        lcd.clear();
        reactionTime = currentMillis - previousMillis - randomhold;
        player1score = player1score + 1;
        if(reactionTime > 5000000)
        {
          player1score = player1score -2 ;  
          lcd.setCursor(0,0);
          lcd.print(player1);
          lcd.setCursor(0,1);
          lcd.print("cheated!");
          lcd.setCursor(0,2);
          lcd.print(player1score);
          lcd.print(" points");
          Serial.print(player1);
          Serial.println(" HAS CHEATED!");
          Serial.println("Huijasit ja menetit pisteen!");
        }
        else {
          lcd.setCursor(0,0);
          lcd.print(player1);
          lcd.print(" wins!");
          lcd.setCursor(0,2);
          lcd.print(player1score);
          lcd.print(" points");
          lcd.setCursor(0,1);
          lcd.print("Aika: ");
          lcd.print(reactionTime);
          lcd.print("ms");
          Serial.print(player1);
          Serial.println(" WINS!");
          Serial.print(player1);
          Serial.print(" reaction time is ");
          Serial.print(reactionTime);   //jos reakoi liian nopeasti tulos väärin
          Serial.println("ms");
        }
        Serial.print("score is ");
        Serial.println(player1score);
        digitalWrite(ledPin, LOW);
        toisto = true;
        laskuri++;
        kierrosSPAM = false;
        
      } else if(buttonState2 == 0){     //PLAYER 2 --------------------------
        lcd.clear();
        reactionTime = currentMillis - previousMillis - randomhold;
        player2score = player2score + 1;
        if(reactionTime > 5000000)
        {      
          player2score = player2score -2 ;  
          lcd.print(player2);
          lcd.setCursor(0,1);
          lcd.print("cheated!");
          lcd.setCursor(0,2);
          lcd.print(player2score);
          lcd.print(" points");
          Serial.print(player2);
          Serial.println(" HAS CHEATED!");
          Serial.println("Huijasit ja menetit pisteen!");
        }
        else {
          lcd.print(player2);
          lcd.print(" wins!");
          lcd.setCursor(0,2);
          lcd.print(player2score);
          lcd.print(" points");
          lcd.setCursor(0,1);
          lcd.print("Aika: ");
          lcd.print(reactionTime);
          lcd.print("ms");
          Serial.print(player2);
          Serial.println(" WINS!");
          Serial.print(player2);
          Serial.print(" reaction time is ");
          Serial.print(reactionTime);   //jos reakoi liian nopeasti tulos väärin
          Serial.println("ms");
        }
        Serial.print("Player2 score is ");
        Serial.println(player2score);
        digitalWrite(ledPin, LOW);
        toisto = true;
        laskuri++;
        kierrosSPAM = false;
      }
    if(laskuri == 3)    //kierroksia 3
    {
      kierros = false;  
      laskuri = 0;
      lcd.setCursor(0,4);
      lcd.print("Press ON to restart");
    }
  }
  
  delay(1);        // delay in between reads for stability
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

