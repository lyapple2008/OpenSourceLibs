#include <iostream>
#include "../src/sigslot.h"

using namespace std;
using namespace sigslot;

const int On = 1;
const int Off = 0;
class Switch
{
public:
	signal0<> Clicked;
};
class Light : public has_slots<>
{
public:
	Light(bool state) { b_state = state; Displaystate(); }
	void ToggleState() { b_state = !b_state; Displaystate(); }
	void TurnOn() { b_state = On; Displaystate(); }
	void TurnOff() { b_state = Off; Displaystate(); }
	void Displaystate() { cout << "The state is " << b_state << endl; }
private:
	bool b_state;
};
void main()
{
	Switch sw1, sw2, all_on, all_off;
	Light lp1(On), lp2(Off);
	sw1.Clicked.connect(&lp1, &Light::ToggleState); 
	sw2.Clicked.connect(&lp2, &Light::ToggleState);
	all_on.Clicked.connect(&lp1, &Light::TurnOn);
	all_on.Clicked.connect(&lp2, &Light::TurnOn);
	all_off.Clicked.connect(&lp1, &Light::TurnOff);
	all_off.Clicked.connect(&lp2, &Light::TurnOff);

	sw1.Clicked();
	sw2.Clicked();
	all_on.Clicked();
	all_off.Clicked();

	sw1.Clicked.disconnect(&lp1);
	sw2.Clicked.disconnect(&lp2);
	all_on.Clicked.disconnect(&lp1);
	all_on.Clicked.disconnect(&lp2);
	all_off.Clicked.disconnect(&lp1);
	all_off.Clicked.disconnect(&lp2);
}