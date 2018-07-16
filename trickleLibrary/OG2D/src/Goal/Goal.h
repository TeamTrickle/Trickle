#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"

class Goal : public GameObject, public TaskObject
{
	class CameraAnim
	{
		Vec2 startPos;
		Vec2 endPos;
		unsigned int time;
		Easing easing_x;
		Easing easing_y;
	public:
		void Set(const Vec2& start, const Vec2& end, const unsigned int time);
		Vec2 Move();
		bool isPlay();
	};
	enum Mode
	{
		Non,	//初期
		Form1,	//カメラ移動
		Form2,	//花咲き
		Form3,	//カメラ戻り
		End,	//終了
	};
	bool isClear;
	bool isCheck;
	bool cameraLock;
	unsigned int animCnt;
	unsigned int ID;
	Texture* image;
	Texture lightTex;
	GameObject foot;
	Box2D draw;
	Box2D src;
	Paint::PaintColor color;
	Paint::PaintColor termsColor;
	Mode mode;
	CameraAnim cm_Pos;
	CameraAnim cm_Size;
	Vec2* precmPos;
	Vec2* precmSize;
	bool isGoalCheck();
	std::string soundname;   //サウンドのファイル名格納
	bool testClear;
public:
	explicit Goal(const Vec2& pos);
	virtual ~Goal();
	void SetColor(const Paint::PaintColor&);	//ゴールのカラーを指定する
	Paint::PaintColor GetColor() const;			//ゴールに指定されている色を返す
	bool ColorCheck() const;					//色が正しいかを判定する
	void UpDate() override;						//更新
	void Render2D() override;					//描画
	bool GetClear() const;						//クリアしているかを返す
	void SetTexture(Texture*);					//描画する画像を登録する
	bool WaterHit();							//水との判定を行う
	bool GetLock() const;						//カメラの固定状況を返す
	unsigned int GetID() const;					//登録されているIDを返す
	typedef std::shared_ptr<Goal> SP;			//スマートポインタ
	static SP Create(const Vec2& pos, bool = true);	//生成処理
	Sound sound;     //サウンド生成
	bool lightCreate;
	Vec2 lightscale;
	void TestGoal();
};