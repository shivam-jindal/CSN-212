//Solution for a test case at Ideone : http://ideone.com/t876p4

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

//Struct of Point having x and y coordinates as integers
struct Point
{
    int x, y;
};

int determinant(Point p, Point q, Point r)
{
    return (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y);
}


//function to compare points w.r.t. their x coordinates
bool comp(Point a, Point b)
{
    return (a.x<b.x);
}


//Function to find the partial hull of passed points
void findPartialHull(vector<Point> &arr, vector<Point> &result, Point p1, Point pn)
{
    vector<Point> s1 = vector<Point>();   //holds Points of a part

    for (vector<Point>::iterator it = arr.begin(); it < arr.end(); it++)
    {
        if (determinant(p1,pn,*it) > 0)
        {
            //if the Point is on the left of p1-->pn line put it into the vector
            s1.push_back(*it);
        }
    }
    if (s1.empty())
    {
        //if s1 is empty, write p1 to result array; base case
        result.push_back(p1);
    }
    else
    {
        float maxDist = 0;  //distance to p1-->pn line
        Point pmax;    //hold the Pointer of pmax
        float dist;
        float length = sqrt(pow(p1.x - pn.x, 2) + pow(p1.y - pn.y, 2)); //length of p1-->pn line
        for (vector<Point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            dist = determinant(p1,pn,*it) / length; //distance(height) = area / length
            if (dist > maxDist)
            {
                //find the Point with max distance
                maxDist = dist;
                pmax = *it;
            }
        }
        //find Points left to p1-->pmax and pmax-->pn
        vector<Point> s11 = vector<Point>();  //holds Points left to p1-->pmax
        vector<Point> s12 = vector<Point>();  //holds Points left to pmax-->pn
        for (vector<Point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            //iterate s1 and find all Points we are looking for
            if (determinant(p1,pmax,*it) > 0)
            {
                //left to p1-->pmax
                s11.push_back(*it);
            }
            else if (determinant(pmax,pn,*it) > 0)
            {
                //left to pmax-->pn
                s12.push_back(*it);
            }
        }
        findPartialHull(s11, result, p1, pmax); //recursively search in s11
        findPartialHull(s12, result, pmax, pn); //recursively search in s12
    }
}


void quickHull(vector<Point> &P, int n) {

    vector<Point> upper = vector<Point>();
    vector<Point> lower = vector<Point>();

    //sort raw data in increasing order of x
    sort(P.begin(),P.end(),comp);

    findPartialHull(P, upper, P[0], P[n-1]);   //upper hull, line direction p1-->pn
    findPartialHull(P, lower, P[n-1], P[0]);   //lower hull, line direction pn-->p1

    //sort result in increasing order of x
    sort(upper.begin(),upper.end(),comp);
    sort(lower.begin(),lower.end(),comp);

    for (vector<Point>::iterator it = upper.begin(); it < upper.end(); it++)
    {
        //upper part, clock-wise
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    for (vector<Point>::iterator it = lower.end()-1; it >= lower.begin(); it--)
    {
        //reverse iterating order for lower part; still clock-wise
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
}


int main()
{
    //take number of Points as input
    int n;
    cin>> n;

    //create an array to store those Points
    vector<Point> P = vector<Point>();

    for (int i = 0; i < n; i++){
        Point p;
        cin>>p.x>>p.y;
        P.push_back(p); }

    clock_t tStart = clock();

    //print the Points on convex hull
    cout<<"Points on the convex hull are :" << endl;
    quickHull(P, n);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
