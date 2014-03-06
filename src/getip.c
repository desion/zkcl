#include <iostream>
#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <time.h>
using namespace std;

#define MST (-7)

int main(int argc, char *argv[])
{
	/*char hostname[256]; 
        gethostname(hostname, sizeof(hostname)); 	
	hostent * record = gethostbyname(hostname);
	if(record == NULL)
	{
		printf("%s is unavailable\n", argv[1]);
		exit(1);
	}
	in_addr * address = (in_addr * )record->h_addr;
	string ip_address = inet_ntoa(* address);
	cout  << " (" << ip_address << ")\n";*/
        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        hostent* host = gethostbyname(hostname);
        in_addr* address = (in_addr *)host->h_addr;
        char* ip = inet_ntoa(*address);
        char buf[1024];
        sprintf(buf,"host:%s ip:%s status:ok",hostname,ip);
        printf("%s",buf);
        string ret = string(buf);
        cout << ret << endl;
	return 0;
}

