#include "Task_Sample.h"

void Sample::Initialize()
{
	std::cout << "Sample‰Šú‰»" << std::endl;
	s.createSound(file);
	a.createSound(file2);
	gameEngine->soundManager->SetSound(&s);
	gameEngine->soundManager->SetSound(&a);
	gameEngine->soundManager->SetMaxVolume(0.5f);
	a.play();
	s.play();
	gameEngine->soundManager->SetVolume(&a, 0.5f);
}

TaskFlag Sample::UpDate()
{
	std::cout <<
		s.currenttime() << 
		":" << a.currenttime() << ":" << std::endl;
	TaskFlag nowtask = Task_Sample;
	if (gameEngine->in.key.down(In::SPACE))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Sample::Render2D()
{
	
}

void Sample::Finalize()
{
	std::cout << "Sample‰ð•ú" << std::endl;
	s.stop();
	a.stop();
	gameEngine->soundManager->AllDelete();
}
