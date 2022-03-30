//
// Created by Gal on 30/03/2022.
//

#include <iostream>
#include "Notebook.hpp"

using namespace ariel;
const int MaxRow = 100;
const int MaxChar = 126;
const int MinChar = 32;

void
Notebook::check_input(int page, int row, int column, Direction direction, int length, bool write_flag, bool show_flag,
                      bool erase_flag, bool read_flag, string const &str) {
    if (read_flag) {
        if (page < 0 || row < 0 || column < 0 || length < 0 || (column >= MaxRow) ||
            (column + length > MaxRow && direction == Direction::Horizontal)) {
            throw invalid_argument("Invalid argument");
        }
    }
    if (erase_flag) {
        if (page < 0 || row < 0 || column < 0 || length < 0 || (column >= MaxRow) ||
            (column + length > MaxRow && direction == Direction::Horizontal)) {
            throw invalid_argument("Invalid argument");
        }
    }
    if (show_flag) {
        if (page < 0) {
            throw invalid_argument("Page cannot be negative");
        }
    }
    if (write_flag) {
        if (page < 0 || row < 0 || column < 0 || length < 0 || (column >= MaxRow) ||
            (column + length > MaxRow && direction == Direction::Horizontal)) {
            throw invalid_argument("Invalid argument");
        }
        for (char i: str) {
            if (i < MinChar || i > MaxChar) {
                throw invalid_argument("Invalid argument");;
            }
        }
        if (str.find('~') != string::npos) {
            throw invalid_argument("Invalid argument");
        }
    }

}

void ariel::Notebook::show(int page) {
    check_input(page, 0, 0, Direction::Horizontal, 0, false, true, false, false, "");
    string pagestrings = to_string(page);
    bool flag = true;
    for (pair<string, array<char, MaxRow>> e: map) {
        flag = true;
        for (unsigned int i = 0; i < pagestrings.size(); ++i) {
            if (e.first.at(i) != pagestrings.at(i)) {
                flag = false;
            }
        }
        if (flag) {
            cout << e.first.substr(pagestrings.size() + 1) << ":";
            for (unsigned long i = 0; i < MaxRow; ++i) {
                cout << e.second.at(i);
            }
        }
    }
}

void ariel::Notebook::erase(int page, int row, int column, ariel::Direction direction, int length) {
    check_input(page, row, column, direction, length, false, false, true, false, "");
    string pass;
    int i = 0;
    if (direction == Direction::Vertical) {
        while (i < length) {
            pass = to_string(page) + "," + to_string(row++);
            if (map.find(pass) == map.end()) {
                array<char, MaxRow> arr{};
                arr.fill('_');
                map[pass] = arr;
            }
            map[pass][static_cast<unsigned long>(column)] = '~';
            i++;
        }
    } else if (direction == Direction::Horizontal) {
        pass = to_string(page) + "," + to_string(row);
        if (map.find(pass) == map.end()) {
            array<char, MaxRow> arr{};
            arr.fill('_');
            map[pass] = arr;
        }
        while (i < length) {
            map[pass][static_cast<unsigned long>(column++)] = '~';
            i++;
        }
    }
}

string ariel::Notebook::read(int page, int row, int column, ariel::Direction direction, int length) {
    check_input(page, row, column, direction, length, false, false, false, true, "");
    string pass;
    string temp;
    int i = 0;
    if (direction == Direction::Vertical) {
        while (i < length) {
            pass = to_string(page) + "," + to_string(row++);
            if (map.find(pass) == map.end()) {
                temp += "_";
            } else {
                temp += map[pass][static_cast<unsigned long>(column)];
            }
            i++;
        }
    } else if (direction == Direction::Horizontal) {
        pass = to_string(page) + "," + to_string(row);
        if (map.find(pass) == map.end()) {
            temp = string(static_cast<unsigned long>(length), '_');
        } else {
            while (i < length) {
                temp += map[pass][static_cast<unsigned long>(column++)];
                i++;
            }
        }
    }
    return temp;
}


void ariel::Notebook::write(int page, int row, int column, ariel::Direction direction, string const &str) {
    check_input(page, row, column, direction, 0, true, false, false, false, str);
    string pass;
    string line = this->read(page, row, column, direction, static_cast<int>(str.length()));
    for (char c: line) {
        if (c != '_') {
            throw invalid_argument("no space");
        }
    }
    if (direction == Direction::Vertical) {
        for (char i: str) {
            pass = to_string(page) + "," + to_string(row++);
            if (map.find(pass) == map.end()) {
                array<char, MaxRow> arr{};
                arr.fill('_');
                map[pass] = arr;
            }
            map[pass][static_cast<unsigned long>(column)] = i;
        }
    }
    if (direction == Direction::Horizontal) {
        pass = to_string(page) + "," + to_string(row);
        if (map.find(pass) == map.end()) {
            array<char, MaxRow> arr{};
            arr.fill('_');
            map[pass] = arr;
        }
        for (char i: str) {
            map[pass][static_cast<unsigned long>(column++)] = i;
        }
    }
}
