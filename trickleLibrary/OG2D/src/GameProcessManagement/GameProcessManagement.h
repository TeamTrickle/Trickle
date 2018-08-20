#include "OGSystem\OGsystem.h"
/**
*@brief	:ゲーム進行管理class
*/
class GameManager : public TaskObject
{
	//!	経過秒タイム
	unsigned int Seconds;
	//!	経過分タイム
	unsigned int Minute;
	//!	経過カウント
	unsigned int timeCnt;
	//!	ゲームクリア後ゲーム終了するまでの時間
	unsigned int time;
	//! クリア状態
	bool isclear;
	//!	ミッションクリア状態
	bool M_flag[3];	
	//!	スマートポインタ
	typedef std::shared_ptr<GameManager> SP;
	/**
	*@brief	:タイマーの上限確認
	*@return:bool タイマー上限に達していた場合true
	*/
	bool isMaxTime();
	/**
	*@brief	:今の記録を保存する
	*@return:bool 保存に成功すればtrue
	*/
	bool OutData();
	/**
	*@brief	:前までの最高記録と比較しよい方を保存する
	*@return:bool 最大記録の保存に成功すればtrue
	*/
	bool ComparisonData();
	/**
	*@brief	:現在のデータをそのまま保存する
	*/
	void OutFileData();
	/**
	*@brief	:constructor	各値の初期化
	*/
	explicit GameManager();
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
public:
	/**
	*@brief	:クリア状況を返す
	*@return:bool ゲームクリアしていればtrue
	*/
	bool isClear();
	/**
	*@brief	:現在の秒タイムを返す
	*@return:unsigned int 秒タイム
	*/
	unsigned int SecondsTime() const;
	/**
	*@brief	:現在の分タイムを返す
	*@return:unsigned int 分タイム
	*/
	unsigned int MinuteTime() const;
	/**
	*@brief	:セーブデータの初期化
	*/
	static void ResetData();
	/**
	*@brief	:destructor	次生成タスクを指定する
	*/
	virtual ~GameManager();
	/**
	*@brief	:タスク生成
	*@reutrn:GameManager	生成に失敗した場合はnullptr
	*/
	static SP Create();
};