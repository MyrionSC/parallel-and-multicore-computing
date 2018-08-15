echo execution date: $(date) >> output.txt
echo "*******" >> output.txt
echo " " >> output.txt
cat *.out >> output.txt && rm *.out
