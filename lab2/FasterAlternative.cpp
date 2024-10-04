// #include "image.h"
// #include "window.h"
// #include "load.h"
// #include <chrono>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <unordered_map>

// using std::cerr;
// using std::cout;
// using std::endl;
// using std::string;
// using std::unordered_map;
// using std::vector;

// class Image_Summary
// {
// public:
//   vector<bool> horizontal;
//   vector<bool> vertical;

//   bool operator==(const Image_Summary &other) const
//   {
//     return horizontal == other.horizontal && vertical == other.vertical;
//   }
// };

// namespace std
// {
//   template <>
//   struct hash<Image_Summary>
//   {
//     size_t operator()(const Image_Summary &summary) const
//     {
//       size_t h_hash = std::hash<vector<bool>>{}(summary.horizontal);
//       size_t v_hash = std::hash<vector<bool>>{}(summary.vertical);
//       return h_hash ^ (v_hash << 1);
//     }
//   };
// }

// Image_Summary compute_summary(const Image &image)
// {
//   const size_t summary_size = 16;

//   Image_Summary result;
//   result.horizontal.resize(summary_size);
//   result.vertical.resize(summary_size);

//   for (size_t y = 0; y < summary_size; ++y)
//   {
//     for (size_t x = 1; x < summary_size; ++x)
//     {
//       float current_brightness = image.pixel(x, y).brightness();
//       float previous_brightness = image.pixel(x - 1, y).brightness();
//       result.horizontal[y] = (current_brightness > previous_brightness);
//     }
//   }

//   for (size_t x = 0; x < summary_size; ++x)
//   {
//     for (size_t y = 1; y < summary_size; ++y)
//     {
//       float current_brightness = image.pixel(x, y).brightness();
//       float previous_brightness = image.pixel(x, y - 1).brightness();
//       result.vertical[x] = (current_brightness > previous_brightness);
//     }
//   }

//   return result;
// }

// int main(int argc, const char *argv[])
// {
//   WindowPtr window = Window::create(argc, argv);

//   if (argc < 2)
//   {
//     cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
//     cerr << "Missing directory containing files!" << endl;
//     return 1;
//   }

//   vector<string> files = list_files(argv[1], ".jpg");
//   cout << "Found " << files.size() << " image files." << endl;

//   if (files.size() <= 0)
//   {
//     cerr << "No files found! Make sure you entered a proper path!" << endl;
//     return 1;
//   }

//   auto begin = std::chrono::high_resolution_clock::now();

//   unordered_map<Image_Summary, vector<string>> summary_map;

//   for (const auto &file : files)
//   {
//     Image img = load_image(file).shrink(32, 32);
//     Image_Summary summary = compute_summary(img);

//     summary_map[summary].push_back(file);
//   }

//   auto end = std::chrono::high_resolution_clock::now();
//   cout << "Summary computation took: "
//        << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
//        << " milliseconds." << endl;

//   // Vi har nu en lista med alla bilder grupperade efter sina sammanfattningar.
//   for (const auto &entry : summary_map)
//   {
//     if (entry.second.size() > 1)
//     {
//       // Rapportera alla bilder som dubbletter, eftersom de har samma sammanfattning.
//       window->report_match(entry.second);
//     }
//   }

//   return 0;
// }
