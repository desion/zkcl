#include <stdio.h>
#include <stdlib.h>
#include "leveldb/write_batch.h"
#include<fcntl.h>
#include<unistd.h>
#include <leveldb/db.h>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <string>
#define MAX_LINE 1024
using namespace std;

static int read_cnt;
static char* read_ptr;
static char read_buf[4096];
long get_time_usecs()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    long usecs = time.tv_sec*1000000 + time.tv_usec;
    return usecs;
}
static ssize_t my_read(int fd, char* ptr){
    if(read_cnt <=0){
        again:
        if((read_cnt = read(fd, read_buf,sizeof(read_buf))) < 0){
            if(errno == EINTR) goto again;
            return (-1);
        }else if(read_cnt == 0){
            return (0);
        }
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

ssize_t readline(int fd, char *vptr, size_t maxline){
    int n, rc;
    char c,*ptr;
    ptr = vptr;
    for(n = 1; n < maxline; n++){
       if((rc = my_read(fd, &c)) == 1){
           if(c == '\n' || c == '\r'){
               break;
           }
           *ptr++ = c;
       }else if(rc == 0){
           if(n == 1){
              return 0;
           }else{
               break;
           }
       }else{
           return -1;
       }
    }
    *ptr = 0;
    return n;
}

/*split the string*/
/*int split(const string& src, string sep,vector<string>& strs)
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
}*/

void split(char *src, const char *separator, char **dest, int *num)
{
    char *pNext;
    int count = 0;

    if (src == NULL || strlen(src) == 0) return;
    if (separator == NULL || strlen(separator) == 0) return;

    pNext = strtok(src,separator);

    while(pNext != NULL)
    {
        *dest++ = pNext;
        ++count;
        pNext = strtok(NULL,separator);
    }

    *num = count;
}

int main(int argc, char* argv[]){
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, argv[2], &db);
    if(status.ok()){
        cout << "open db" << argv[2] << " ok!" << endl; 
    }
    long start_usecs = get_time_usecs();
    char* path = argv[1];
    int fp = open(path,O_RDONLY);
    if (fp) {
       char line[1024];
       leveldb::WriteBatch batch;
       int i = 0;
       vector<string> items;
       int splitnum_ = 2;
       while((readline(fp, line, MAX_LINE)) > 0){
           if(i > 0 && i % 100000 ==0){
               leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
               if(status.ok()){
                  cout << "ok" << endl;
               }else{
                  cerr << "fail" << endl;
              }
              batch.Clear();
           }
	   
           i++;
           int strsize_ = strlen(line);
           char *items_[strsize_];
           split(line,"\t",items_,&splitnum_);
           batch.Put(string(items_[0]), string(items_[1]));
       }
       leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
       if(status.ok()){
             cout << "ok" << endl;
        }else{
             cerr << "fail" << endl;
        }
        cout << "total:" <<  i << endl;
        batch.Clear();
        delete db;
    }else{
       cerr << "read file fial" << endl;
    }

    /*FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        cerr << "[Error] can not open server IP address file!\n";
        exit(1);
    }
    char uid[24];
    int num1,num2;
    leveldb::WriteBatch batch;
    int i = 0;
    while (fscanf(fp, "%s\t%d\t%d\n", uid, num1, num2) != EOF) {
        if(i % 10000 == 0){
            leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
            leveldb::WriteBatch batch;
        }else{
           char str[24];
           sprintf(str,"%d\t%d",num1, num2);
           batch.Put(uid,str);
           i++; 
       }
       printf("%s\t%d\t%d\n", uid, num1, num2);
    }*/

    long end_usecs = get_time_usecs();
    double secs = (double)(end_usecs - start_usecs) / (double)1000;
    cout <<  " use time:" << secs / 1000 << "s" << endl;
}
