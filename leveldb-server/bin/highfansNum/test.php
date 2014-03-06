<?php
    $path = "./db/leveldb";
    $db = new LevelDb($path);
    var_dump($db->get("1"));
?>
