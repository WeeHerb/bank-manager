//
// Created by mslxl on 10/18/2022.
//

#pragma once

#include<stack>
#include<vector>
#include<ostream>

#include "scene.h"
#include "biarray.h"

class Frame {
private:
    std::stack<Scene> scenes;
    BiArray<char> canvas;

    void draw_border_line();

public:
    unsigned short width;
    unsigned short height;
    bool draw_border;

    Frame(unsigned short w, unsigned h) : width(w), height(h), canvas(w, h) {
        draw_border = true;
    }

    void paint(std::ostream &os);

    void update();

    void push_scene(Scene scene);

    void pop_scene(Scene scene);


};


