

#ifndef Firebase_h
#define Firebase_h

#include <Firebase_ESP_Client.h>

#define API_KEY "AIzaSyDEXI0NflTOvRTBLOpA8w5zG7ZzHww_YtU"
#define DATABASE_URL "https://smart-bike-93ffd-default-rtdb.firebaseio.com/"

#define USER_EMAIL "asd15654@bike.com"
#define USER_PASSWORD "asdasdasd"

extern FirebaseData fbdo;
extern FirebaseAuth auth;
extern FirebaseConfig config;

void firebaseInit();

#endif