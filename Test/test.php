<?php

/*
for ($i = 0; $i < 100000; ++$i)
{
    $data = file_get_contents('http://127.0.0.1:1331');
    echo strlen($data) ."\n";
}
*/

for ($i = 0; $i < 40000000; ++$i)
{
    $socket = socket_create( AF_INET, SOCK_DGRAM, SOL_UDP );
    $msg = "echo|asdasdasdasdasdlkajsdlkajskldjaklsdjalksdjlkasjdlkasjdklasjd";
    $len = strlen($msg);
    socket_sendto($socket, $msg, $len, 0, 'localhost', 8687);

    $from = "";
    $port = 0;
    socket_recvfrom( $socket, $buf, 1024, 0, $from, $port );

    //echo $buf."\n";

    //echo $buf;
    if (0 == $i % 10000)
    {
        echo $i ."\n";
    }
}
