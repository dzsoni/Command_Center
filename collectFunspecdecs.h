#ifndef COLLECTFUNSPECDECS_H
#define COLLECTFUNSPECDECS_H

/*
if you don't need any collectFun, please define NO_NEED_XXX_COLLECTFUN in your compile option in the platformio.ini 
[env]
build_flags = -D NO_NEED_XXX_COLLECTFUN


 NO_NEED_RELAY_COLLECTFUN
 NO_NEED_RELAYARRAY_COLLECTFUN
 NO_NEED_NONBLOCKINGDALLASARRAY_COLLECTFUN
 NO_NEED_COMMANDCENTER_COLLECTFUN
 NO_NEED_MQTTCOMMAND_COLLECTFUN
 NO_NEED_WIFIMANAGER_COLLECTFUN
 NO_NEED_CONTROLLOGICMANAGER_COLLECTFUN
 ..etc
*/

#ifndef NO_NEED_RELAY_COLLECTFUN
#include "Relay_collectFun.h"                   //relay: https://github.com/dzsoni/Relay
#endif 

#ifndef NO_NEED_RELAYARRAY_COLLECTFUN
#include "RelayArray_collectFun.h"              //relayarray: https://github.com/dzsoni/Relay  
#endif 

#ifndef NO_NEED_NONBLOCKINGDALLASARRAY_COLLECTFUN 
#include "NonBlockingDallasArray_collectFun.h"  //https://github.com/dzsoni/NonBlockingDallasArray
#endif 

#ifndef NO_NEED_COMMANDCENTER_COLLECTFUN
#include "CommandCenter_collectFun.h"
#endif 

#ifndef NO_NEED_MQTTCOMMAND_COLLECTFUN
#include "MQTT_Command_collectFun.h"
#endif

#ifndef NO_NEED_WIFIMANAGER_COLLECTFUN
#include "WifiManager_collectFun.h"
#endif 

#ifndef NO_NEED_CONTROLLOGICMANAGER_COLLECTFUN
#include "ControlLogicManager_collectFun.h"
#endif

#endif 
