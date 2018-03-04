##### head file

関数の宣言はヘッダファイルに書きましょう

##### about head file

```
/*iamhead.h*/
#ifndef I_AM_HEAD_H //名前は任意かな?
#define I_AM_HEAD_H //この名前を定義

#include <stdio.h>

void foo();
int mac();

#endif //I_AM_HEAD_H
```

###### about makefile(GNU make)

(http://www.ie.u-ryukyu.ac.jp/~e085739/c.makefile.tuts.html)
(これ以上高度なことはやらない)

```
# Makefile2
.PHONY: all
all: main

main: main.o
  gcc -o main main.o

main.o: main.c
  gcc -c main.c

main.o: str.h

.PHONY: clean
clean:
  rm -rf main main.o
```
