<?php
namespace Zeus;

interface ZsEventInterface
{
    /**
     * Read event.
     *
     * @var int
     */
    const ZsEvent_Read = 1;

    /**
     * Write event.
     *
     * @var int
     */
    const ZsEvent_Write = 2;

    /**
     * Signal event.
     *
     * @var int
     */
    const ZsEvent_Signal = 4;

    /**
     * Timer once event.
     *
     * @var int
     */
    const zsEvent_Timerout = 8;

    /**
     * Timer event.
     *
     * @var int
     */
    const ZsEvent_Interval = 16;

    /**
     * Add event listener to event loop.
     *
     * @param mixed    $fd
     * @param int      $flag
     * @param callable $func
     * @param mixed    $args
     * @return bool
     */
    public function AddEventListener($fd, $flag, $func, $args = null);

    /**
     * Remove event listener from event loop.
     *
     * @param mixed $fd
     * @param int   $flag
     * @return bool
     */
    public function DelEventListener($fd, $flag);

    /**
     * Remove all timers.
     *
     * @return void
     */
    public function DelAllTimer();

    /**
     * Main loop.
     *
     * @return void
     */
    public function DoEventLoop();
}
