// INPUT HERE THE WIFI CONNECTION DATA

// const char * WIFI_SSID = "Nothing Phone (1)";
// const char * WIFI_PASS = "pholpetrol";

const char * WIFI_SSID = "Netu13";
const char * WIFI_PASS = "sons1929";

// const char * WIFI_SSID = "TP-Link_Archer_AX50";
// const char * WIFI_PASS = "xxx";

//#define WIFI_SSID "DIGI_3cc088"
//#define WIFI_PASS "5b2ec33f"

//#define WIFI_SSID "TP-LINK_453E"
//#define WIFI_PASS "46821584"

// HTTP CONNECTION DATA

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET"; // or "POST"
char   HOST_NAME[] = "api.openweathermap.org"; // hostname of web server:

String API_KEY = "37ac76a7227cc0aa9c4be36d2120dcbe";
String CITY_NAME = "Timisoara";
String COUNTRY_CODE = "RO";
String PATH_NAME   = "/data/2.5/weather?q=" + CITY_NAME + "," + COUNTRY_CODE + "&APPID=" + API_KEY;

// LCD SIZE DEF

#define LCD_ADDRESS 0x27
#define LCD_COLLUMNS 16
#define LCD_ROWS 2