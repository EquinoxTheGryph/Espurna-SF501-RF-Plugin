
#ifdef _PLUGIN_SF501

/*
A Simple Way To Bind Virtual Relays To Send Commands To External Flamingo SF501 Relays Via RF 433MHZ19

Plugin Copyright

This file is part of Espurna-SF501-RF-Plugin.

    Espurna-SF501-RF-Plugin is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Espurna-SF501-RF-Plugin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Espurna-SF501-RF-Plugin.  If not, see <https://www.gnu.org/licenses/>.
*/


//*---------------------------------------------------------------------------
//* Plugin includes
//*---------------------------------------------------------------------------
#include <EEPROM.h>
#include <Ticker.h>
#include <ArduinoJson.h>
#include <vector>
#include <functional>
#include <sf501-remote.h>

//*---------------------------------------------------------------------------
//* Default defines
//*---------------------------------------------------------------------------
//* Set the Remote ID
#ifndef RF_REMOTE_ID
#define  REMOTE_ID 0
#endif
//* Set the pin that is connected to the RF Transmitter
#ifndef RF_OUTPUT_PIN
#define  RF_OUTPUT_PIN 5
#endif
//* Set At Which ID the code should watch on
#ifndef RF_RELAY_START
#define RF_RELAY_START 2
#endif
//* Set the Maximum relays the code can control
#ifndef RF_MAX_RELAYS
#define RF_MAX_RELAYS 4
#endif



//*----------------------------------------------------------------------------
//* Private
//*----------------------------------------------------------------------------
//*----------------------------------------------------------------------------
//* Plugin globals
//*----------------------------------------------------------------------------

//* Determine Whether the plugin is enabled or not
bool _plugin_enabled = false;

//* Store an array of states
bool _last_relay_state[RF_MAX_RELAYS];

//unsigned long _pluginReportInterval = 1000 * PLUGIN_REPORT_EVERY;
//unsigned long _pluginLastUpdate = 0;
//unsigned long _pluginCounter = PLUGIN_PARAMETER_1;

//*----------------------------------------------------------------------------
//* Plugin helper functions
//*----------------------------------------------------------------------------

//* Initialize the Remote Library
Sf501Remote remote;


//* Initializes the array of states
void initRelayStatus() {
    for (int i = 0; i < RF_MAX_RELAYS; i++) {
        _last_relay_state[i] = relayStatus(RF_RELAY_START + i);
    }
}

//* Handles any changes on the virtual switches
void checkRelayStatus() {
    for (int i = 0; i < RF_MAX_RELAYS - RF_RELAY_START + 1; i++) {
        //* A Switch has been changed! handle it!
        if (relayStatus(RF_RELAY_START + i) != _last_relay_state[i]) {
            //* Save the new state for checking later
            bool new_state = relayStatus(RF_RELAY_START + i);
            _last_relay_state[i] = new_state;
            //* Now Send the command to the relays! (Add 1 to i, because i think 0 will act like a master switch?)
            remote.sendCommand(RF_REMOTE_ID, i + 1, new_state);
            DEBUG_MSG_P(PSTR("[PLUGIN] Set Remote Relay #%u To %d\n"), i + 1, new_state ? PSTR("ON") : PSTR("OFF"));
        }
    }
}

//* ---------------------------THE FOLLOWING WAS ADDED BY THE EXAMPLE---------------------
//* If API support needed
//* API register helper function
//*-----------------------------
#if WEB_SUPPORT
    //* register api functions
    //* apiRegister(key, _getFunction, _putFunction);
    //* this is API registraion to enable disable the plugin
    //* use this as template to create additional API calls for the plugin
    void _pluginSetupAPI() {
          char key[15];
          snprintf_P(key, sizeof(key), PSTR("%s"), MQTT_TOPIC_SF501);
          apiRegister(key, [](char * buffer, size_t len) {
               //snprintf_P(buffer, sizeof(buffer), PSTR("Ok - %d"), _pluginCounter);
               snprintf_P(buffer, len, PSTR("%d"), _plugin_enabled ? "ON" : "OFF");
               DEBUG_MSG_P(PSTR("[PLUGIN_SF501] API call return: (%s)\n"), buffer);},
               [](const char * payload) {
                   unsigned char value = relayParsePayload(payload);
                   if (value == 0xFF) {
                       DEBUG_MSG_P(PSTR("[PLUGIN_SF501] Wrong payload (%s)\n"), payload);
                       return;
                   }
                   _plugin_enabled = (value == 1);
                   setSetting("PLG1_EN", _plugin_enabled);
                   //snprintf_P(buffer, len, PSTR("%d"), _plugin_enabled ? "ON" : "OFF");
                   //DEBUG_MSG_P(PSTR("[PLUGIN_SF501] API call return: (%s)\n"), buffer);
                });
	    }
