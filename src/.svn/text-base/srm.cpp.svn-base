#include <time.h>
#include <set>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <cgicc/Cgicc.h>
#include <jsoncpp/json.h>
#include <stdlib.h>
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <operate.h>
#include "utils.h"
#include "configuration.h"
#include "log.h"
using namespace std;
using namespace cgicc;
using namespace boost;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using boost::lexical_cast;
//#define DEBUG 1

typedef vector<string> string_vector;
typedef set<string> string_set;
typedef set<unsigned long> long_set;
typedef vector<pair<string, int> > pair_vector;

//create the thrift client by host ip
operateClient CreateService(const string& host)
{
    shared_ptr<TTransport> socket(new TSocket(host, conf.thriftPort));
    shared_ptr<TTransport> transport(new TFramedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    operateClient client(protocol);
    try {
        transport->open();
        return client;
    } catch (TException &tx) {
        transport->close();
        return client;
    }
}

/*the cgi param*/
Cgicc formData;
/*configuration*/
struct cacheConfig conf;

/* output results in json string */
void outputJsonString(const string &res, const double time,const int status)
{
    if(status != 0){
       cout <<  "{\"status\": " << status << ",\"time\": 0, \"result\": []}" << endl;
       return;
    }

    cout << "{\"status\": " << status <<  ", \"time\": " << time
         << ", \"result\": [" << res << "]}" << endl;
}

int main(int argc,char* argv[]){
    cout << "Content-type: text/html; charset=utf-8\n\n";
#ifdef DEBUG
    char *envQueryCstr = getenv("QUERY_STRING");
    if (envQueryCstr == NULL || strcmp(envQueryCstr, "") == 0) {
        outputJsonString("",0.0,-1); 
        exit(1);
    }
#endif
    loadConfig("./service.ini",conf);
    string uid = formData("uid");
    string cache = formData("cache");
    const char* uidCstr = uid.c_str();
    int isCache = cache == "0" ? 0 : 1;
    //get the data from db
    long start_usecs = get_time_usecs();
    unsigned int hash = genHashFunction((const unsigned char *)uidCstr, strlen(uidCstr));
    int groupNum = conf.serverGroup.size();
    pair<string,string> group = conf.serverGroup[hash%groupNum];
    long timestamp = get_time_usecs();
    string jsonStr;
    try{
        if(timestamp % 2 == 0){
	     operateClient client = CreateService(group.first);
             try{
	         client.get(jsonStr,string(uid),isCache);
             }catch(TException &tx){
                 client = CreateService(group.second);
                 client.get(jsonStr,string(uid),isCache);
             }
        }else{
	     operateClient client = CreateService(group.second);
             try{
                 client.get(jsonStr,string(uid),isCache);
             }catch(TException &tx){
                 client = CreateService(group.first);
                 client.get(jsonStr,string(uid),isCache);
             }
        }
    }catch(TException &tx){
        outputJsonString("",0.0,-1);
        return -1;
    }
    long end_usecs = get_time_usecs();                                                                                                  double secs = (double)(end_usecs - start_usecs) / (double)1000;
    outputJsonString(jsonStr,secs,0);
    return 0;
}
