/*
 Version : 1.0.0
 Modified : 30/6/2019
 Licence: GNU Lesser General Public License v3.0
 Data Storage Library - Stores sensor data into device RAM and serves them per request.
*/


#ifndef SENSORDB_h
#define SENSORDB_h

#include "Arduino.h"
#include "ArduinoJson.h" // Compatible with ArduinoJson v6.10.0

#define DEBUG 0

#define SENSOR_LIMIT 15

class SENSORDBClass{
    public: 
        String getJson(){
            String json = "";
            
            StaticJsonDocument<1024> arrayDoc;
            JsonArray array = arrayDoc.to<JsonArray>();
            
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] != ""){
                    DynamicJsonDocument doc(256);
                    JsonObject object = doc.to<JsonObject>();
                    object["id"] = sensor_id[i];
                    object["name"] = sensor_name[i];
                    if(sensor_type[i] == 0){
                        object["value"] = sensor_string_value[i];
                    }else if(sensor_type[i] == 1){
                        object["value"] = sensor_int_value[i];
                    }else if(sensor_type[i] == 2){
                        object["value"] = sensor_bool_value[i];
                    }
                    object["unit"] = sensor_unit[i];
                    array.add(object);
                }
            }
            serializeJson(arrayDoc, json);
            return json;
        }

         String getSenML(){
            String json = "";
            
            StaticJsonDocument<512> arrayDoc;
            JsonArray array = arrayDoc.to<JsonArray>();
            
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] != ""){
                    DynamicJsonDocument doc(256);
                    JsonObject object = doc.to<JsonObject>();
                    object["n"] = sensor_id[i];
                    object["u"] = sensor_unit[i];
                    if(sensor_type[i] == 0){
                        object["v"] = sensor_string_value[i];
                    }else if(sensor_type[i] == 1){
                        object["v"] = sensor_int_value[i];
                    }else if(sensor_type[i] == 2){
                        object["v"] = sensor_bool_value[i];
                    }
                    array.add(object);
                }
            }
            serializeJson(arrayDoc, json);
            return json;
        }

        String get(const char* id){
            String json = "";
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == id){
                    StaticJsonDocument<256> doc;
                    JsonObject object = doc.to<JsonObject>();
                    object["id"] = sensor_id[i];
                    object["name"] = sensor_name[i];
                    if(sensor_type[i] == 0){
                        object["value"] = sensor_string_value[i];
                    }else if(sensor_type[i] == 1){
                        object["value"] = sensor_int_value[i];
                    }else if(sensor_type[i] == 2){
                        object["value"] = sensor_bool_value[i];
                    }
                    object["unit"] = sensor_unit[i];
                    serializeJson(doc, json);
                    break;
                }
            }
            return json;
        }

        void insert(const char* id, const char* name, const char* value, const char* unit){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == ""){
                    sensor_id[i] = id;
                    sensor_name[i] = name;
                    sensor_type[i] = 0;
                    sensor_string_value[i] = value;
                    sensor_unit[i] = unit;
                    break;
                }
            }
        }

        void insert(const char* id, const char* name, int value, const char* unit){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == ""){
                    sensor_id[i] = id;
                    sensor_name[i] = name;
                    sensor_type[i] = 1;
                    sensor_string_value[i] = value;
                    sensor_unit[i] = unit;
                    break;
                }
            }
        }

        void insert(const char* id, const char* name, bool value, const char* unit){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == ""){
                    sensor_id[i] = id;
                    sensor_name[i] = name;
                    sensor_type[i] = 2;
                    sensor_string_value[i] = value;
                    sensor_unit[i] = unit;
                    break;
                }
            }
        }

        void update(const char* id, const char* value){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == id && sensor_type[i] == 0){
                    sensor_string_value[i] = value;
                    break;
                }
            }
        }

        void update(const char* id, int value){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == id && sensor_type[i] == 1){
                    sensor_int_value[i] = value;
                    break;
                }
            }
        }

        void update(const char* id, bool value){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == id && sensor_type[i] == 2){
                    sensor_bool_value[i] = value;
                    break;
                }
            }
        }

        void destroy(const char* id){
            for(int i=0; i < SENSOR_LIMIT; i++){
                if(sensor_id[i] == id){
                    sensor_id[i] = "";
                    sensor_name[i] = "";
                    sensor_unit[i] = "";
                    sensor_string_value[i] = "";
                    sensor_int_value[i] = 0;
                    sensor_bool_value[i] = false;
                    break;
                }
            }
        }

        void destroyAll(){
            for(int i=0; i < SENSOR_LIMIT; i++){
                sensor_id[i] = "";
                sensor_name[i] = "";
                sensor_unit[i] = "";
                sensor_string_value[i] = "";
                sensor_int_value[i] = 0;
                sensor_bool_value[i] = false;
            }
        }

    private:
        // ID
        String sensor_id[SENSOR_LIMIT] = {};
        String sensor_name[SENSOR_LIMIT] = {};
        String sensor_unit[SENSOR_LIMIT] = {};

        // Types -
        // 0 - String
        // 1 - int
        // 2 - bool
        int sensor_type[SENSOR_LIMIT] = {};

        // Data
        String sensor_string_value[SENSOR_LIMIT] = {};
        int sensor_int_value[SENSOR_LIMIT] = {};
        bool sensor_bool_value[SENSOR_LIMIT] = {};
};

SENSORDBClass DataStorage;
#endif
