#!/bin/bash

# daily topic user mining
#if [ $# -ne 1 ]; then
#    echo -e "parameter error \n Usage: ./sh_file inputfile_path"
#	exit 1
#fi

jobname="chengyun5_feasext"

input_dir=$1
curdir=$(basename $input_dir)
output_dir=$2

mapnums=400
reducenums=20

mapper_file="./feature_extract.py"
mapper_exec="python ./feature_extract.py"

# hadoop client path
hadoop_bin="/usr/local/hadoop/bin/hadoop"
# depends library
lib_home="/usr/local/hadoop/share/hadoop/tools/lib"
hadoop_jar="$lib_home/hadoop-streaming-2.7.3.jar"
scdh4_jar="$lib_home/mapreduce-client.jar"

# clear data already exists
${hadoop_bin} fs -rm -r -skipTrash ${output_dir} 2&>/dev/null
input=${input_dir}
output=${output_dir}

echo "output_dir"$output_dir
echo "input: "$input
echo "output: "$output

# 请在此修改参数
# 1) -D开头的参数为通用参数, 必须放在非-D参数的前面, -D取代老版本的jobConf
# 2) 可用的参数请参看: ./docs/hadoop-streaming参数指南.txt
# 3) jar以及-libjars是必须的, 切勿修改
#
function job_emit_main() {
	cmd="${hadoop_bin} jar $hadoop_jar -libjars '$scdh4_jar'"
	cmd="${cmd} -files ./util"
	cmd="${cmd} -D mapred.job.queue.name=production"
	cmd="${cmd} -D mapred.job.name=${jobname}"
	cmd="${cmd} -D mapred.map.tasks=${mapnums}"
	cmd="${cmd} -D mapred.reduce.tasks=${reducenums}"
	cmd="${cmd} -D mapreduce.map.memory.mb=4096"
	cmd="${cmd} -D mapred.map.tasks.speculative.execution=false"
	cmd="${cmd} -D mapred.reduce.tasks.speculative.execution=false"
	cmd="${cmd} -D mapred.output.compress=true"
	cmd="${cmd} -D mapred.output.compression.codec=org.apache.hadoop.io.compress.GzipCodec"
	cmd="${cmd} -outputformat com.yunrang.hadoop.app.common.output.NoTabTextOutputFormat"
	cmd="${cmd} -input '${input}'"
	cmd="${cmd} -output '${output}'"
    cmd="${cmd} -mapper '${mapper_exec}'"
	cmd="${cmd} -reducer 'cat'"
	cmd="${cmd} -file ${mapper_file}"
	cmd="${cmd} -file ./stop_words"
    cmd="${cmd} -cacheArchive '/tmp/chengyun5/mr_pack.tar.gz#mr_pack'"
    cmd="${cmd} -cacheArchive '/tmp/chengyun5/seg_data.tar.gz#seg'"
	echo "${cmd}"
	eval $cmd
}

#cmd="${cmd} -reducer 'cat'"
#cmd="${cmd} -cacheArchive '/tmp/chengyun5/jieba-0.38.tar.gz#jieba'"
#cmd="${cmd} -mapper '${mapper_exec}'"
job_emit_main  &> ./log/hadoop_log

echo 'Job Emit Done!'
