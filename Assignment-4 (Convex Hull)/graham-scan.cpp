//Solution for a test case at Ideone : http://ideone.com/699P9M

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

//Struct of Point having x and y coordinates as integers
struct Point
{
    int x, y;
};
Point p0;

// A function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}


// Function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}


// A utility function to return square of distance between p1 and p2
int distanceSquare(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


// To find orientation of ordered triplet (p, q, r).
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    if (val > 0) return 1;   // clockwise
    return 2;                // counterclock wise
}


int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *) vp1;
    Point *p2 = (Point *) vp2;

    // Find orientation
    int orient = orientation(p0, *p1, *p2);
    if (orient == 0)
        return (distanceSquare(p0, *p2) >= distanceSquare(p0, *p1)) ? -1 : 1;
    if(orient == 1) return 1;
    return -1;
}


// Prints convex hull of a set of n points.
void grahamScan(Point points[], int n)
{
    // Find the bottommost point
    int ymin = points[0].y;
    int minIndex = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        // Pick the bottom-most or chose the left most point in case of tie
        if ((y < ymin) || (ymin == y && points[i].x < points[minIndex].x))
            ymin = points[i].y, minIndex = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[minIndex]);

    // Sort n-1 points with respect to the first point.
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Create an empty stack and push first three points to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < n; i++)
    {
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    while (!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
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
    grahamScan(points, n);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
