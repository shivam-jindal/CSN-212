#include <bits/stdc++.h>
#include <vector>
#include <string.h>
using namespace std;

/*function to check whether the move is blocked or not*/
bool ifMoveBlocked(vector<string> bad, int a, int b, int c, int d){
    //convert in form of elements of bad array
    string move1 = to_string(a)+" "+to_string(b)+" "+to_string(c)+" "+to_string(d);
    string move2 = to_string(c)+" "+to_string(d)+" "+to_string(a)+" "+to_string(b);

    bool move1Found = find(bad.begin(), bad.end(), move1) != bad.end();
    bool move2Found = find(bad.begin(), bad.end(), move2) != bad.end();

    return move1Found || move2Found;
    }

/*function to return all possible number of distinct paths*/
long numWays(int width, int height, vector<string> bad){
    long dp[height+1][width+1];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;

	for(int i=0; i<=height; i++){
		for(int j=0; j<=width; j++){
			if ((!ifMoveBlocked(bad, j,i-1,j,i)) && (i!=0))
				dp[i][j] += dp[i-1][j];
			if ((!ifMoveBlocked(bad, j-1,i,j,i)) && (j!=0))
				dp[i][j] += dp[i][j-1];
		}
	}
	return dp[height][width];
}

int main(){
    //check for a test input
    int width = 6;
    int height = 6;
    vector<string> bad = {"0 0 0 1","6 6 5 6"};

    cout<<"Number of distinct paths for test input is "<< numWays(width, height, bad)<<endl;

    return 0;
}
