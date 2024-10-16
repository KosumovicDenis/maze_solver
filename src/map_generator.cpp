#include <cstdlib>
#include <random>
#include <math.h>
#include <fstream>

void genMap(int32_t w, int32_t h, std::string f_name) {
    std::ofstream out (f_name);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_w(1,w);
    std::uniform_int_distribution<std::mt19937::result_type> dist_h(1,h);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);

    int start_y = dist_h(rng);
    int start_x = dist_w(rng);

    int end_y = dist_h(rng);
    int end_x = dist_w(rng);

    for(int32_t i = 1; i <= h; i ++) {
        for (int32_t j = 1; j <= w; j++) {
            if (i == start_y && j == start_x) {
                out << 'S';
            } else  if (i == end_y && j == end_x) {
                out << 'E';
            } else {
                if (dist(rng) > 65) {
                    out << '#';
                } else {
                    out << '.';
                }
            }
        }
        out << '\n';
    }
    out.close();
}

int main(void) {
    genMap(30, 30, "map2.txt");
    return 0;
}
