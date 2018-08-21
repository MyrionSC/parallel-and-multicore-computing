#rm output.txt > /dev/null 2>&1 # hide output

DATE=$(date -I's')
FILE=results/$DATE.txt

echo execution date: $DATE >> $FILE
echo "*******" >> $FILE
echo " " >> $FILE
cat output/*.out >> $FILE 
#rm output/*.out
