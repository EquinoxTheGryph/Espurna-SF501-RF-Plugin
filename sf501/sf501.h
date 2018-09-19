/*

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
