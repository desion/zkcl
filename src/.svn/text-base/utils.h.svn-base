#include <stdio.h>
#include <time.h>

#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <operate.h>
#include <stdarg.h>
#include <syslog.h>
#include <jsoncpp/json.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//#define VERSION "1.0"
#define MAX_LOGMSG_LEN 1024

/* Log levels */
#define CACHE_LOG_DEBUG 0
#define CACHE_LOG_VERBOSE 1
#define CACHE_LOG_NOTICE 2
#define CACHE_LOG_WARNING 3

#define CACHE_TYPE_INT 2
#define CACHE_TYPE_LONG 3
#define CACHE_TYPE_STRING 1
using namespace std;
typedef struct cacheConfig{
   int thriftPort;
   //string redisHost;
   //int redisDB;
   string leveldbPath;
   int logLevel;
   string logPath;
   int vbose;
   string pidPath;
   string dumpPath;
   vector<string> serverGroup;
} cacheConfig;

