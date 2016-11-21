<?php
namespace Zeus;

class ZsEvent implements ZsEventInterface
{
    /**
     * Event base.
     * @var object
     */
    protected $_eventBase = null;

    /**
     * All listeners for read/write event.
     * @var array
     */
    protected $_allEvents = array();

    /**
     * Event listeners of signal.
     * @var array
     */
    protected $_eventSignal = array();

    /**
     * All timer event listeners.
     * [func, args, event, flag, time_interval]
     * @var array
     */
    protected $_eventTimer = array();

    /**
     * Timer id.
     * @var int
     */
    protected static $_timerId = 1;

    /**
     * construct
     * @return void
     */
    public function __construct()
    {
        $this->_eventBase = new \EventBase();
    }

    /**
     * @see EventInterface::add()
     */
    public function AddEventListener($fd, $flag, $func, $args=array())
    {
        switch ($flag)
        {
            case self::ZsEvent_Signal:
                $fd_key = (int)$fd;
                $event = \Event::signal($this->_eventBase, $fd, $func);
                if (!$event||!$event->add())
                {
                    return false;
                }
                $this->_eventSignal[$fd_key] = $event;
                return true;

            case self::zsEvent_Timerout:
            case self::ZsEvent_Interval:
                $param = array($func, (array)$args, $flag, $fd, self::$_timerId);
                $event = new \Event($this->_eventBase, -1, \Event::TIMEOUT|\Event::PERSIST, array($this, "timerCallback"), $param);
                if (!$event||!$event->addTimer($fd))
                {
                    return false;
                }
                $this->_eventTimer[self::$_timerId] = $event;
                return self::$_timerId++;

            default :
                $fd_key = (int)$fd;
                $real_flag = $flag === self::EV_READ ? \Event::READ|\Event::PERSIST : \Event::WRITE|\Event::PERSIST;
                $event = new \Event($this->_eventBase, $fd, $real_flag, $func, $fd);
                if (!$event||!$event->add())
                {
                    return false;
                }
                $this->_allEvents[$fd_key][$flag] = $event;
                return true;
        }
    }

    /**
     * @see Events\EventInterface::del()
     */
    public function DelEventListener($fd, $flag)
    {
        switch ($flag)
        {
            case self::ZsEvent_Read:
            case self::ZsEvent_Write:
                $fd_key = (int)$fd;
                if (isset($this->_allEvents[$fd_key][$flag]))
                {
                    $this->_allEvents[$fd_key][$flag]->del();
                    unset($this->_allEvents[$fd_key][$flag]);
                }

                if (empty($this->_allEvents[$fd_key]))
                {
                    unset($this->_allEvents[$fd_key]);
                }
                break;

            case  self::ZsEvent_Signal:
                $fd_key = (int)$fd;
                if (isset($this->_eventSignal[$fd_key]))
                {
                    $this->_allEvents[$fd_key][$flag]->del();
                    unset($this->_eventSignal[$fd_key]);
                }
                break;

            case self::zsEvent_Timerout:
            case self::ZsEvent_Interval:
                if (isset($this->_eventTimer[$fd]))
                {
                    $this->_eventTimer[$fd]->del();
                    unset($this->_eventTimer[$fd]);
                }
                break;
        }
        return true;
    }

    /**
     * Timer callback.
     * @param null $fd
     * @param int $what
     * @param int $timer_id
     */
    public function timerCallback($fd, $what, $param)
    {
        $timer_id = $param[4];

        if ($param[2] === self::EV_TIMER_ONCE)
        {
            $this->_eventTimer[$timer_id]->del();
            unset($this->_eventTimer[$timer_id]);
        }

        try
        {
            call_user_func_array($param[0], $param[1]);
        }
        catch (\Exception $e)
        {
            exit(250);
        }
        catch (\Error $e)
        {
            exit(250);
        }
    }
}