#endif

//* If terminal Terminal commands needed
//* Plugin terminal commands helper function
//*-----------------------------------------
#if TERMINAL_SUPPORT
      void _pluginInitCommands() {
          //* Register Terminal commad to turn on/off the plugin
          //* use this as template to create additional plugin terminal commands
          settingsRegisterCommand(F("PLUGIN_SF501"), [](Embedis* e) {
                  if (e->argc == 0) {
                      DEBUG_MSG_P(PSTR("Pluin1 Status: %s\n"), _plugin_enabled ? "ON" : "OFF");
                      DEBUG_MSG_P(PSTR("Send 0/1 to enable/disable\n"));
                      DEBUG_MSG_P(PSTR("+OK\n"));
                      return;
                  }
                  _plugin_enabled = (String(e->argv[1]).toInt() == 1);
                  setSetting("PLG1_EN", _plugin_enabled);
                  DEBUG_MSG_P(PSTR("Pluin1 Set Status: %s\n"), _plugin_enabled ? "ON" : "OFF");
                  DEBUG_MSG_P(PSTR("+OK\n"));
              });

      }
#endif

//* end of helper functions
//*----------------------------------------------------------------------------

//*----------------------------------------------------------------------------
//* Plugin setup
//*----------------------------------------------------------------------------
void pluginSF501Setup() {
    //*    plugin setup code
    //* pluginSF501Setup() is called by custom.h - espurna plugin entry point

    _plugin_enabled = getSetting("PLG1_EN", PLUGIN_SF501_ENABLE).toInt() == 1;

    //* Register plugin loop to espurna main loop
    //*------------------------------------------
    espurnaRegisterLoop(_pluginLoop);

    //* If API used set up Api
    //*-----------------------
    #if WEB_SUPPORT
        _pluginSetupAPI();
    #endif

    //* If Web Sockets set up WS
    //*-------------------------
//    #if WEB_SUPPORT
//        _pluginSetupWS();
//    #endif

    //* If MQTT used set up MQTT
    //*-------------------------
//    #if MQTT_SUPPORT
//        _pluginSetupMQTT();
//    #endif

    //* If trminal used set up terminal
    //*-------------------------------
	  #if TERMINAL_SUPPORT
	      _pluginInitCommands();
	  #endif
    DEBUG_MSG_P(PSTR("[PLUGIN] Plugin setup code finished \n"));

    //* Begin the Remote api
    remote.startTransmitter(RF_OUTPUT_PIN);
    initRelayStatus();
}
//* end of plugin setup
//*----------------------------------------------------------------------------

//*----------------------------------------------------------------------------
//* PLUGIN loop
//*----------------------------------------------------------------------------
void _pluginLoop() {
    //* if plugin disabled dont run the coded
    if (_plugin_enabled != 1) return;

    //* Check the relay status, send codes if any has changed
    checkRelayStatus();
}

//*----------------------------------------------------------------------------
//* Public - Plugin API
//*----------------------------------------------------------------------------
//* Here goes ublic plugin API definitions and coded
//* currently plugin enabled query implemented
//* use this as template to create additionl API calls
//* to Set/Get internal plugin data or use plugin functions
bool pluginEnabled() {
    return _plugin_enabled;
}
#endif  //#ifdef _PLUGIN_SF501
