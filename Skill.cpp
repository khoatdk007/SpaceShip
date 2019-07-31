#include "Skill.h"

Skill::Skill(double recoveryTime, double kiToUse) {
	this->recoveryTime = recoveryTime;
	this->timer = this->recoveryTime;
	this->kiToUse = kiToUse;
}

double Skill::getTimer() {
	return this->timer;
}

bool Skill::isAvailable() {
	return this->timer >= this->recoveryTime;
}
void Skill::update(double timeUpdate) {
	this->timer += timeUpdate;
	if (this->timer > this->recoveryTime) this->timer = this->recoveryTime;
}

void Skill::use() {
	this->timer = 0;

}

double Skill::getKiToUse() {
	return this->kiToUse;
}

double Skill::getRecoveryTime() {
	return this->recoveryTime;
}