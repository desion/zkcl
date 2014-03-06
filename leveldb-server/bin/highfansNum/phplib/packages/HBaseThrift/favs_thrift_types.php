<?php
/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
include_once $GLOBALS['THRIFT_ROOT'].'/Thrift.php';


class request {
  static $_TSPEC;

  public $start = null;
  public $num = null;
  public $query = null;
  public $uid = null;
  public $debug = null;
  public $querystring = null;

  public function __construct($vals=null) {
    if (!isset(self::$_TSPEC)) {
      self::$_TSPEC = array(
        1 => array(
          'var' => 'start',
          'type' => TType::I32,
          ),
        2 => array(
          'var' => 'num',
          'type' => TType::I32,
          ),
        3 => array(
          'var' => 'query',
          'type' => TType::STRING,
          ),
        4 => array(
          'var' => 'uid',
          'type' => TType::STRING,
          ),
        5 => array(
          'var' => 'debug',
          'type' => TType::STRING,
          ),
        6 => array(
          'var' => 'querystring',
          'type' => TType::MAP,
          'ktype' => TType::STRING,
          'vtype' => TType::STRING,
          'key' => array(
            'type' => TType::STRING,
          ),
          'val' => array(
            'type' => TType::STRING,
            ),
          ),
        );
    }
    if (is_array($vals)) {
      if (isset($vals['start'])) {
        $this->start = $vals['start'];
      }
      if (isset($vals['num'])) {
        $this->num = $vals['num'];
      }
      if (isset($vals['query'])) {
        $this->query = $vals['query'];
      }
      if (isset($vals['uid'])) {
        $this->uid = $vals['uid'];
      }
      if (isset($vals['debug'])) {
        $this->debug = $vals['debug'];
      }
      if (isset($vals['querystring'])) {
        $this->querystring = $vals['querystring'];
      }
    }
  }

  public function getName() {
    return 'request';
  }

  public function read($input)
  {
    $xfer = 0;
    $fname = null;
    $ftype = 0;
    $fid = 0;
    $xfer += $input->readStructBegin($fname);
    while (true)
    {
      $xfer += $input->readFieldBegin($fname, $ftype, $fid);
      if ($ftype == TType::STOP) {
        break;
      }
      switch ($fid)
      {
        case 1:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->start);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 2:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->num);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 3:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->query);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 4:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->uid);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 5:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->debug);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 6:
          if ($ftype == TType::MAP) {
            $this->querystring = array();
            $_size0 = 0;
            $_ktype1 = 0;
            $_vtype2 = 0;
            $xfer += $input->readMapBegin($_ktype1, $_vtype2, $_size0);
            for ($_i4 = 0; $_i4 < $_size0; ++$_i4)
            {
              $key5 = '';
              $val6 = '';
              $xfer += $input->readString($key5);
              $xfer += $input->readString($val6);
              $this->querystring[$key5] = $val6;
            }
            $xfer += $input->readMapEnd();
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        default:
          $xfer += $input->skip($ftype);
          break;
      }
      $xfer += $input->readFieldEnd();
    }
    $xfer += $input->readStructEnd();
    return $xfer;
  }

  public function write($output) {
    $xfer = 0;
    $xfer += $output->writeStructBegin('request');
    if ($this->start !== null) {
      $xfer += $output->writeFieldBegin('start', TType::I32, 1);
      $xfer += $output->writeI32($this->start);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->num !== null) {
      $xfer += $output->writeFieldBegin('num', TType::I32, 2);
      $xfer += $output->writeI32($this->num);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->query !== null) {
      $xfer += $output->writeFieldBegin('query', TType::STRING, 3);
      $xfer += $output->writeString($this->query);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->uid !== null) {
      $xfer += $output->writeFieldBegin('uid', TType::STRING, 4);
      $xfer += $output->writeString($this->uid);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->debug !== null) {
      $xfer += $output->writeFieldBegin('debug', TType::STRING, 5);
      $xfer += $output->writeString($this->debug);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->querystring !== null) {
      if (!is_array($this->querystring)) {
        throw new TProtocolException('Bad type in structure.', TProtocolException::INVALID_DATA);
      }
      $xfer += $output->writeFieldBegin('querystring', TType::MAP, 6);
      {
        $output->writeMapBegin(TType::STRING, TType::STRING, count($this->querystring));
        {
          foreach ($this->querystring as $kiter7 => $viter8)
          {
            $xfer += $output->writeString($kiter7);
            $xfer += $output->writeString($viter8);
          }
        }
        $output->writeMapEnd();
      }
      $xfer += $output->writeFieldEnd();
    }
    $xfer += $output->writeFieldStop();
    $xfer += $output->writeStructEnd();
    return $xfer;
  }

}

