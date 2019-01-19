<?php

class test extends Thread {
    private $name = '';
    private $res = null;
 
    public function __construct($name, $res){
        $this->name = $name;
        $this->res = $res;
    }
    public function run(){
        while(!feof($this->res)) {
            if(flock($this->res, LOCK_EX)) {
                $data = fgets($this->res);
                $data = trim($data);
                echo "Thread {$this->name} Read {$data} \r\n";
                sleep(1);
                flock($this->res, LOCK_UN);
            }
        }
    }
}
 
$fp = fopen('./test.log', 'rb');
 
$threads[] = new test('a', $fp);
$threads[] = new test('b', $fp);
 
foreach($threads as $thread) {
    $thread->start();
}
 
foreach($threads as $thread) {
    $thread->join();
}

?>

