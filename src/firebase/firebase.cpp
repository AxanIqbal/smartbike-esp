#include "firebase.h"
//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
// #include <addons/RTDBHelper.h>

/* 4. Define the user Email and password that alreadey registerd or added in
 * your project */

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

void firebaseInit()
{

    Serial.println();
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    //Or use legacy authenticate method
    //config.database_url = DATABASE_URL;
    //config.signer.tokens.legacy_token = "<database secret>";

    //To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
#if defined(ESP8266)
    fbdo.setBSSLBufferSize(512, 2048);
#endif
}