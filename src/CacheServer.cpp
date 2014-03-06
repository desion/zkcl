#include <time.h>

#include <iostream>
#include <string.h>
#include <vector>
#include <server/TSimpleServer.h>
#include <config.h>
#include <jsoncpp/json.h>

#include <protocol/TCompactProtocol.h>
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include <operate.h>
#include <sys/time.h>
#include <redisclient/redisclient.h>

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <server/TNonblockingServer.h>
#include <server/TThreadPoolServer.h>
#include <leveldb/db.h>
#include <stdlib.h>
#include <fcntl.h>
#include "utils.h"
#include "configuration.h"
#include "ServiceImpl.h"
#define DEBUG 1

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;
Json::Reader reader;
vector<pair<string, int> > serviceList;

struct cacheConfig conf;
unsigned int serviceNum;

char* confFile = new char[1024];

#define SERVER_VERSION "1.0"
/* read service list from servece.ini */
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
/* Thomas Wang's 32 bit Mix Function */
unsigned int intHashFunction(unsigned int key)
{
    key += ~(key << 15);
    key ^=  (key >> 10);
    key +=  (key << 3);
    key ^=  (key >> 6);
    key += ~(key << 11);
    key ^=  (key >> 16);
    return key;
}

//create the pid file storre the pid
void createPidFile(void) {
    string pidPath = conf.pidPath;
    /* Try to write the pid file in a best-effort way. */
    FILE *fp = fopen(pidPath.c_str(),"w");
    if (fp) {
        fprintf(fp,"%d\n",(int)getpid());
        fclose(fp);
    }
}

void InitConfig(){
    loadConfig(confFile,conf);
#ifdef DEBUG
        cout << "[DEBUG] Config File:" << confFile << endl;
        cout << "[DEBUG] thriftPort:" << conf.thriftPort 
             << " leveldbPath:" << conf.leveldbPath << '\n';
#endif
}

void InitServer(){
    //redis client 
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, conf.leveldbPath, &db);
    //Thrfit Server NonBlocking
    shared_ptr<ServiceImpl> handler(new ServiceImpl(db));
    shared_ptr<TProcessor> processor(new operateProcessor(handler));
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    //shared_ptr<TProtocolFactory> protocolFactory(new TCompactProtocolFactory());

    shared_ptr<TServerTransport> serverTransport(new TServerSocket(conf.thriftPort));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(20);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
    TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    //TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

    // using thread pool with maximum 15 threads to handle incoming requests    

    /*shared_ptr<ThreadManager> threadManager =
            ThreadManager::newSimpleThreadManager(15);
    shared_ptr<PosixThreadFactory> threadFactory =
            shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
    TNonblockingServer server(processor, protocolFactory, conf.thriftPort, threadManager);*/
    server.serve();
}

static void sigtermHandler(int sig) {
    Log(CACHE_LOG_WARNING,"Received SIGTERM, scheduling shutdown...");
    cout << "Received SIGTERM, scheduling shutdown..." << endl;
    exit(0);
}

void usage(){
    fprintf(stderr, "Usage: CacheServer\n");
    fprintf(stderr, "-v -version show the version\n");
    fprintf(stderr, "-h -help show usage\n");
    fprintf(stderr, "-c [config file] specify the config file\n");
}
void daemonize(void) {
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}

void setupSignalHandlers(void) {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sigtermHandler;
    sigaddset(&act.sa_mask,SIGINT);
    sigaction(SIGINT, &act, NULL);
    return;
}

int main(int argc, char *argv[])
{
    if(argc == 2){
        if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1],"-version") == 0){
            printf("CacheServer Version:%s\n",SERVER_VERSION);
            exit(0); 
        }else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") ==0){
        
        }else{
            usage();
        }
    }else if(argc == 3){
        if(strcmp(argv[1], "-c") ==0){
            daemonize();
            setupSignalHandlers();
            strcpy(confFile, argv[2]);
            InitConfig();
            createPidFile();
            Log(CACHE_LOG_WARNING,"CacheServer start ...");
            InitServer();
        }else{
           usage();
        }
    }else{
        usage();
    }
    return 0;
}
