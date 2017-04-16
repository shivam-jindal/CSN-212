//Solution for a test case at Ideone : http://ideone.com/TGvbNd

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

//Struct of Point having x and y coordinates as integers
struct Point
{
    int x, y;
};


// To find orientation of ordered triplet (p, q, r).
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    if (val > 0) return 1;   // clockwise
    return 2;                // counterclock wise
}


// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // There must be at least 3 points
    if (n < 3) return;

    vector<Point> convexHull;

    // Find the leftmost point
    int leftMost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftMost].x)
            leftMost = i;

    // Start from leftmost point, keep moving counter clock wise until reach the start point again.
    int p = leftMost, q;
    do
    {
        // Add current point to result
        convexHull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x,q) is counterclockwise for all points 'x'
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }

        p = q;

    } while (p != leftMost);

    for (int i = 0; i < convexHull.size(); i++)
        cout << "(" << convexHull[i].x << ", " << convexHull[i].y << ")" << endl;
}


int main()
{
    //take number of points as input
    int n;
    cin>> n;

    //create an array to store those points
    Point *points = new Point[n];

    for (int i = 0; i < n; i++)
        cin>> points[i].x >> points[i].y;

    clock_t tStart = clock();

    //print the points on convex hull
    cout<<"Points on the convex hull are :" << endl;
    convexHull(points, n);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
