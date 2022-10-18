//
// Created by mslxl on 10/18/2022.
//

#pragma once
#include<memory>
#include<cassert>


template<class T>
class BiArray {
private:
    class BiArrayAccessDelegate{
    private:
        std::size_t y;
        std::size_t offset_x;
        BiArray<T> *arr;
    public:
        T& operator[](std::size_t x) const {
            assert(x + offset_x < arr-> width);
            return arr->data[y * arr->width + x + offset_x];
        }

        BiArrayAccessDelegate(std::size_t y, BiArray<T> *arr, std::size_t offset_x=0): y(y), arr(arr), offset_x(offset_x){
            assert(offset_x < arr->width);
        }
    };

    class BiArrayRel{
    private:
        std::size_t rel_x;
        std::size_t rel_y;
        BiArray<T> *arr;

    public:
        BiArrayAccessDelegate operator[](std::size_t y){
            assert(rel_y + y < arr->height);
            return BiArrayAccessDelegate(rel_y + y, arr, rel_x);
        }
        BiArrayRel(std::size_t x, std::size_t y, BiArray<T> *arr): rel_x(x), rel_y(y), arr(arr){}
    };
public:
    std::size_t width;
    std::size_t height;
    T* data;
    BiArray(std::size_t w, std::size_t h): width(w), height(h){
      data = new T[width * height];
    }

    ~BiArray(){
        delete[] data;
    }

    BiArrayRel rel(std::size_t x, std::size_t y){
        return BiArrayRel(x,y, this);
    }

    BiArrayAccessDelegate operator[](std::size_t y){
        assert(y < height);
        return BiArrayAccessDelegate(y, this);
    }
};
