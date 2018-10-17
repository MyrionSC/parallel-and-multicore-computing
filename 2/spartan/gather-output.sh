#rm output.txt > /dev/null 2>&1 # hide output

DATE=$(date +%Y-%m-%d-%H-%M-%S)
FILE=results/$DATE.txt

cat output/*.out >> $FILE 
#rm output/*.out
