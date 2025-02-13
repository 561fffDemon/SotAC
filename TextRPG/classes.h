#pragma once

#include <iostream>
#include <sstream>

class Entity {
	float MaxHP, HP, Damage, Defence;
	string Name;

public:
	Entity(float MaxHP, float HP, float Damage, float Defence, string Name) : MaxHP{ MaxHP }, HP{ HP }, Damage{ Damage }, Defence{ Defence }, Name{Name} {

	}

	void TakeDMG_HP(float dmg) { 
		HP -= dmg * (1 - Defence / 100); 

		if (HP < 0)
			HP = 0;
	}
	void TakeDMG_DEF(float dmg) {
		Defence -= dmg * (1 - Defence / 100);

		if (Defence < 0)
			Defence = 0;
	}

	void SetHP(float HP) {
		HP = HP;

		if (HP > MaxHP) 
			HP = MaxHP;
	}

	void SetHP_MAX(float HP) { MaxHP = HP; }
	void SetDEF(float Defence) { Defence  = Defence; }

	float GetHP() { return HP; }
	float GetMaxHP() { return MaxHP; }
	float GetDEF() { return Defence; }
	float GetDMG() { return Damage; }
	string GetNAME() { return Name; }
};