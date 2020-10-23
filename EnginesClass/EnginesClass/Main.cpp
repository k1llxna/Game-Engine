#include "Engine/Core/CoreEngine.h"
#include "Game\Game1.h"

int main(int argc, char* argv[]) {

	CoreEngine::GetInstance()->SetGameInterface(new Game1); // game interface instance

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 1200, 780)) { // game engine instance
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();

	return 0;
}