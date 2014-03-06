#! /usr/local/bin/php
<?php
        date_default_timezone_set("PRC");
	$GLOBALS['THRIFT_ROOT']='./phplib';
	require_once $GLOBALS['THRIFT_ROOT'].'/Thrift.php';
	require_once $GLOBALS['THRIFT_ROOT'].'/protocol/TBinaryProtocol.php';
	require_once $GLOBALS['THRIFT_ROOT'].'/transport/TSocket.php';
	require_once $GLOBALS['THRIFT_ROOT'].'/transport/TBufferedTransport.php';
	require_once $GLOBALS['THRIFT_ROOT'].'/CacheServer/operate.php';
	require_once $GLOBALS['THRIFT_ROOT'].'/CacheServer/CacheServer_types.php';
	function getInstance($LEVELDB_IP,$LEVELDB_PORT){
		$socket = new TSocket($LEVELDB_IP, $LEVELDB_PORT);
		if(!$socket) return false;
		$socket->setSendTimeout( 1000 );
		$socket->setRecvTimeout( 1000 ); // ten seconds
		$transport = new TBufferedTransport($socket,4096,4096);
		if(!$transport) return false;
		$protocol = new TBinaryProtocol($transport);
		if(!$protocol) return false;
		$processer = new operateClient($protocol);
		if(!$processer) return false;
		$transport->open();
		return $processer;
	}

        $ldb = getInstance("127.0.0.1",8090);
        //var_dump($ldb->putjson(1,'num1' ,3, 2));
        $res = $ldb->get(1);
        var_dump(json_decode($res));
?>
