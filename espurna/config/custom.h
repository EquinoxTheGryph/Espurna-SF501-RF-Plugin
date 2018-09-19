//* espurna custom header template file
//* This is espurna custom header integration point
//* All custom defines goes Here
//* See plugin integration section on bottom of this file
//* Template Version: 0.0.1
//* files: /code/espurna/config/custom.h; code/espurna/plugin1.ino; /code/libplugin1/plugin1.h

#define MANUFACTURER            "APHELION"
#define DEVICE                  "CUSTOM"

// Disable non-core modules
#define ALEXA_SUPPORT           1 //0
#define BROKER_SUPPORT          1 //0
#define DOMOTICZ_SUPPORT        1 //0
#define HOMEASSISTANT_SUPPORT   1 //0
#define I2C_SUPPORT             0
#define MQTT_SUPPORT            1 //0
#define NTP_SUPPORT             1
#define SCHEDULER_SUPPORT       1
#define SENSOR_SUPPORT          0
#define THINGSPEAK_SUPPORT      0
#define WEB_SUPPORT             1
#define WEB_EMBEDDED            1
#define DEBUG_WEB_SUPPORT     	1
#define TELNET_SUPPORT          1
#define DEBUG_SERIAL_SUPPORT    1
#define TERMINAL_SUPPORT        1
#define SYSTEM_CHECK_ENABLED    1
#define HEARTBEAT_ENABLED       1
#define MDNS_SERVER_SUPPORT     0

// Relays
//#define DUMMY_RELAY_COUNT   4

// // Buttons
// #define BUTTON1_PIN         	  3
// #define BUTTON1_RELAY       	  1
// #define BUTTON1_MODE        	  BUTTON_SWITCH
// #define BUTTON1_CLICK      	    BUTTON_MODE_TOGGLE
// #define BUTTON_DBLCLICK_DELAY   500
// #define BUTTON_LNGCLICK_CNT     5
// #define BUTTON_LNGLNGCLICK_CNT  10
// #define BUTTON1_DBLCLICK        BUTTON_MODE_AP
// #define BUTTON1_LNGCLICK    	  BUTTON_MODE_RESET
// #define BUTTON1_LNGLNGCLICK 	  BUTTON_MODE_FACTORY
//
// // LEDs
// #define LED1_PIN            	1
// #define LED1_MODE            	LED_MODE_RELAY
// #define LED1_PIN_INVERSE    	0
// #define LED1_RELAY            1

// -----------------------------------------------------------------------------
// Plugin integration strt here
// -----------------------------------------------------------------------------
//* To create plugin you need 3 files:
//* custom.h: espurna's entry point for custom headers integration
//*     This header will be included by all.h, depended on USE_CUSTOM_H flag
//*     read top of all.h header file for help how to ectivate
//*     in espurna code (the only change you need in code code)
//* plugin(x).h: plugin header file
//* plugin(x).ino plugin code file

//* Include flags include the plugins code in the image
//* The plugin can be enabled/diabled in run time (API + TERMINAL commands)
#define INCLUDE_PLUGIN_SF501 1
//#define INCLUDE_PLUGIN2      0

//* USE_EXTRA is espurna 3rd party code integration hook
//* flag is used by espurna.ino to call extraSetup() function
#define USE_EXTRA            INCLUDE_PLUGIN_SF501 // || INCLUDE_PLUGIN2

//* Plugin integation point
#if USE_EXTRA
    //* include the plugin header (plugin entry point)
    #if INCLUDE_PLUGIN_SF501
        #include <sf501.h>
    #endif
    // #if INCLUDE_PLUGIN2
    //     #include <plugin2.h>
    // #endif

    //* Declare espurna calling function
    void extraSetup();

    void extraSetup() {
        //* extraSetup is called by espurna.ino (depended on USE_EXTRA flag)
        //* This is a single entry point to the plugin code
        //* Call the plugin setup function
        #if INCLUDE_PLUGIN_SF501
            pluginSF501Setup();
        #endif
        // #if INCLUDE_PLUGIN2
        //     plugin2Setup();
        // #endif
    }
#endif