class result {
  static $_TSPEC;

  public $m = null;
  public $sn = null;
  public $en = null;
  public $time = null;
  public $body = null;

  public function __construct($vals=null) {
    if (!isset(self::$_TSPEC)) {
      self::$_TSPEC = array(
        1 => array(
          'var' => 'm',
          'type' => TType::I32,
          ),
        2 => array(
          'var' => 'sn',
          'type' => TType::I32,
          ),
        3 => array(
          'var' => 'en',
          'type' => TType::I32,
          ),
        4 => array(
          'var' => 'time',
          'type' => TType::I64,
          ),
        5 => array(
          'var' => 'body',
          'type' => TType::LST,
          'etype' => TType::MAP,
          'elem' => array(
            'type' => TType::MAP,
            'ktype' => TType::STRING,
            'vtype' => TType::STRING,
            'key' => array(
              'type' => TType::STRING,
            ),
            'val' => array(
              'type' => TType::STRING,
              ),
            ),
          ),
        );
    }
    if (is_array($vals)) {
      if (isset($vals['m'])) {
        $this->m = $vals['m'];
      }
      if (isset($vals['sn'])) {
        $this->sn = $vals['sn'];
      }
      if (isset($vals['en'])) {
        $this->en = $vals['en'];
      }
      if (isset($vals['time'])) {
        $this->time = $vals['time'];
      }
      if (isset($vals['body'])) {
        $this->body = $vals['body'];
      }
    }
  }

  public function getName() {
    return 'result';
  }

  public function read($input)
  {
    $xfer = 0;
    $fname = null;
    $ftype = 0;
    $fid = 0;
    $xfer += $input->readStructBegin($fname);
    while (true)
    {
      $xfer += $input->readFieldBegin($fname, $ftype, $fid);
      if ($ftype == TType::STOP) {
        break;
      }
      switch ($fid)
      {
        case 1:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->m);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 2:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->sn);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 3:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->en);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 4:
          if ($ftype == TType::I64) {
            $xfer += $input->readI64($this->time);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 5:
          if ($ftype == TType::LST) {
            $this->body = array();
            $_size9 = 0;
            $_etype12 = 0;
            $xfer += $input->readListBegin($_etype12, $_size9);
            for ($_i13 = 0; $_i13 < $_size9; ++$_i13)
            {
              $elem14 = null;
              $elem14 = array();
              $_size15 = 0;
              $_ktype16 = 0;
              $_vtype17 = 0;
              $xfer += $input->readMapBegin($_ktype16, $_vtype17, $_size15);
              for ($_i19 = 0; $_i19 < $_size15; ++$_i19)
              {
                $key20 = '';
                $val21 = '';
                $xfer += $input->readString($key20);
                $xfer += $input->readString($val21);
                $elem14[$key20] = $val21;
              }
              $xfer += $input->readMapEnd();
              $this->body []= $elem14;
            }
            $xfer += $input->readListEnd();
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        default:
          $xfer += $input->skip($ftype);
          break;
      }
      $xfer += $input->readFieldEnd();
    }
    $xfer += $input->readStructEnd();
    return $xfer;
  }

  public function write($output) {
    $xfer = 0;
    $xfer += $output->writeStructBegin('result');
    if ($this->m !== null) {
      $xfer += $output->writeFieldBegin('m', TType::I32, 1);
      $xfer += $output->writeI32($this->m);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->sn !== null) {
      $xfer += $output->writeFieldBegin('sn', TType::I32, 2);
      $xfer += $output->writeI32($this->sn);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->en !== null) {
      $xfer += $output->writeFieldBegin('en', TType::I32, 3);
      $xfer += $output->writeI32($this->en);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->time !== null) {
      $xfer += $output->writeFieldBegin('time', TType::I64, 4);
      $xfer += $output->writeI64($this->time);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->body !== null) {
      if (!is_array($this->body)) {
        throw new TProtocolException('Bad type in structure.', TProtocolException::INVALID_DATA);
      }
      $xfer += $output->writeFieldBegin('body', TType::LST, 5);
      {
        $output->writeListBegin(TType::MAP, count($this->body));
        {
          foreach ($this->body as $iter22)
          {
            {
              $output->writeMapBegin(TType::STRING, TType::STRING, count($iter22));
              {
                foreach ($iter22 as $kiter23 => $viter24)
                {
                  $xfer += $output->writeString($kiter23);
                  $xfer += $output->writeString($viter24);
                }
              }
              $output->writeMapEnd();
            }
          }
        }
        $output->writeListEnd();
      }
      $xfer += $output->writeFieldEnd();
    }
    $xfer += $output->writeFieldStop();
    $xfer += $output->writeStructEnd();
    return $xfer;
  }

}

?>
