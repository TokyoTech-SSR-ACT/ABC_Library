# ABC_Library
## What's ABC Library?
本リポジトリは，東京工業大学ロボット技術研究会ACTが開発した，多軸ロボット駆動用の汎用制御基板「ACT Base Circuit（以下，ABC）」のための標準ライブラリです．
本ライブラリでは，BNO055やNeoPixelなどの一般部品に対するピンアサイン，並びにABCオリジナル機能に対する関数の実装をしています．

ABC_LibraryはArdiono frameworkを用いて構成されています．
また，[Bluepad32](https://github.com/ricardoquesada/bluepad32)を導入することにより，複数種類のゲームコントローラによるBlueTooth遠隔操作が可能となっています．

## 導入
本ライブラリの導入に当たっては，Bluepad32フレームワークをArduino環境へ構築する必要があります．以下に従って，導入をしてください．

### Arduino IDEへの導入
[こちら](https://bluepad32.readthedocs.io/en/latest/plat_arduino/)の公式ドキュメントを参考にしてください．

### PlatformIOへの導入
プロジェクトのplatformio.iniへ，以下のコードを追記してください．
```
platform_packages =
   framework-arduinoespressif32@https://github.com/maxgerhardt/pio-framework-bluepad32/archive/refs/heads/main.zip
```
[参考文献](https://community.platformio.org/t/use-bluepad32-library-in-pio/46745)

## 使用するリポバッテリーセル数の設定
ABCには，現在の電源電圧を監視する機能が搭載されています．これにより，バッテリーの過放電を抑制します．

その設定ファイルとして，```abc_config.hpp```を用意いたしました．適宜使用するバッテリのセル数を変更してください．

## NeoPixel, BNO055, Feetech サーボモータについて
ABCはこれらのものを搭載，または動作させる能力を有していますが，これら部品は外部ライブラリが公開されています．
そちらを別途お使いください．

## コンタクト
　技術的お問い合わせは，本リポジトリのIssueよりお願いいたします．

　その他の問い合わせについては，[主任開発者HP内のコンタクトに記載された手段](https://sugi-kmmm.github.io/contact.html)により行ってください．また，教育機関の講義で使用する場合等においては，特段の連絡は必要ありませんが，ご報告していただけますと製作者のモチベーションにつながります．ぜひご一報いただけますと幸いです．

## 開発者
開発者は[Sugi_kmmm](https://github.com/Sugi-kmmm)です．


## LICENSE情報
ABC_Libraryは以下のクリエイティブ・コモンズ・ライセンスにより保護されています．

ABC_Library © 2025 by [
TokyoTech-SSR-ACT](https://github.com/TokyoTech-SSR-ACT) is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1).