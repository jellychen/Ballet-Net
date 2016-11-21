<?php

namespace Zeus;

class ZsEventLoop
{
    const ZsEventRead = 1;

    const ZsEventWrite = 2;

    const ZsEventSignal = 4;

    const ZsEventInterval = 8;

    const zsEventTimerout = 16;

    protected $eventLoop_ = null;

    public function __construct()
    {
        $this->$eventLoop_ = new \EventBase();
    }

    public function AddEventListener()
    {

    }

    public function RemoveEventListener()
    {

    }
}
