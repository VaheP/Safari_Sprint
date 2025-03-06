#include "Event.h"		
#include "ViewObject.h"

#define POINTS_STRING "Points"

class Points : public df::ViewObject {
private:
	int score;

public:
	Points();
	int eventHandler(const df::Event* p_e) override;
	int getScore() const;
	void addScore(int amount);
};
#pragma once
