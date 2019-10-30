//LORA server address
#define SERVER_ADDRESS 15

//LORA client address
#define CLIENT_ADDRESS_RELAYS 115
#define CLIENT_ADDRESS_ENERGY_METER 107

//Determinant if we need to log the attendance or not based on the distance of the user
#define RSSI_LIMIT -100

//Credentials for Watson IOT

#define ORG "09bceq"
#define DEVICE_TYPE "kinex-lora-01"
#define DEVICE_ID "kinex-02"
#define TOKEN "E)?NhHkUS4P94qXS&u"

//#define DEVICE_TYPE "IA3201"
//#define DEVICE_ID "kinex01"
//#define TOKEN "CLa!TvNNF?8?l_BWN_"

#define MESSAGE_MAX_LEN 256

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

const char publishTopic[] = "iot-2/evt/status/fmt/json";
const char publishLoraTopic[] = "iot-2/evt/evt_energy/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char switch1Topic[] = "iot-2/cmd/led1/fmt/json";
const char switch2Topic[] = "iot-2/cmd/led2/fmt/json";
const char switch3Topic[] = "iot-2/cmd/led3/fmt/json";
const char switch4Topic[] = "iot-2/cmd/led4/fmt/json";
const char energyTopic[] = "iot-2/cmd/energy/fmt/json";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";


//pin for IR sender
#define SEND_PIN D0

#define INDICATOR D9
