BOOST_DIR = /data1/minisearch/dexin/boost-1.47.0-install/include
THRIFT_INCLUDE_DIR = ../include/thrift
JSONCPP_INCLUDE_DIR = ../include/jsoncpp
CGICC_INCLUDE_DIR = ../include/cgicc
LIB_DIR = ../lib 
GEN_SRC = ./gen-cpp/operate.cpp ./gen-cpp/CacheServer_constants.cpp  ./gen-cpp/CacheServer_types.cpp

CXXFLAGS = #--std=c++0x
LDFLAGS = -L${LIB_DIR} -ljson_linux-gcc-4.1.2_libmt -lthrift -lcgicc -lredisclient
LDFLAGS_C = -L${LIB_DIR} -ljson_linux-gcc-4.1.2_libmt -lredisclient -lthrift -lthriftnb -lleveldb -lpthread -levent
LDFLAGS_CGI = -L${LIB_DIR} -ljson_linux-gcc-4.1.2_libmt -lthrift -lthriftnb -lcgicc -lpthread -levent
#all: cacheserver cacheclient loaddb
all:  cacheserver cacheclient loaddb

OBJ = config.o genthrift.o cacheclient.o

INSTALL_BIN= ../leveldb-server/bin
DB=../leveldb-server/db
LOG=../leveldb-server/log
CGI=../leveldb-server/bin/cgi
INSTALL= mv
SERVERNAME=cacheserver_fansnum
CLIENTNAME=cacheclient_fansnum
LOADNAME=load_db
CONFIGNAME=./service.ini
CGINAME=srm.cgi

config.o: config.c utils.h
cacheclient.o: CacheClient.cpp
genthrift.o: ${GEN_SRC} ${THRIFT_INCLUDE_DIR}

cacheserver: CacheServer.cpp 
	g++ ${CXXFLAGS} -o cacheserver_fansnum -I../include -I${THRIFT_INCLUDE_DIR} -I${BOOST_DIR} -I./gen-cpp CacheServer.cpp ${GEN_SRC} ${LDFLAGS_C}  

cacheclient: CacheClient.cpp 
	g++ ${CXXFLAGS} -o cacheclient_fansnum -I../include -I${THRIFT_INCLUDE_DIR} -I${BOOST_DIR} -I./gen-cpp CacheClient.cpp ${GEN_SRC} ${LDFLAGS_C}

srm: srm.cpp
	g++ ${CXXFLAGS} -o srm.cgi -I../include -I${THRIFT_INCLUDE_DIR} -I${BOOST_DIR} -I./gen-cpp srm.cpp ${GEN_SRC} ${LDFLAGS_CGI}

loaddb: LoadData.cpp
	g++ ${CXXFLAGS} -o load_db -I../include -I${BOOST_DIR} LoadData.cpp ${LDFLAGS_C}

clean:
	rm cacheserver_fansnum
	rm cacheclient_fansnum
	rm srm.cgi

install: all
	mkdir -p $(INSTALL_BIN)
	mkdir -p $(DB)
	mkdir -p $(LOG)
	mkdir -p $(CGI)
	$(INSTALL) $(SERVERNAME) $(INSTALL_BIN)
	$(INSTALL) $(CLIENTNAME) $(INSTALL_BIN)
	$(INSTALL) $(CONFIGNAME) $(INSTALL_BIN)
	$(INSTALL) $(CGINAME) $(CGI)
	$(INSTALL) $(CONFIGNAME) $(CGI)
