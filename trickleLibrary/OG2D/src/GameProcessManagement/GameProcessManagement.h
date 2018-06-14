#include "OGSystem\OGsystem.h"

class GameManager : public TaskObject
{
	unsigned int Seconds;
	unsigned int Minute;
	unsigned int timeCnt;
	bool isclear;
	bool M_flag[3];
	bool isMaxTime();
	bool OutData();
	bool ComparisonData();
	void OutFileData();
public:
	bool isClear();
	unsigned int SecondsTime() const;
	unsigned int MinuteTime() const;
	explicit GameManager();
	void UpDate() override;
	static void ResetData();
	virtual ~GameManager();
	typedef std::shared_ptr<GameManager> SP;
	static SP Create(bool = true);
};