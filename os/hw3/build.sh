PRJ=os22

rm "${PRJ}"
gcc -g "${PRJ}.c" -o "${PRJ}" -lm
cat test.bin | ./${PRJ}