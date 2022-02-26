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
                        TYBALT, //1
                        MERCUTIO, //2
                        ROMIBALCONY, //3
                        JULIET,  //4
                        FRIARLAURENCE //5
                    };

ACTOR_SELECT currentActor = ROMIFIGHT; //Change this initalization when uploading to different robots.

FriarLaurence friarLaurence;  //Object declarations for full robots.
Juliet juliet;
Tybalt tybalt;
Mercutio mercutio;
RomiFight romiFight;
RomiBalcony romiBalcony;

bool runScene = false; //Used as a wifi trigger to begin the scene.

void mqttCallback(char* topic, byte *payload, unsigned int length)  {

    if(String(topic) == "team20/sceneStart") {
        if(length) {
            if(payload[0] == '0') runScene = false;
            if(payload[0] == '1') runScene = true; //Set manually through the MQTT dashboard
        }
    }    
    if(String(topic) == "team20/mercutioDead") {
        if(length) {
            if(payload[0] == '0') {
                mercutio.mercutioDead = false; 
                romiFight.mercutioDead = false; 
                tybalt.mercutioDead = false;
                }
            if(payload[0] == '1') {
                mercutio.mercutioDead = true; 
                romiFight.mercutioDead = true; 
                tybalt.mercutioDead = true;
                }
            }
        }
    if(String(topic) == "team20/tybaltDead") {
        if(length) {
            if(payload[0] == '0') {
                romiFight.tybaltDead = false;
                tybalt.tybaltDead = false;
            if(payload[0] == '1') {
                romiFight.tybaltDead = true;
                tybalt.tybaltDead = true;
                }
            }
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

    case ROMIFIGHT: romiFight.init(); break;
    case TYBALT: tybalt.init(); break;
    case MERCUTIO: mercutio.init(); break;
    case ROMIBALCONY: romiBalcony.init(); break;
    case JULIET: juliet.init(); break;
    case FRIARLAURENCE: friarLaurence.init(); break;
    default: break;

    }

  setup_mqtt();   //also calls setup_wifi() 
  reconnect();
  client.setCallback(mqttCallback);
  client.subscribe("team20/sceneStart");
  client.subscribe("team20/mercutioDead");
  client.subscribe("team20/tybaltDead");
  client.subscribe("team20/julietTopRamp");
  client.subscribe("team20/julietBottomRamp");
  client.subscribe("team20/atFriar");
  client.subscribe("team20/friarAddressed");

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