/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <iostream>
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

    // draw points to screen all at once
    window->draw_points(points);

    // Sort points by their natural order. Makes finding endpoints a bit easier.
    sort(points.begin(), points.end());

    auto begin = chrono::high_resolution_clock::now();
    // Iterate over each point as the reference point
    for (int i{0}; i < N; ++i)
    {
        // Create a vector to hold points and their slopes relative to point[i]
        vector<Point> slopePoints = points;

        // Sort other points based on the slope with respect to points[i]
        sort(slopePoints.begin() + i + 1, slopePoints.end(), PolarSorter(points[i]));

        // Now check for consecutive points with the same slope
        int j = 1;
        while (j < slopePoints.size() - 1)
        {
            vector<Point> collinear{points[i]};

            // Check if the slope between consecutive points is the same
            while (j < slopePoints.size() &&
                   points[i].sameSlope(slopePoints[j], slopePoints[j + 1], tolerance))
            {
                collinear.push_back(slopePoints[j]);
                j++;
            }

            // If we found 3 or more points, draw the line
            if (collinear.size() >= 4)
            {
                window->draw_line(collinear);
            }

            // Move to the next set of points
            j++;
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw_line'.
    /////////////////////////////////////////////////////////////////////////////

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
