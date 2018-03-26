#include "Task_GIMMICK_Control.h"
//☆☆☆☆//-----------------------------------------------------------------------------
GIMMICK_Control::GIMMICK_Control()
{

}
//☆☆☆☆//-----------------------------------------------------------------------------
GIMMICK_Control::~GIMMICK_Control()
{
	//delete _p_pointa;
	delete _e_pointa;
	delete _sen_pointa;
	delete _ka_pointa;
	delete _swi_pointa;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Initialize()
{
	//ギミックのそれぞれの初期化処理を入れる
	//p_pointa = new Player();
	//_e_pointa = new EnemyHitTest();

	_sen_pointa = new Senpuki(_e_pointa);
	_ka_pointa = new Kanetuki(_e_pointa);
	_swi_pointa = new Switch(_e_pointa);

	//_p_pointa->Initialize();
	//_e_pointa->Initialize();
	_sen_pointa->Initialize();
	_ka_pointa->Initialize();
	_swi_pointa->Initlaize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Finalize()
{
	//ギミックそれぞれの解放処理
	//_p_pointa->Finalize();
	//_e_pointa->Finalize();
	_sen_pointa->Finalize();
	_ka_pointa->Finalize();
	_swi_pointa->Finalize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
TaskFlag GIMMICK_Control::UpDate()
{
	//ギミックそれぞれの更新処理
	TaskFlag nextTask = Task_Sample;
	//_p_pointa->UpDate();
	//_e_pointa->UpDate();
	_sen_pointa->UpDate();
	_ka_pointa->UpDate();
	_swi_pointa->UpDate();
	return nextTask;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Render2D()
{
	//ギミックそれぞれの描画処理
	//_e_pointa->Render();
	//_p_pointa->Render();
	_sen_pointa->Render();
	_ka_pointa->Render();
	_swi_pointa->Render();
}
