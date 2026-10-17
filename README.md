# AppleGame

raylib + C++ で作ったミニゲーム

**プレイはこちら** → https://morumoru.jp/works/raylib-apple/

## 概要

- プレイヤーの体力＝大きさは時間経過で縮んでいき、0になるとゲームオーバー
- リンゴに触れると回復する。リンゴは画面外から生成され、画面内に入ってくる
- 一定時間ごとに自分の後ろにウンチが出現する。触れるとダメージを受ける
- 操作：矢印キーで移動、Enterでスタート／リスタート

## ビルド

- Visual Studio 2022 + MSVC（C++20）
- `Game.sln` を開いて F5（Debug / x64）
- raylib 6.0 は `vendor/raylib/` に同梱済み（追加のセットアップは不要）
