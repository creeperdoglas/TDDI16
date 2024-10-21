#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"

using namespace std;

int main(int argc, const char *argv[])
{
    WindowPtr window = create_window(argc, argv);
    if (!window)
        return 1;

    // The array of points
    vector<Point> points;

    // Read tolerance from cin
    double tolerance{};
    cin >> tolerance;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i)
    {
        double x{}, y{};
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // Draw points to screen all at once
    window->draw_points(points);

    auto begin = chrono::high_resolution_clock::now();

    // Iterate through all possible origins:
    for (int o{0}; o < N; ++o)
    {
        // Sort points based on the angle with respect to the origin point
        // Instead of copying, we sort the indices.
        vector<int> indices(N);
        iota(indices.begin(), indices.end(), 0); // Create an index vector [0, 1, 2, ... N-1]

        // Sort the indices based on slope with respect to point[o]
        sort(indices.begin(), indices.end(), [&](int i, int j)
             { return points[o].slopeTo(points[i]) < points[o].slopeTo(points[j]); });

        // Now find all collinear points
        for (std::vector<int>::size_type i = 0; i < indices.size(); ++i)
        {
            vector<Point> series{points[o], points[indices[i]]};

            for (std::vector<int>::size_type j = i + 1; j < indices.size(); ++j)
            {
                if (abs(points[o].slopeTo(points[indices[i]]) - points[o].slopeTo(points[indices[j]])) < tolerance)
                {
                    series.push_back(points[indices[j]]);
                }
                else
                {
                    // Break early since the list is sorted
                    break;
                }
            }

            // If we have at least 4 points (including the origin point)
            if (series.size() >= 4)
            {
                window->draw_line(series);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // Wait for user to terminate program
    window->run();

    return 0;
}
