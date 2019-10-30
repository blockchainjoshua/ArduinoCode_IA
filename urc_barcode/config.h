#define DEBUG



//Credentials for Watson IOT
#define ORG "140ugs"
#define DEVICE_TYPE "urc-calamba-p"
#define DEVICE_ID "kx-barcode-03"
#define TOKEN "4fI5xgaD@enVe)4nR6"

#define wifimanager_ssid DEVICE_ID
#define wifimanager_password "123"

//#define DEVICE_ID "line1-barcode-02"
//#define TOKEN "j)+&?X28)VwY6K1Qyi"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";;
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

//commands
const char getIPTopic[] = "iot-2/cmd/ip/fmt/json";

#define sensor_pin A0
#define green_pin D8
#define red_pin D7
#define button_pin D0

//software serial
#define rx_pin 14 //D5
#define tx_pin 12 //D6
#define sw_baud 9600

// EEPROM address configuration
#define EEPROM_SIZE 512

#define CALIBRATION_MAX_LENGH 20
#define SENSOR_MIN_LENGH 20
#define SENSOR_MAX_LENGTH 20

#define MESSAGE_MAX_LEN 256
