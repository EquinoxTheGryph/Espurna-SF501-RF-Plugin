#ifdef INCLUDE_PLUGIN_SF501
#ifndef _PLUGIN_SF501
#define _PLUGIN_SF501


//*---------------------------------------------------------------------------
//* Espurna overrides
//* -------------------------------------------------------------------------
//*  Here put espurna plugin specific overrides
#define RELAY_PROVIDER          RELAY_PROVIDER_HW655
#define SERIAL_BAUDRATE         9600

//---------------------------------------------------------------------------
//* Plugin defines
//----------------------------------------------------------------------------
//* plese refer to plugin1.ino for more help and inline documentaion
//* Plugin enabled flag (enabling or disabling execution)
#define PLUGIN_SF501_ENABLE             1
//* sample plugin MTQQ topic
#define MQTT_TOPIC_SF501         "SF501"
//* Sample plugin reporting interval (0 no reporting)
#define PLUGIN_REPORT_EVERY        5

//------------------------------------------------------------
//* Plugin public interface
//------------------------------------------------------------
//* declare the plugin setup function (used by custom.h)
void pluginSF501Setup();
//* get plugin enabled state
bool pluginEnabled();

#endif
#endif
