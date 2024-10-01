#include "maze.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
}

void SquareMaze::makeMaze(int width, int height){
    maze.clear();
    this->width_ = width;
    this->height_ = height;
    maze.resize(width * height, 3);
    set.addelements(width * height);
    vector<int> walls;
    for(unsigned i = 0; i < (unsigned)(height_ * width_ * 2); i++){
        walls.push_back(i);
    }
    for(unsigned i = 0; i < walls.size()-1; i++){
        unsigned j = i + rand() % (walls.size() - i);
        swap(walls[i], walls[j]);
    }

    for(unsigned i = 0; i < walls.size(); i++){
        int random = walls[i] / 2;
        int wall = walls[i] % 2;
        if(wall == 0){
            if((random + 1) % width != 0 && set.find(random) != set.find(random + 1)){
                setWall(random % width, random / width, 0, false);
                set.setunion(random, random + 1);
            }
        }
        else{
            if(random + width < width * height && set.find(random) != set.find(random + width)){
                setWall(random % width, random / width, 1, false);
                set.setunion(random, random + width);
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(x < 0 || y < 0 || x >= width_ || x >= height_ || width_ <= 0 || height_ <= 0){
        return false;
    }
    if(dir == 0){
        if(x < width_ - 1 && maze[y * width_ + x] != 1 && maze[y * width_ + x] != 3){
            return true;
        }
    }
    if(dir == 1){
        if(y < height_-1 && maze[y * width_ + x] != 2 && maze[y * width_ + x] != 3){
            return true;
        }
    }
    if(dir == 2){
        if(x > 0 && maze[y * width_ + x - 1] != 1 && maze[y * width_ + x - 1] != 3){
            return true;
        }
    }
    if(dir == 3){
        if(y > 0 && maze[(y - 1) * width_ + x] != 2 && maze[(y - 1) * width_ + x] != 3){
            return true;
        }
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        if(exists){
            if(maze[y * width_ + x] == 0){
                maze[y * width_ + x] = 1;
            }
            else if(maze[y * width_ + x] == 2){
                maze[y * width_ + x] = 3;
            }
        }
        else{
            if(maze[y * width_ + x] == 1){
                maze[y * width_ + x] = 0;
            }
            else if(maze[y * width_ + x] == 3){
                maze[y * width_ + x] = 2;
            }
        }
    }
    else{
        if(exists){
            if(maze[y * width_ + x] == 0){
                maze[y * width_ + x] = 2;
            }
            else if(maze[y * width_ + x] == 1){
                maze[y * width_ + x] = 3;
            }
        }
        else{
            if(maze[y * width_ + x] == 2){
                maze[y * width_ + x] = 0;
            }
            else if(maze[y * width_ + x] == 3){
                maze[y * width_ + x] = 1;
            }
        }
    }
}

vector<int> SquareMaze::solveMaze(){
    vector<bool> visit(width_ * height_, false);
    vector<int> dir(width_ * height_, -1);
    vector<int> path(width_ * height_, -1);
    vector<int> result;
    queue<int> cell;
    cell.push(0);
    while(!cell.empty()){
        int index = cell.front();
        visit[index] = true;
        if(canTravel(index % width_, index / width_, 0) && visit[index + 1] == false){
            cell.push(index + 1);
            dir[index + 1] = 0;
            path[index + 1] = index;
        }
        if(canTravel(index % width_, index / width_, 1) && visit[index + width_] == false){
            cell.push(index + width_);
            dir[index + width_] = 1;
            path[index + width_] = index;
        }
        if(canTravel(index % width_, index / width_, 2) && visit[index - 1] == false){
            cell.push(index - 1);
            dir[index - 1] = 2;
            path[index - 1] = index;
        }
        if(canTravel(index % width_, index / width_, 3) && visit[index - width_] == false){
            cell.push(index - width_);
            dir[index - width_] = 3;
            path[index - width_] = index;
        }
        cell.pop();
    }
    int exit = 0;
    int distance = 0;
    for(int bottum = width_ * height_ - width_; bottum < width_ * height_; bottum++){
        int count = 0;
        int tmp = bottum;
        while(tmp > 0){
            tmp = path[tmp];
            count++;
        }
        if(count > distance){
            exit = bottum;
            distance = count;
        }
    }
    while(exit > 0){
        result.push_back(dir[exit]);
        exit = path[exit];
    }
    reverse(result.begin(), result.end());
    return result;
}

cs225::PNG* SquareMaze::drawMaze(){
    cs225::PNG* init = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    for(int i = 10; i < width_ * 10 + 1; i++){
        cs225::HSLAPixel& pixel = init -> getPixel(i, 0);
        pixel.l = 0;
    }
    for(int i = 0; i < height_ * 10 + 1; i++){
        cs225::HSLAPixel& pixel = init -> getPixel(0, i);
        pixel.l = 0;
    }
    for(int x = 0; x < width_; x++){
        for (int y = 0; y < height_; y++) {
            if(maze[y * width_ + x] == 1 || maze[y * width_ + x] == 3){
                for (int k = 0; k <= 10; k++) {
                    cs225::HSLAPixel& pixel = init -> getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;
                    pixel.h = 0;
                    pixel.s = 0;
                }
            }
            if(maze[y * width_ + x] == 2 || maze[y * width_ + x] == 3){
                for (int k = 0; k <= 10; k++) {
                    cs225::HSLAPixel& pixel = init -> getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;
                    pixel.h = 0;
                    pixel.s = 0;
                }
            }
        }
    }
    return init;
}

cs225::PNG* SquareMaze::drawMazeWithSolution(){
    cs225::PNG* maze = drawMaze();
    vector<int> solution = solveMaze();
    int x = 5;
    int y = 5;
    for(unsigned int i = 0; i < solution.size(); i++){
        if(solution[i] == 0){
            for(int j = 0; j <= 10; j++){
                maze -> getPixel(x + j, y) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            x += 10;
        }
        if(solution[i] == 1){
            for(int j = 0; j <= 10; j++){
                maze -> getPixel(x, y + j) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            y += 10;
        }
        if(solution[i] == 2){
            for(int j = 0; j <= 10; j++){
                maze -> getPixel(x - j, y) = cs225::HSLAPixel(0, 1, 0.5, 1);

            }
            x -= 10;
        }
        if(solution[i] == 3){
            for(int j = 0; j <= 10; j++){
                maze -> getPixel(x, y - j) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            y -= 10;
        }
    }
    x -= 4;
    y += 5;
    for(int i = 0; i < 9; i++){
        cs225::HSLAPixel& pixel = maze -> getPixel(x + i, y);
        pixel.l = 1;
        pixel.h = 0;
        pixel.s = 0;
    }
	return maze;
}