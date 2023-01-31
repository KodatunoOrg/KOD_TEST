# KOD_TEST
Kodatuno Kernel の動作確認用サンプル Qt プロジェクト

## Kodatuno について
Kodatuno は，金沢大学マンマシン研究室で開発されているオープンソースのCAMカーネルです．
本家は <http://www-mm.hm.t.kanazawa-u.ac.jp/research/kodatuno/>

## 本リポジトリについて
本家 Kodatuno から GUI に相当する部分（Kernel以外）を抜き出し，Qt プロジェクトとして構築しなおしたものです．
このサンプルで Kodatuno Kernel の動作を確認したり，セミナー（勉強会）を実施したりします．  
ファイル構成を含めてまだまだ試行中です．

## 実行方法

* Qtのセットアップは [本家インストールしてみた](http://www-mm.hm.t.kanazawa-u.ac.jp/research/kodatuno/inst/) から
 [セットアップマニュアル(R3.5/Windows10)](http://www-mm.hm.t.kanazawa-u.ac.jp/research/kodatuno/inst/20220617-01/SetUpGuide_R3.5_win10.pdf) を参考にしてください．

* Kodatuno Kernel を用意してください．
ライブラリのビルド方法は <https://github.com/KodatunoOrg/Kernel> を参照してください．

* QtからKOD_TEST.proのプロジェクトファイルを開き，プロジェクトの設定を各自の環境に合わせて変更してください．

Kernelのインクルードパス
```
INCLUDEPATH += \
    SYS/ \
    UA/ \
    GUI/ \
    $$PWD/../Kernel/include/ # 各自の環境に合わせて変更
```

ライブラリファイル
```
# libKernel は OpenGL の前に定義しないとリンクエラーになる
LIBS += -L$$PWD/../Kernel/build/debug/ -llibKernel # 各自の環境に合わせて変更
LIBS += -lopengl32 -lglu32
```
