#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

class Interaction
{
private:
	bool e_pressed = false;

public:
	Interaction();
	~Interaction();

	bool getEState() const;
	void setEState(const bool &in_state);
};
#endif // !INTERACTION_H
