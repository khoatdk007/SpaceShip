#ifndef _SKILL_H
#define _SKILL_H

#include <iostream>

class Skill {
private:
	double recoveryTime;
	double timer;
	double kiToUse;
public:
	Skill(double recoveryTime, double kiToUse);
	double getTimer();
	bool isAvailable();
	void update(double timeUpdate);
	void use();
	double getKiToUse();
	double getRecoveryTime();
};

#endif