#include "stdafx.h"
#include "Interaction.h"

Interaction::Interaction()
{
}

Interaction::~Interaction()
{
}

bool Interaction::getReset() const
{
	return this->reset;
}

void Interaction::setReset(const bool & in_this)
{
	this->reset = in_this;
}

bool Interaction::getEState() const
{
	return this->e_pressed;
}

void Interaction::setEState(const bool & in_state)
{
	this->e_pressed = in_state;
}
