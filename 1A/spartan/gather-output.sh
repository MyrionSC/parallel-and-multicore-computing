rm output.txt > /dev/null 2>&1 # hide output
echo execution date: $(date) >> output.txt
echo "*******" >> output.txt
echo " " >> output.txt
cat *.out >> output.txt && rm *.out
