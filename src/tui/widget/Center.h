//
// Created by mslxl on 11/7/2022.
//

#pragma once
#include "VCenter.h"
#include "HCenter.h"
#include "Container.h"
namespace tui {

    class Center: public Container {
    public:
        ~Center() override = default;
        explicit Center(std::shared_ptr<Widget>);
    };

} // tui
