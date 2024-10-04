#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

class Image_Summary
{
public:
    vector<bool> horizontal;
    vector<bool> vertical;

    bool operator==(const Image_Summary &other) const
    {
        return horizontal == other.horizontal && vertical == other.vertical;
    }
};

namespace std
{
    template <>
    struct hash<Image_Summary>
    {
        size_t operator()(const Image_Summary &summary) const
        {
            // består av två vektorer(horizontal och vertical) som lagrar information om hur ljusstyrkan i bilden förändras horisontellt och vertikalt.
            size_t h_hash = std::hash<vector<bool>>{}(summary.horizontal);
            size_t v_hash = std::hash<vector<bool>>{}(summary.vertical);
            return h_hash ^ (v_hash << 1);
        }
    };
}
Image_Summary compute_summary(const Image &image)
{
    const size_t summary_size = 8; // minska storlek för mer nogranhet

    Image shrunk_image = image.shrink(summary_size + 1, summary_size + 1);

    Image_Summary result;
    result.horizontal.resize(summary_size * (summary_size + 1));
    result.vertical.resize(summary_size * (summary_size + 1));

    for (size_t y = 0; y < summary_size + 1; ++y)
    {
        for (size_t x = 1; x < summary_size + 1; ++x)
        {
            float current_brightness = shrunk_image.pixel(x, y).brightness();
            float previous_brightness = shrunk_image.pixel(x - 1, y).brightness();

            result.horizontal[y * summary_size + (x - 1)] = (current_brightness > previous_brightness);
        }
    }

    for (size_t x = 0; x < summary_size + 1; ++x)
    {
        for (size_t y = 1; y < summary_size + 1; ++y)
        {
            float current_brightness = shrunk_image.pixel(x, y).brightness();
            float previous_brightness = shrunk_image.pixel(x, y - 1).brightness();

            result.vertical[x * summary_size + (y - 1)] = (current_brightness > previous_brightness);
        }
    }

    return result;
}

int main(int argc, const char *argv[])
{
    WindowPtr window = Window::create(argc, argv);

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1], ".jpg");
    cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0)
    {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    }

    // En unordered_map används för att gruppera bilderna baserat på deras sammanfattningar.Varje unikt Image_Summary fungerar som en nyckel, och en lista över bildfiler som har samma sammanfattning lagras som värde. för att snabbt identifiera potentiella dubbletter utan att behöva göra parvisa jämförelser av alla bilder.
    auto begin = std::chrono::high_resolution_clock::now();

    unordered_map<Image_Summary, vector<string>> summary_map;

    for (const auto &file : files)
    {
        Image img = load_image(file);
        Image_Summary summary = compute_summary(img);

        summary_map[summary].push_back(file);
    }

    auto end = std::chrono::high_resolution_clock::now();
    cout << "Summary computation took: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // Vi har nu en lista med alla bilder grupperade efter sina sammanfattningar.
    for (const auto &entry : summary_map)
    {
        if (entry.second.size() > 1)
        {
            // Rapportera alla bilder som dubbletter, eftersom de har samma sammanfattning.
            window->report_match(entry.second);
        }
    }

    return 0;
}
