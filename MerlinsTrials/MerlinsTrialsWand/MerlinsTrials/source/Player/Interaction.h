#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

class Interaction
{
private:
	bool e_pressed = false;
	bool reset = false;
public:
	Interaction();
	~Interaction();

	bool getReset() const;
	void setReset(const bool &in_this);
	bool getEState() const;
	void setEState(const bool &in_state);
};
#endif // !INTERACTION_H
