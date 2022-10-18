//
// Created by mslxl on 10/18/2022.
//

#include<cstring>
#include "frame.h"

void Frame::push_scene(Scene scene) {
    scenes.push(scene);
}

void Frame::pop_scene(Scene scene) {
    scenes.pop();
}

void Frame::paint(std::ostream &os) {
    update();
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            os << canvas[y][x];
        }
        os << "\n";
    }
    os.flush();
}

void Frame::update() {
    std::memset(canvas.data, ' ', sizeof(char) * width * height);

    if (draw_border){
        draw_border_line();
    }
}

void Frame::draw_border_line() {
    auto fst_row = canvas[0];
    auto lst_row = canvas[height-1];
    for(int i = 0; i < width; i++){
        fst_row[i] = '-';
        lst_row[i] = '-';
    }
    for(int i = 0; i < height; i++){
        canvas[i][0] = '|';
        canvas[i][width-1] = '|';
    }
}
