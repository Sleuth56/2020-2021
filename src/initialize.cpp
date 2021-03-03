#include "main.h"

void initialize() {
	runScreen();
}

void disabled() {
	lv_tabview_set_tab_act(tabview, 1, true);
	chassis.get()->stop();
}

void competition_initialize() {}