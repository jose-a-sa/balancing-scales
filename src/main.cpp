#include <iostream>
#include <span>
#include <format>

#include "tree_of_scales.h"
#include "csv.h"


int main(int argc, char** argv)
{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    try
    {
        TreeOfScales tree{};

        auto const parse_row = [&](std::span<std::string_view, 3> parts)
        { 
            tree.add_scale_entry(parts[0], parts[1], parts[2]); 
        };

        read_csv_lines<3>(std::cin, parse_row);

        tree.balance_scales();

        for(auto& s: tree.scale_entries())
        {
            auto const [added_left, added_right] = s.added_weights();
            std::cout << std::format("{},{},{}\n", s.id(), added_left, added_right);
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }


    return 0;
}
