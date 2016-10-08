<?php

for ($i = 0; $i < 100000; ++$i)
{
    $data = file_get_contents('http://127.0.0.1:1331');
    echo strlen($data) ."\n";
}
