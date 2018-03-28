## 基本的な流れ
ゲーム内で使うすべてのオブジェクトたちにObjectクラスを継承してください。

このObjectクラスを継承したオブジェクトの初期化部分に、オブジェクトの種類を表すタグを付けてください。

当たり判定はオブジェクトの初期化部分に下のようにつけて下さい。

現在クラスの中にいるすべてのメンバー関数・変巣はそのまま使えます。

当たり判定を行いたいオブジェクトはCollisionManagerに登録してください。

Task_Gameでcm.AddChild()関数で登録できます。

## 例題

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
