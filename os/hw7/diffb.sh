PRJ=os41
TCASE=10

clear
rm "${PRJ}" result.txt
gcc -g "${PRJ}.c" -o "${PRJ}" -lm
cat test4-${TCASE}.bin | ./${PRJ} >> result.txt
diff -y -w result.txt result-${TCASE}.txt
diff -q -w result.txt result-${TCASE}.txt