#!/bin/bash
# interpreter
echo '!'                #cannot $var
echo "\n"

var = value             #equal
var=value               #set
echo ${var} $var

cat /proc/$PID/environ | tr '\0' '\n' #tr replace char

expert PATH="$PATH:/home/..." #add new environ
echo ${#var}            #return length of var
echo $0                 #$SHELL

#int add
no1=1;
no2=2;
let res=no1+no2
let res++
let res+=1
res=$[ no1 + no2 ]
res=$[ $no1 + 5 ]
res=$((no1 + 5))

#redirect >  empty target file
#         >> append
# stdin - 0 stdout - 1 strerr - 2
cmd 2>&1 log.txt        #both 1&2
cmd | tee log.txt       #stdout work fine and redirect


arr={1,2,3,4}
arr[0]="str1"
arr[1]="str2"
echo ${arr[0]}
echo ${arr[*]}          #list all
declare -A arr
arr=([key1]='str1' [key2]='str2')
echo ${arr[key1]}
echo ${!arr[*]}         #list all index

start=$(data +%s)
end=$(data +%s)
difference=$(( end - start )) #time<script>

