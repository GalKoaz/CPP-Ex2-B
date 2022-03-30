//
// Created by Gal on 24/03/2022.
//

#include "Direction.hpp"
#include <string>
#include <map>
#include <unordered_map>

using namespace std;
namespace ariel {
    class Notebook {

    private:
        unordered_map<string, array<char, 100>> map;

    public:

        static void check_input(int page, int row, int column, Direction direction, int length,bool write_flag, bool show_flag,
                                bool erase_flag, bool read_flag, string const &str);

        void write(int page, int row, int column, Direction direction, string const &str);

        string read(int page, int row, int column, Direction direction, int length);

        void erase(int page, int row, int column, Direction direction, int length);

        void show(int page);
    };
}
