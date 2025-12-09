#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class OutOfBoundsException : public std::runtime_error {
public:
    OutOfBoundsException() : std::runtime_error("Out of bounds") {}
};

struct Location {
    int x, y;
    char value;
};

class Map {
public:
    std::vector<std::string> board;
    int x_size, y_size;

    Map(std::ifstream& file) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                board.push_back(line);
            }
        }
        if (!board.empty()) {
            x_size = board[0].size();
            y_size = board.size();
        } else {
            x_size = 0;
            y_size = 0;
        }
    }

    char get_cell(int x, int y) {
        if (x < 0 || x >= x_size || y < 0 || y >= y_size) {
            throw OutOfBoundsException();
        }
        return board[y][x];
    }

    char set_cell(int x, int y, char value) {
        if (x < 0 || x >= x_size || y < 0 || y >= y_size) {
            throw OutOfBoundsException();
        }
        board[y][x] = value;
        return value;
    }

    std::vector<Location> iter_all_cells() {
        std::vector<Location> locations;
        for (int y = 0; y < y_size; ++y) {
            for (int x = 0; x < x_size; ++x) {
                locations.push_back({x, y, get_cell(x, y)});
            }
        }
        return locations;
    }
};

int main() {
    std::ifstream file("input");
    if (!file) {
        std::cerr << "Cannot open input file\n";
        return 1;
    }
    Map map(file);

    // Part 1
    
    int accessable_count = 0;

    auto locations = map.iter_all_cells();
    for (const auto& loc : locations) {
        //std::cout << "Location: (" << loc.x << ", " << loc.y << ") = " << loc.value << std::endl;
        if (loc.value != '@') {
            continue;
        }

        // count each cell's eight neighbors with value '@'
        int neighbor_count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue; // skip self
                try {
                    if (map.get_cell(loc.x + dx, loc.y + dy) == '@')
                        neighbor_count++;
                } catch (const OutOfBoundsException&) {
                    // Ignore out of bounds
                }
            }
        }
        if (neighbor_count < 4) {
            accessable_count++;
        }
    }

    std::cout << "Accessable '@' count: " << accessable_count << std::endl;

    // Part 2
    accessable_count = 0;

    int changed_values = 1;
    while (changed_values > 0) {
        changed_values = 0;
        auto locations = map.iter_all_cells();
        for (const auto& loc : locations) {
            if (loc.value != '@') {
                continue;
            }

            // count each cell's eight neighbors with value '@'
            int neighbor_count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue; // skip self
                    try {
                        if (map.get_cell(loc.x + dx, loc.y + dy) == '@')
                            neighbor_count++;
                    } catch (const OutOfBoundsException&) {
                        // Ignore out of bounds
                    }
                }
            }
            if (neighbor_count < 4) {
                map.set_cell(loc.x, loc.y, 'x');
                accessable_count++;
                changed_values++;
            }
        }
    }

    std::cout << "Accessable '@' count with repeated operation: " << accessable_count << std::endl;
    return 0;
}
