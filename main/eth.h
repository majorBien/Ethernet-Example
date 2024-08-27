/*
 * eth.h
 *
 *  Created on: 27 sie 2024
 *      Author: Dell
 */



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "lwip/dns.h"
#include "esp_log.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_eth.h" 
#include <arpa/inet.h>


#define ETH_AP_MAX_CONNECTIONS		5					// AP max clients
#define ETH_AP_BEACON_INTERVAL		100					// AP beacon: 100 milliseconds recommended
#define ETH_AP_IP					"192.168.0.1"		// AP default IP
#define ETH_AP_GATEWAY				"192.168.0.1"		// AP default Gateway (should be the same as the IP)
#define ETH_AP_NETMASK				"255.255.255.0"		// AP netmask
#define ETH_AP_DNS1                 "8.8.8.8"           // AP dns1
#define ETH_AP_DNS2					"8.8.4.4"			// AP dns2
#define ETH_AP_MAC_ADDRESS			"12:2:8:4:7:6"       // AP mac 
#define ETH_APP_DHCP				0					// DHCP on/off

typedef struct {
    uint8_t v[4]; 
} IP_ADDR;


typedef struct {
    IP_ADDR ip;
    IP_ADDR netmask;
    IP_ADDR gw;
    IP_ADDR dns1;
    IP_ADDR dns2;
    uint8_t dhcp;
} CFG;


typedef union _DWORD_VAL {
    uint32_t Val;
    uint16_t w[2];
    uint8_t v[4];
} DWORD_VAL;


CFG AppConfig;


void get_eth_mac(uint8_t *mac_addr);

static void eth_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

static void got_ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

void ethernet_init(void);

void setIPAddressFromString(IP_ADDR *ip, const char *ipStr);

void ethernetParamConfig(CFG *config);

void setStaticIP(CFG * config);