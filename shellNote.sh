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

function fun()
{
    echo $1, $2
    echo "$@"           #list all params
    return 0
}
echo $?                 #last return value
#Fork bomb
#:(){ :|:& };:

cmd_output=$(ls | cat -n)
cmd_output=`ls | cat -n`

repeat()
{
    while :             #true 
    do
        $@ && return
    done
}

find . -maxdepth 1 \( -name "*.txt" -o -name "*.cfg" \) -exec cat {} \;>out.txt #-iname ignore case
#-type d dic, f file
#-delete

#xargs -n X         #X param in oneline
#xargs -d X         #split by X
#xargs -I {} cmd {}
find . -type f -name "something" -print0 | xargs -0 rm -f
find . -type f -name "*.c" -print0 | xargs -0 wc -l #count all .c files total lines

echo 12345 | tr '1-5' '54321'
#-d '[set1]'    delete in [set1]
#-s ''          compress
#-c             complementary set

sort out.txt | uniq     # -c count  #-d repeat line