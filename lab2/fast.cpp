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
    const size_t summary_size = 16; // Öka storleken för bättre noggrannhet.

    // initierng
    Image_Summary result;
    result.horizontal.resize(summary_size);
    result.vertical.resize(summary_size);

    for (size_t y = 0; y < summary_size; ++y)
    {
        for (size_t x = 1; x < summary_size; ++x)
        {
            float current_brightness = image.pixel(x, y).brightness();
            float previous_brightness = image.pixel(x - 1, y).brightness();
            result.horizontal[y] = (current_brightness > previous_brightness);
        }
        // Denna jämförelse returnerar true om ljusstyrkan hos den nuvarande pixeln är större än ljusstyrkan hos den föregående, och false annars.
        // Det booleska resultatet lagras i result.horizontal[y], vilket representerar om ljusstyrkan ökar från vänster till höger på rad
    }

    for (size_t x = 0; x < summary_size; ++x)
    {
        for (size_t y = 1; y < summary_size; ++y)
        {
            float current_brightness = image.pixel(x, y).brightness();
            float previous_brightness = image.pixel(x, y - 1).brightness();
            result.vertical[x] = (current_brightness > previous_brightness);
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

    auto begin = std::chrono::high_resolution_clock::now();
    // En unordered_map används för att gruppera bilderna baserat på deras sammanfattningar.Varje unikt Image_Summary fungerar som en nyckel, och en lista över bildfiler som har samma sammanfattning lagras som värde. för att snabbt identifiera potentiella dubbletter utan att behöva göra parvisa jämförelser av alla bilder.
    unordered_map<Image_Summary, vector<string>> summary_map;

    for (const auto &file : files)
    {
        Image img = load_image(file).shrink(32, 32); // Shrink images.
        Image_Summary summary = compute_summary(img);

        summary_map[summary].push_back(file);
    }

    auto end = std::chrono::high_resolution_clock::now();
    cout << "Summary computation took: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // Gör en noggrannare jämförelse för de bilder som har samma sammanfattning
    for (const auto &entry : summary_map)
    {
        if (entry.second.size() > 1)
        {
            for (size_t i = 0; i < entry.second.size(); ++i)
            {
                for (size_t j = i + 1; j < entry.second.size(); ++j)
                {
                    // Gör en finare jämförelse med den gamla metoden från slow.cpp
                    Image img1 = load_image(entry.second[i]).shrink(32, 32);
                    Image img2 = load_image(entry.second[j]).shrink(32, 32);
                    double difference = img1.compare_to(img2);

                    // Använd samma tröskelvärde som i slow.cpp
                    if (difference <= 0.01)
                    {
                        vector<string> matches = {entry.second[i], entry.second[j]};
                        window->report_match(matches);
                    }
                }
            }
        }
    }

    return 0;
}
