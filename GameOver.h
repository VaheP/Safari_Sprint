#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Object.h"
#include "ViewObject.h"

class GameOver : public df::ViewObject {

private:
	int time_to_live;
	void step();

public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e) override;
	int draw() override;
};
#endif