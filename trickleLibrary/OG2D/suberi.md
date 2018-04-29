氷に滑るオブジェクトの作り方
----

1. Objectを継承します。
2. Update関数を実装して、その中にUpdatePhysics()関数を読んでください

        void Block::Update() {
            Object::UpdatePhysics();
            // 以下略
        }

3. オブジェクトの位置を決める処理のなかにこの関数の値を足してください

        ...
        this->position = est * speed + Object::UseFricition();
        ...