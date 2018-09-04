#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"
/**
*@brief	:ゴールオブジェクト
*/
class Goal : public GameObject, public TaskObject
{
	/**
	*@class	CameraAnim
	*カメラ操作を行うclass
	*/
	class CameraAnim
	{
		//!	開始位置
		Vec2 startPos;
		//!	終了位置
		Vec2 endPos;
		//!	移動主要時間
		unsigned int time;
		//!	X座標用Easing
		Easing easing_x;
		//!	Y座標用Easing
		Easing easing_y;
	public:
		/**
		*@brief	:イージングを登録する
		*@param	:Vec2 start	開始位置
		*@param	:Vec2 end	終了位置
		*@param	:unsigned int time	所要時間
		*/
		void SetEasing(const Vec2& start, const Vec2& end, const unsigned int time);
		/**
		*@brief	:移動値を返す
		*@return:移動後の値
		*/
		Vec2 Move();
		/**
		*@brief	:移動中かどうかを返す
		*@return:移動中ならtrue
		*/
		bool isPlay();
	};
	/**
	*enum Mode
	*現在の状態を管理する
	*/
	enum Mode
	{
		//!	初期
		Non,
		//!	カメラ移動
		Form1,
		//!	花咲き
		Form2,
		//!	カメラを戻す
		Form3,
		//!	終了
		End,
	};
	//!	クリア状態
	bool isClear;
	//!	入力を制限かけるかどうか
	bool isCheck;
	//!	普段のゲーム用カメラのロックを設定解除
	bool cameraLock;
	//!	アニメーション用カウント
	unsigned int animCnt;
	//!	個別ID
	unsigned int ID;
	//!	使用画像
	Texture* image;
	//!	光用画像
	Texture lightTex;
	//!	水用当たり判定
	GameObject foot;
	//!	描画位置
	Box2D draw;
	//! 描画画像位置
	Box2D src;
	//!	当たってきた色の情報
	Paint::PaintColor color;
	//!	カラー情報
	Paint::PaintColor termsColor;
	//!	現在の状況
	Mode mode;
	//!	カメラの位置Easing管理
	CameraAnim cm_Pos;
	//!	カメラのサイズEasing管理
	CameraAnim cm_Size;
	//!	移動前カメラ位置
	Vec2* precmPos;
	//!	移動前カメラサイズ
	Vec2* precmSize;
	//!	サウンドのファイル名格納
	std::string soundname;
	/**
	*@brief	:他のゴールの状態を確認する
	*@return:bool 全てゴールしていればtrue
	*/
	bool isGoalCheck();
	/**
	*@brief	:constructor
	*@param	:Vec2 pos	生成位置
	*/
	explicit Goal(const Vec2& pos);
	//! スマートポインタ
	typedef std::shared_ptr<Goal> SP;
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Goal();
	/**
	*@brief	:ゴールのカラーを登録する
	*@param	:Paint::PaintColor color	指定したい色情報
	*/
	void SetColor(const Paint::PaintColor& color);
	/**
	*@brief	:登録されているカラーを返す
	*@return:Paint::PaintColor カラー情報
	*/
	Paint::PaintColor GetColor() const;
	/**
	*@brief	:登録されている色と現在の色が等しいか判定する
	*@return:bool 同じならばtrue
	*/
	bool ColorCheck() const;
	/**
	*@brief	:クリア状況を返す
	*@return:bool クリアしているならばtrue
	*/
	bool GetClear() const;
	/**
	*@brief	:使用画像を登録する
	*@param	:Texture* tex	画像のポインタ
	*/
	void SetTexture(Texture*);
	/**
	*@brief	:水との判定を行う
	*@return:bool 当たっていればtrue
	*/
	bool WaterHit();
	/**
	*@brief	:カメラの固定状況を返す
	*@return:固定しているならばtrue
	*/
	bool GetLock() const;
	/**
	*@brief	:個別IDを返す
	*@return:unsigned int 個別ID
	*/
	unsigned int GetID() const;	
	/**
	*@brief	:タスク生成
	*@param	:Vec2 pos 位置
	*@return:Goal 成功に失敗した場合nullptrを返す
	*/
	static SP Create(const Vec2& pos);	
	Sound sound;     //サウンド生成
	bool lightCreate;
	Vec2 lightscale;
};