#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <jsoncpp/json.h>
#include <redisclient/redisclient.h>

//#define DEBUG 1
#define LOAD_SIZE 4096
#define CACHE_SIZE 2048
using namespace std;
using namespace boost;


Json::Reader reader;
/*the service list*/
vector<pair<string, int> > serviceList;

/*void loadCache(string &file){
    FILE *userFile = fopen(file, "r");
    if(userFile != NULL){
        try{
            shared_ptr<redis::client> redisClient(new redis::client(ip));
            redisClient->select(9);
            Josn:Reader reader;
            Json:Value value;
            char *strJson = new char[2048];
            while(fscanf(userFile, "%s", strJson) != EOF){
                 bool isSucess = reader.parse(strJson, value);
                 if(!isSucess) continue;
                 string uid = value.get("uid").asString();
                 redisClient->set(uid, string(strJson));
            }
            fclose(userFile);
        }catch(redis::redis_error& re){
            fclose(userFile);
            exit(EXIT_FAILURE);
        }
    }
}*/

void loadServiceList(const char *path, vector<pair<string, int> > &serviceList)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
#ifdef DEBUG
        cerr << "[Error] can not open server IP address file!\n";
#endif
        exit(1);
    }

    char ip[32];
    int port;

    while (fscanf(fp, "%s %d\n", ip, &port) != EOF) {
        serviceList.push_back(pair<string, int>(ip, port));
    }

    fclose(fp);

#ifdef DEBUG
    cout << "[DEBUG] service number: " << serviceList.size() << '\n';
#endif
}

/* Generic hash function (a popular one from Bernstein). */
unsigned int genHashFunction(const unsigned char *buf, int len) {
    unsigned int hash = 5381;

    while (len--)
        hash = ((hash << 5) + hash) + (*buf++); /* hash * 33 + c */
    return hash;
}

int main(int argc, char *argv[]){
#ifdef DEBUG
    cout << "[DEBUG] file name: " << string(argv[1]) << '\n';
#endif
    loadServiceList("./service.ini", serviceList);
    /*the total merger services*/
    unsigned int serviceNum = serviceList.size();
    FILE *userFile = fopen(argv[1], "r");
    if(userFile != NULL){
        try{
            Json::Value value;
            char *strJson = new char[LOAD_SIZE];
            while(!feof(userFile)){
                 if(fgets(strJson, LOAD_SIZE, userFile) == NULL) continue;
#ifdef DEBUG
    cout << "[DEBUG] line: " << string(strJson) << " size:"  << strlen(strJson) <<'\n';
#endif
                 if(strlen(strJson) > CACHE_SIZE) continue;
                 bool isSucess = reader.parse(strJson, value);
                 if(!isSucess){
                     cerr << "parse error:" << string(strJson) << '\n';
                     continue;
                 }
                 string uid = value["uid"].asString();
#ifdef DEBUG
    cout << "[DEBUG] uid: " << uid << '\n';
#endif
                 const char *uidCstr = uid.c_str();
                 unsigned int hash = genHashFunction((const unsigned char *)uidCstr, strlen(uidCstr));
                 string ip = serviceList[hash%serviceNum].first;
                 /*redis client*/
#ifdef DEBUG
    cout << "[DEBUG] redis ip: " << ip << '\n';
#endif
                 shared_ptr<redis::client> redisClient(new redis::client(ip));
                 redisClient->select(9);
                 redisClient->set(uid, string(strJson));
                 cout << uid << '\t' << ip << '\n';
            }
            fclose(userFile);
            delete strJson;
        }catch(redis::redis_error& re){
            cerr << "redis error:" << re.what() << '\n';
            fclose(userFile);
            exit(EXIT_FAILURE);
        }
    }    
    return 0;
}
