#pragma once
#include "Staff.h"
#include "BaseMenu.h"

struct StaffMenu : BaseMenu {
    static void show(List<Staff>& sources);
};
