#include "include/graph/graph.h"
#include <fstream>

graph g;

int main(void) {
    std::ifstream map;
    map.open("map2.txt");
    std::cout << "Reading from file" << std::endl;
    std::string row;
    Tile starting_t;
    Tile end_t;
    if (map.is_open()) {
        int32_t i = 0;
        while(std::getline(map, row)) {
            for(int j = 0; j < row.length(); j++) {
                if (static_cast<int32_t>(row[j]) != 35) {
                    g.AddVertex({i,j});
                }
                if (static_cast<int32_t>(row[j]) == 83) {
                    starting_t = {i, j};
                } else if (static_cast<int32_t>(row[j]) == 69) {
                    end_t = {i, j};
                }
            }
            i++;
        }
        map.close();
    }

    std::vector<Tile> path;

    g.FindPathAStar(starting_t, end_t, path);

    g.PrintMaze(path);

    for (int32_t i = 0; i < path.size() - 1; i ++) {
        if (path.at(i).x < path.at(i + 1).x) {
            std::cout << "'RIGHT'\t";
        } else if (path.at(i).x > path.at(i + 1).x) {
            std::cout << "'LEFT'\t";
        } else if (path.at(i).y < path.at(i + 1).y) {
            std::cout << "'DOWN'\t";
        } else {
            std::cout << "'UP'\t";
        }
   }

    return 0;
}
