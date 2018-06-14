#include "OGSystem\OGsystem.h"

class GameManager : public TaskObject
{
public:
	enum Achievement
	{
		Flag1 = 1 << 0,		//�t���O1
		Flag2 = 1 << 1,		//�t���O2
		Flag3 = 1 << 2,		//�t���O3
		Flag4 = 1 << 3,		//�t���O4
		Master = 0x0F,		//�S�Ẵt���O���B������
	};
private:
	//�~�b�V�������ڊ֘A
	struct Mission
	{
		//�t���O�֘A
		void Flag_Input(Achievement);
		void Flag_Judge_Clear();

		//�t���O��i�[����ϐ�
		int  Flag;
	};
	//�t���O�֘A
	void Flag_Judge(unsigned short& mapnumber, std::ofstream& fin);

	//�e���ϐ�

	//�~�b�V�����֘A
	Mission mission;					//�B�����ڂ̏���

	//��{�̏��
	bool gameclear_flag;                 //�l�X�ȃt���O��i�[����
	bool pause_flag;					 //�|�[�Y��ʂ���^�C�g���֖߂ꂳ���ꍇ�̑΍�

	//�^�C�}�[�֘A
	Timer::SP timer;                     //�^�C�}�[�̃Z�b�g���

	

	const char* TimeFilePath = "./data/Result/Result.dat";

private:
	//�S�[������֘A
	void Goal_Check();		//�S�[���̔����`�F�b�N���܂�
	void Goal_Event();		//�S�Ă��S�[����ԂȂ烊�U���g��ʂɍs���܂�

	//���U���g��ʂɃf�[�^�𑗂�֐��֘A
	void File_Writing();				 //�t���[���������
public:
	std::string taskName;
	virtual ~GameProcessManagement();
	typedef std::shared_ptr<GameProcessManagement> SP;
	static GameProcessManagement::SP Create(bool = true);
	GameProcessManagement();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//���

	//���̃N���X�Ŏg�p����֐�
	bool isAllGoal();		//�S�Ă��S�[����Ă��邩�ǂ�����Ԃ��܂�
	int  GetFlag();			//���݂̃X�e�[�W�~�b�V�����t���O��Ԃ��܂�
	unsigned int Seconds;
	unsigned int Minute;
	unsigned int timeCnt;
	bool isMaxTime();
	bool OutData();
public:
	bool isClear();
	unsigned int SecondsTime() const;
	unsigned int MinuteTime() const;
	explicit GameManager();
	void UpDate() override;
	virtual ~GameManager();
	typedef std::shared_ptr<GameManager> SP;
	static SP Create(bool = true);
};