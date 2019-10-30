#define DEBUG

//Credentials for Watson IOT
#define ORG "2b9cz4"
#define DEVICE_TYPE "kx-ultrasonic"
#define DEVICE_ID "ultrasonic"
#define TOKEN "xI9E9w5V93ko*-?uA1"

#define wifimanager_ssid DEVICE_ID
#define wifimanager_password "123"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

const char publishTopic[] = "iot-2/evt/status/fmt/json";
const char publishSensorTopic[] = "iot-2/evt/sensor/fmt/json";
const char publishIPTopic[] = "iot-2/evt/myip/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";

const char getIPTopic[] = "iot-2/cmd/ip/fmt/json";

//commands
//const char showReadingTopic[] = "iot-2/cmd/reading/fmt/json";

#define sensor_pin A0
#define green_pin D8
#define red_pin D7
#define button_pin D0

#define TRIGGER D1  
#define ECHO    D2

// EEPROM address configuration
#define EEPROM_SIZE 512

#define MESSAGE_MAX_LEN 256
