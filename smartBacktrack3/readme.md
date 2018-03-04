#README

2017-Feb-03 @author: candy water

本プログラムは、1-page book embedding問題を解くバックトラックアルゴリズムである。

valgrindでメモリチェック済み。

#構成

メイン:main.cc h_head.h

データ構造:classes.cc class_head.h

交差数を数える:func.cc

バックトラック:backtrack.cc

ヒューリスティック:greedyAppend.cc circularSifting.cc

main.ccをいじれば、ヒューリスティックアルゴリズムだけを実行することができる。

#コンパイル方法

コマンドラインの実行できる環境。

```
$ make
$ ./a.out < inputData
```

#入力形式

```
n m
k
p_1
p_2
p_n
v_1 u_1 
v_2 u_2 
v_n u_n 
```

#出力形式

```
n m
k
p_1
p_2
p_n
v_1 u_1 [0]
v_2 u_2 [0]
v_n u_n [0]
```

#入力インスタンス

(1)ランダムグラフ(頂点数10-14、辺密度それぞれ0.1, 0.3, 0.5, 0.6, 0.75, 0.8, 0.9, 1.0である)

(2)木幅コンテスト100問
木幅コンテスト、exact奇数番の公開された100問

//2017 PACE
https://pacechallenge.wordpress.com/pace-2017/track-a-treewidth/

