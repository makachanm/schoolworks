#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cstdlib>

class Point {
private: 
    int x;
    int y;

public: 
    Point(int x1, int y1) :
        x(x1), y(y1)
    { }

    int getx() {
        return this->x;
    }

    int gety() {
        return this->y;
    }
};

bool isValidPath(Point p, int width, int height, char** map) {
    int x = p.getx();
    int y = p.gety();

    if(x < 0 || y < 0 || x >= width || y >= height) return false;
    else return (map[x][y] == '0' || map[x][y] == 'T');
}

int main() {
    char** maze;
    std::deque<Point> path_queue;
    int width, height;
    int step = 0;

    std::cin >> width;
    std::cin >> height;

    std::vector<std::vector<int>> distance(width, std::vector<int>(height, 1));


    maze = (char**)malloc(height * sizeof(char*));

    for(int i = 0; i < height; i++) {
        char* s = (char*)malloc(width * sizeof(char));
        std::cin >> s;

        maze[i] = s;
    }

    //find start point
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(maze[i][j] == 'S') {
                path_queue.push_back(Point(i, j));
                distance[i][j] = 1;
                break;
            }
        }
    }
    
    while(!path_queue.empty()) {
        Point current = path_queue.front();
        path_queue.pop_front();

        int croc_x = current.getx();
        int croc_y = current.gety();

        if(maze[croc_x][croc_y] == '0' || maze[croc_x][croc_y] == 'T' || maze[croc_x][croc_y] == 'S')
            step++;

        if(maze[croc_x][croc_y] == 'T') {
            std::cout << distance[croc_x][croc_y] << std::endl;
            
            for(int i = 0; i < width; i++) {
                std::cout << std::endl;
            }

            for(int i = 0; i < height; i++)
                free(maze[i]);
            free(maze);

            return 0;
        } else {
            maze[croc_x][croc_y] = '!';
            if(isValidPath(Point(croc_x, croc_y +1), width, height, maze)) { 
                path_queue.push_back(Point(croc_x, croc_y +1)); 
                distance[croc_x][croc_y + 1] = distance[croc_x][croc_y] + 1;
            }
            if(isValidPath(Point(croc_x +1, croc_y), width, height, maze)) { 
                path_queue.push_back(Point(croc_x +1, croc_y)); 
                distance[croc_x+1][croc_y] = distance[croc_x][croc_y] + 1;
            }
            if(isValidPath(Point(croc_x, croc_y -1), width, height, maze)) { 
                path_queue.push_back(Point(croc_x, croc_y -1)); 
                distance[croc_x][croc_y - 1] = distance[croc_x][croc_y] + 1;
            }
            if(isValidPath(Point(croc_x -1, croc_y), width, height, maze)) { 
                path_queue.push_back(Point(croc_x -1, croc_y)); 
                distance[croc_x-1][croc_y] = distance[croc_x][croc_y] + 1;
            }
           
        }
    }

    std::cout << "0" << std::endl;

    for(int i = 0; i < height; i++)
        free(maze[i]);
    free(maze);

    return 0;
}