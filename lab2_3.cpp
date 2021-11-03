#include <string>
#include <iostream>
#include <Windows.h>

#undef max

#include "menu.h"

void Read() {
    try {
        std::string map_name;

        std::cout << "Enter map name:\n";
        std::getline(std::cin, map_name);

        HANDLE map_handle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, map_name.data());
        if (map_handle == nullptr) {
            throw GetLastError();
        }

        void* map_address = MapViewOfFile(map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (map_address == nullptr) {
            throw GetLastError();
        }

        std::string data(static_cast<char*>(map_address));
        std::cout << "Read data:\n" << data << '\n';

    } catch (DWORD& error) {
        std::cout << "Error " << error << " ocurred\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu_process(Menu("READER", "Exit", std::vector<Item>({ Item("Read", Read) })));
}
