```sh
DAY=01
cc ./src/main.c ./src/util/*.c ./src/solutions/day_$DAY.c -o solve
./solve test
./solve $DAY
```
