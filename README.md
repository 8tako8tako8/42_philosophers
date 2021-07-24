# Philosophers

## Overview
42Tokyoの課題。
食事する哲学者問題。

<img width="272" alt="スクリーンショット 2021-07-24 22 58 56" src="https://user-images.githubusercontent.com/65395999/126870837-6aaaf24c-eedd-4d23-afa2-c1b0727138af.png">

## Rule
```
ルール１：哲学者は、フォークを取る、食事する、寝る、考える、この４つを繰り返す。
ルール２：食事をするためにはフォークが２本必要。
ルール３：フォークは各哲学者が１本所持している。
ルール４：食事をしなければ哲学者が死ぬ
```

## Requirement
- mac Catalina 10.15.7

## Usage
```
git clone ...
cd 42_philosophers
make
./philo <哲学者の人数> <死ぬまでの時間> <食事時間> <睡眠時間> (<最低限の食事回数>)
```
