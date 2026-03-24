PRJ=os32

clear
rm "${PRJ}"
gcc -g "${PRJ}.c" -o "${PRJ}" -lm
cat test3.bin | ./${PRJ}