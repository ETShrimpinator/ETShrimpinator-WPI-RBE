#include <Arduino.h>
#include <RBE-200n-Lib.h>
#include <Robot.h>
#include <MQTT.h>
#include <RomiFight.h>
#include <Tybalt.h>
#include <Mercutio.h>
#include <RomiBalcony.h>
#include <Juliet.h>
#include <FriarLaurence.h>

    enum ACTOR_SELECT {   
                        ROMIFIGHT, //0
                        TYBALT,
                        MERCUTIO,
                        ROMIBALCONY,
                        JULIET, 
                        FRIARLAURENCE, 
                        NONE,
                    };

    ACTOR_SELECT currentActor = NONE;

FriarLaurence friarLaurence;
RomiFight romiFight;
Tybalt tybalt;
Mercutio mercutio;
RomiBalcony romiBalcony;
Juliet juliet;

bool runScene = false;

void mqttCallback(char* topic, byte *payload, unsigned int length)  {

    if(String(topic) == "team20/sceneStart") {
        if(length) {
            if(payload[0] == '0') runScene = false;
            if(payload[0] == '1') runScene = true;  //Time to fight...
        }
    }    
    if(String(topic) == "team20/mercutioDead") {
        if(length) {
            if(payload[0] == '0') mercutio.tybaltReady = false;
            if(payload[0] == '1') mercutio.tybaltReady = true;
        }
    }
    if(String(topic) == "team20/tybaltDead") {
        if(length) {
            if(payload[0] == '0') tybalt.romiFightReady = false;
            if(payload[0] == '1') tybalt.romiFightReady = true;
        }
    }
    if(String(topic) == "team20/julietTopRamp") {
        if(length) {
            if(payload[0] == '0')  romiBalcony.julietReady = false;
            if(payload[0] == '1')  romiBalcony.julietReady = true;
        }
    }
    if(String(topic) == "team20/julietBottomRamp") {
        if(length) {
            if(payload[0] == '0') romiBalcony.julietReady = false;
            if(payload[0] == '1') romiBalcony.julietReady = true;
        }
    }
    if(String(topic) == "team20/atFriar") {
        if(length) {
            if(payload[0] == '0') friarLaurence.coupleReady = false;
            if(payload[0] == '1') friarLaurence.coupleReady = true;
        }
    }
    if(String(topic) == "team20/friarAddressed") {
        if(length) {
            if(payload[0] == '0') juliet.friarReady = false;
            if(payload[0] == '1') juliet.friarReady = true;
        }
    }
}
    

void setup() {

  Serial.begin(115200); //For "standard" serial communication
  Serial2.begin(115200); //For UART 

  delay(500);

switch(currentActor) {

    case ROMIFIGHT:
        romiFight.init();
        break;
    case TYBALT:
        tybalt.init();
        break;
    case MERCUTIO:
        mercutio.init();
        break;
    case ROMIBALCONY:
        romiBalcony.init();
        break;
    case JULIET:
        juliet.init();
        break;
    case FRIARLAURENCE:
        friarLaurence.init();
        break;
    default:
        break;

    }

  setup_mqtt();   //also calls setup_wifi() 
  reconnect();
  client.setCallback(mqttCallback;
  client.subscribe("dest");

}

void loop() {

    client.loop();  //run mqtt loop
    if (!client.connected()) reconnect();
    
    if (runScene == true) {

  switch(currentActor) {

    case ROMIFIGHT:
        romiFight.runStateMachine();
        break;
    case TYBALT:
        tybalt.runStateMachine();
        break;
    case MERCUTIO:
        mercutio.runStateMachine();
        break;
    case ROMIBALCONY:
        romiBalcony.runStateMachine();
        break;
    case JULIET:
        juliet.runStateMachine();
        break;
    case FRIARLAURENCE:
        friarLaurence.runStateMachine();
        break;
    default:
        break;

        }

    }

}

        //int distance = robot.checkRangefinder(); //Ask Lewin about this.
        //if (robot.checkRangeFinder()) int distance = robot.checkRangefinder;

        //Run expereiment to see if pose updates when setting motor efforts directly through handle rangefinder functions 
    