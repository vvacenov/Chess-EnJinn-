#pragma once
#include "RenderController.h"

class GameController
{
	RenderController r;
	
public:
	GameController() { r.renderLoop(); }
};

