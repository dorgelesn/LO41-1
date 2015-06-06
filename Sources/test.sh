#!/bin/bash
truncate -s 0 test.txt
for i in `seq 1 10`;
do
	echo $i
	echo ------------------>>test.txt	
	echo $i >>test.txt
	echo ------------------>>test.txt	
	./main >> test.txt
done
