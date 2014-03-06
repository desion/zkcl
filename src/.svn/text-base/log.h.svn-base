
extern struct cacheConfig conf;
void Log(int level, const char *fmt, ...) {
    const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
    const char *c = ".-*#";
    time_t now = time(NULL);
    va_list ap;
    FILE *fp;
    char buf[64];
    char msg[MAX_LOGMSG_LEN];

    if (level < conf.vbose) return;

    fp = fopen(conf.logPath.c_str(),"a");
    if (!fp) return;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
    fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
    fflush(fp);

    fclose(fp);

    //if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
}

/* Generic hash function (a popular one from Bernstein). */
unsigned int genHashFunction(const unsigned char *buf, int len) {
    unsigned int hash = 5381;

    while (len--)
        hash = ((hash << 5) + hash) + (*buf++); /* hash * 33 + c */
    return hash;
}

/*get current time*/
long get_time_usecs()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    long usecs = time.tv_sec*1000000 + time.tv_usec;
    return usecs;
}
