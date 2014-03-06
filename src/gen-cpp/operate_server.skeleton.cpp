// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "operate.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class operateHandler : virtual public operateIf {
 public:
  operateHandler() {
    // Your initialization goes here
  }

  void get(std::string& _return, const std::string& rowkey) {
    // Your implementation goes here
    printf("get\n");
  }

  int32_t putjson(const std::string& rowkey, const std::string& key, const std::string& value, const int32_t type) {
    // Your implementation goes here
    printf("putjson\n");
  }

  int32_t delkey(const std::string& rowkey) {
    // Your implementation goes here
    printf("delkey\n");
  }

  int32_t dump() {
    // Your implementation goes here
    printf("dump\n");
  }

  int32_t put(const std::string& rowkey, const std::string& value) {
    // Your implementation goes here
    printf("put\n");
  }

  int32_t load(const std::string& file) {
    // Your implementation goes here
    printf("load\n");
  }

  int32_t shutdown() {
    // Your implementation goes here
    printf("shutdown\n");
  }

  int32_t clear() {
    // Your implementation goes here
    printf("clear\n");
  }

  int32_t count() {
    // Your implementation goes here
    printf("count\n");
  }

  int32_t scan() {
    // Your implementation goes here
    printf("scan\n");
  }

  int32_t range(const std::string& from, const std::string& to) {
    // Your implementation goes here
    printf("range\n");
  }

  int32_t putbatch(const std::vector<kv> & kvs) {
    // Your implementation goes here
    printf("putbatch\n");
  }

  void status(std::string& _return) {
    // Your implementation goes here
    printf("status\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<operateHandler> handler(new operateHandler());
  shared_ptr<TProcessor> processor(new operateProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

