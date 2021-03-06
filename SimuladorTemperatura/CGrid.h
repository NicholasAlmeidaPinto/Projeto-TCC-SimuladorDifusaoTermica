#ifndef CGRID_HPP
#define CGRID_HPP

#include <vector>
#include <string>
#include "CCell.h"
#include <iostream>
#include "CMaterialCorrelacao.h"

class CGrid {
private:
    int width, height;
    std::vector<CCell> grid;
public:
    CGrid() {
        width = 0;
        height = 0;
    }

    CGrid(int _width, int _height) : width{_width}, height{_height}{
        grid.resize(width * height);
    }

    CGrid(int _width, int _height, double temperature) {
        resetSize(_width, _height, temperature);
    }

    void resetGrid(double temperature);

    void resetSize(int _width, int _height, double temperature);

    void draw_rec(int x, int y, double size, double temperature, bool isSourceActive, CMaterial* _material, bool eraser);
    void draw_cir(int x, int y, double size, double temperature, bool isSourceActive, CMaterial* _material, bool eraser);
    void draw(int x, double temperature, bool active, bool isSource, std::string _material);

    int getSize() { return width * height; }

    void updateIteration();
    void updateSolver();
    void startIteration();
    double maxErroIteration();

    int getWidth() { return width;}
    int getHeight() { return height; }
    double getTemp(int position) { return grid[position].temp_nup1; }

    double maxTemp();
    double minTemp();

    bool isActive(int x){ return grid[x].active;}
    CCell* operator () (int x, int y) { return &grid[y * width + x]; }
    CCell* operator [] (int x) { return &grid[x]; }

};
#endif
