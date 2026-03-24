PRJ=os41

clear
rm "${PRJ}"
gcc -g "${PRJ}.c" -o "${PRJ}" -lm
cat test4-6.bin | ./${PRJ}