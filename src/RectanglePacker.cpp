/*
    Rectangle Packer

    Copyright (C) 2022, Novichkov Gleb, PhD

    Rectangle Packer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    Rectangle Packer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rectangle Packer.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Node.h>

//  std, c headers
#include <algorithm>
#include <cstdio>           //  puts
#include <cstdlib>          //  exit(), EXIT_FAILURE
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>


using rects_t = std::vector<Rect>;

static std::tuple <rects_t, rects_t> pack_rectangles (double w, double h, std::vector<Rect> && input_rectangles)
{
    std::sort(
        std::begin(input_rectangles),
        std::end(input_rectangles),
        [](const Rect &l, const Rect& r) { return l.area() >= r.area(); }
    );

    std::vector<Rect> packed_rects;
    std::vector<Rect> faulures;

    Node *root = new Node(0,0,w,h);

    for (auto const & r: input_rectangles) {
        if (root->insert(r) == false) {
            faulures.push_back(r);
        }
    }

    root->visit_nodes_collect_rectangles(packed_rects);
    delete root;

    return {packed_rects, faulures};
}

static std::vector <Rect> load_rects(std::string filename)
{
    auto parse_csv_line = [](std::string line) -> std::tuple <double, double> {
        std::vector <std::string> tokens;
        std::string tk;
        std::stringstream   strs(line);

        while (std::getline (strs, tk, ',')) {
            tokens.push_back (tk);
        }
        if (tokens.size()!=2) {
            throw std::runtime_error("Failed to parse line '" + line + "'");
        }
        return {std::stod(tokens[0]),std::stod(tokens[1])};
    };

    std::vector <Rect> rects;
    std::ifstream  fs{filename};

    if (!fs.good()) {
        std::cerr << "***ERROR***: Failed to open input file " << filename << ". Aborting.\n";
        std::exit(EXIT_FAILURE);
    }
    for (std::string line; std::getline(fs, line); ) {
        auto [w,h] = parse_csv_line(line);
        rects.emplace_back(w,h);
    }

    return rects;
}

static void save_rects(std::string filename, const std::vector <Rect> & rects, bool is_packed = true) {
    std::ofstream  os{filename};

    if (!os.good()) {
        std::cerr << "***ERROR***: Failed to open output file " << filename << ". Aborting.\n";
        std::exit(EXIT_FAILURE);
    }

    for (auto const & r : rects) {
        if (is_packed) {
            os << r.x << "," << r.y << "," << r.w << "," << r.h << "\n";
        }
        else {
            os << r.w << "," << r.h << "\n";
        }
    }
    os.flush();
}

static std::tuple<std::string,
                  std::string,
                  std::string,
                  double,
                  double>
parse_command_line_args(int argc, char* argv[]) {
    std::string input_file;
    std::string output_file;
    std::string failures_file;
    double w = 0, h = 0;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--input" || std::string(argv[i]) == "-i") {
            if (i + 1 < argc) {
                input_file = argv[++i];
            } else {
                throw std::runtime_error ("--input [-i] option requires a parameter.\n");
            }
        }
        else if (std::string(argv[i]) == "--output" || std::string(argv[i]) == "-o") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                throw std::runtime_error ("--output [-o] option requires a parameter.\n");
            }
        }
        else if (std::string(argv[i]) == "--failures" || std::string(argv[i]) == "-f") {
            if (i + 1 < argc) {
                failures_file = argv[++i];
            } else {
                throw std::runtime_error ("--failures [-f] option requires a parameter.\n");
            }
        }
        else if (std::string(argv[i]) == "--width" || std::string(argv[i]) == "-w") {
            if (i + 1 < argc) {
                w = std::stod(argv[++i]);
            } else {
                throw std::runtime_error ("--width [-w] option requires a parameter.\n");
            }
        }
        else if (std::string(argv[i]) == "--height" || std::string(argv[i]) == "-h") {
            if (i + 1 < argc) {
                h = std::stod(argv[++i]);
            } else {
                throw std::runtime_error ("--height [-h] option requires a parameter.\n");
            }
        }
    }
    return {input_file, output_file, failures_file, w, h};
}

static void print_usage(char * name) {
    std::cout << "Usage: " << name << " --input [-i] <input_file.csv> --output [-o] <output_file.csv> --failures [-f] <failures.csv> --width [-w] <width> --height [-h] <height>" << std::endl;
}

int main (int argc, char* argv[]) try {

    if (argc !=11) {
        print_usage(argv[0]);
        std::exit(EXIT_SUCCESS);
    }

    auto [input_file, output_file, failures_file, w, h] = parse_command_line_args(argc, argv);
    auto input = load_rects (input_file);
    auto [p, f] = pack_rectangles(w, h, std::move(input));

    std::cout <<"--- Packed rectangles\n";
    for (auto const & r: p) {
        r.print();
    }

    std::cout <<"--- Failures\n";
    for (auto const & r: f) {
        r.print();
    }
    std::cout <<"------------\n";

    save_rects(output_file, p);
    save_rects(failures_file, f, false);
}
catch (std::runtime_error & e) {
    std::cout << "*** Error occured, aborting. *** Details: " << e.what() << std::endl;
}
catch (std::invalid_argument& e) {
    std::cout << "*** Error occured, aborting. *** Details: " << e.what() << std::endl;
}
