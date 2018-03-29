#include "Task_GIMMICK_Control.h"
//☆☆☆☆//-----------------------------------------------------------------------------
GIMMICK_Control::GIMMICK_Control()
{
	//
}
//☆☆☆☆//-----------------------------------------------------------------------------
GIMMICK_Control::~GIMMICK_Control()
{
	//delete _e_pointa;
	delete _sen_pointa;
	delete _ka_pointa;
	delete _swi_pointa;
	delete _lad_pointa;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Initialize()
{
	//ギミックのそれぞれの初期化処理を入れる

	//_e_pointa = new EnemyHitTest();

	_sen_pointa = new Senpuki();
	_ka_pointa = new Kanetuki();
	_swi_pointa = new Switch();
	_lad_pointa = new Ladder();

	//_e_pointa->Initialize();
	_sen_pointa->Initialize();
	_ka_pointa->Initialize();
	_swi_pointa->Initlaize();
	_lad_pointa->Initialize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Finalize()
{
	//ギミックそれぞれの解放処理

	//_e_pointa->Finalize();
	_sen_pointa->Finalize();
	_ka_pointa->Finalize();
	_swi_pointa->Finalize();
	_lad_pointa->Finalize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
TaskFlag GIMMICK_Control::UpDate()
{
	//ギミックそれぞれの更新処理
	TaskFlag nextTask = Task_Sample;

	//_e_pointa->UpDate();

	_sen_pointa->UpDate();
	_ka_pointa->UpDate();
	_swi_pointa->UpDate();
	_lad_pointa->UpDate();
	return nextTask;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void GIMMICK_Control::Render2D()
{
	//ギミックそれぞれの描画処理

	//_e_pointa->Render();

	/*_sen_pointa->Render();
	_ka_pointa->Render();
	_swi_pointa->Render();*/
}

std::array<Object*, 4> GIMMICK_Control::GetGimmicks() const
{
	return {
		_sen_pointa,
		_ka_pointa,
		_swi_pointa,
		_lad_pointa
	};
}
