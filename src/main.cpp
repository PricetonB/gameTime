
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Game.h"

int main()
{
	Game* game = new Game();

	game->run();

	delete game;
	return 0;
}




/*

   game needs to have access to all scene files.
   
 the while loop in game.run should call runn on current scene

 we inject game in to the scene as an argument. this uses depenedency inversion.
 this way the game doesnt rely on a scene to survive. the scene can be destroyed and the 
 game object will still exist. 

 should have a parent scene that all scenes follow.
 virtual functions will be run(), and changeScene()

 


 GAME CLASS
 

 currentscene = homescreen
 scene_running = homescreen

while true:

	if current_scene == scene_running.name:
		scene_running.run()
	else:
		destroy scene_running
		scene_running = new current_scene();
	
		
		
	


 */

