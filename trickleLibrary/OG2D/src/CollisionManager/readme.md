## 基本的な流れ
ゲーム内で使うすべてのオブジェクトたちにObjectクラスを継承してください。

このObjectクラスを継承したオブジェクトの初期化部分に、オブジェクトの種類を表すタグを付けてください。

当たり判定はオブジェクトの初期化部分に下のようにつけて下さい。

現在クラスの中にいるすべてのメンバー関数・変巣はそのまま使えます。

当たり判定を行いたいオブジェクトはCollisionManagerに登録してください。

Task_Gameでcm.AddChild()関数で登録できます。

----------

＋　CollisionProcessを定義しないとStaticObject扱いになります。

＋　InとOutを使わないときには定義しなくてもOKです。

## 処理用関数の説明
Objectを継承したクラスのみ使えます。
* CollisionIn - 当たり判定が起きったとき１回だけ呼ばれる
* CollisionProcess - 当たってる時に毎フレーム呼ばれる
* CollisionOut - 当たり判定が終わった時１回だけ呼ばれる

## 例題
CollisionIn, CollisionOutも下と同じく使えます。

Task_Game.cpp

    #include "Task_Game.h"
    void Game::Initialize()
    {
        std::cout << "Game初期化" << std::endl;
        player.Initialize();
        


        ...(省略)

        

        cm.AddChild(&player);
    }

Enemy.cpp

    bool Enemy::Initialize() {
        /* タグを設定します。このタグは他のオブジェクトから当たり判定をするとき使われます */
        this->objectTag = "Enemy";

        /* 当たり処理はこんな形にしてください */
        Object::CollisionProcess = [&](const Object& o_) {
            // この中に処理を書いてください
            if (o_.objectTag == "Player") {
                Attack();
                (Player)o_.hp -= 1;
                /* こんな形の処理を書くことができます */
            }
        };
    }
