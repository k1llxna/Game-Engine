#include "../../../Engine/Core/CoreEngine.h"
#include "../../../Game/Game1.h"
#include "../../../Resources/rapidxml.hpp"

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1); // game interface instance

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 1200, 780)) { // game engine instance
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}

	std::ifstream file("./Engine/Info.xml"); // engine folder
	rapidxml::xml_document<> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* root = doc.first_node();
	int id = atoi(root->first_node("person")->first_attribute("id")->value());
	std::string gameTitle = root->first_node("person")->first_node("name")->first_node("gameTitle")->value();
	std::string members = root->first_node("person")->first_node("name")->first_node("members")->value();
	std::string engine = root->first_node("person")->first_node("name")->first_node("engine")->value();

	std::cout << gameTitle << std::endl;
	std::cout << members << std::endl;
	std::cout << engine << std::endl;

	CoreEngine::GetInstance()->Run();

	return 0;
}