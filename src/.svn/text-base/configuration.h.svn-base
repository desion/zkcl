
/*split the string*/
int split(const string& src, string sep,vector<string>& strs)
{
    int separate_characterLen = sep.size();
    int lastPosition = 0,index = -1;
    while (-1 != (index = src.find(sep,lastPosition)))
    {
        strs.push_back(src.substr(lastPosition,index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    string lastString = src.substr(lastPosition);
    if (!lastString.empty())
        strs.push_back(lastString);
    return strs.size();
}

extern struct cacheConfig conf;

//Load the json config file
void loadConfig(const char *path, struct cacheConfig& conf){
    Json::Reader reader;
    Json::Value configuration;
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
    {
        cerr << "[ERROR] can't open the config file\n";
        exit(1);
    }
    char *buf = new char[2048];
    if(fgets(buf, 2048, fp) != NULL){
        bool issucess = reader.parse(buf, configuration);
        if(!issucess){
            cerr << "[ERROR] pase the configuration failed\n";
            exit(2);
        }
        conf.thriftPort = configuration["thriftPort"].asInt();
	cout << "thriftPort" << configuration["thriftPort"];
        //conf.redisHost = configuration["redisHost"].asString();
        //conf.redisDB = configuration["redisDB"].asInt();
        conf.leveldbPath = configuration["leveldbPath"].asString();
        conf.logLevel = configuration["logLevel"].asInt();
        conf.logPath = configuration["logPath"].asString();
        conf.pidPath = configuration["pidPath"].asString();
	conf.dumpPath = configuration["dumpPath"].asString();
        conf.vbose = configuration["vbose"].asInt();
        vector<string> serviceGroup;
        Json::Value serviceArray = configuration["serviceGroup"];
        for(int i = 0;i < serviceArray.size();i += 1){
            serviceGroup.push_back(serviceArray[i].asString());
        }
        /*vector<pair<string,string> >::iterator serviceIter = serviceGroup.begin();
        for(;serviceIter != serviceGroup.end();++serviceIter){
            cout << "first:" << (*serviceIter).first << " second:" << (*serviceIter).second << endl;
        }
        cout << "group size:" << serviceGroup.size();
        */
        conf.serverGroup = serviceGroup;
        delete buf;
    }else{
        cerr << "[ERROR] config file empty\n";
        delete buf;
        exit(3);
    }
    fclose(fp);
}
