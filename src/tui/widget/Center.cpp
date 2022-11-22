//
// Created by mslxl on 11/7/2022.
//

#include "Center.h"

namespace tui {
    Center::Center(std::shared_ptr<Widget> child) : Container(
            std::make_shared<VCenter>(std::make_shared<HCenter>(child))) {

    }
} // tui