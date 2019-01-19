ps aux | grep main_muti_process.py | awk '{print $2}'  | xargs kill
