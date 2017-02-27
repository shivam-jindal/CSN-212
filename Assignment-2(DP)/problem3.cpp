#include <bits/stdc++.h>
using namespace std;

/*
  function to return length of longest increasing subsequence of n guests stating from startingPosition
 */
int findLengthOfLIS(int startingPosition, int numberOfGuests, int a[]){
	int dp[2*numberOfGuests];

	for(int i=startingPosition; i<startingPosition+numberOfGuests; i++)
	{
		int max = 0;
		for(int j=0;j<i;j++)
		{
			if(a[i] > a[j])
			{
				if(max < dp[j])max = dp[j];
			}
		}
		dp[i] = max + 1;
	}

	int ans = 0;
	for(int i=startingPosition; i<startingPosition+numberOfGuests; i++){
		if(ans < dp[i])
			ans = dp[i];
	}
	return ans;
}

int main() {
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;

		//an array of size 2n so that any circular sequence of length n can be picked up
		int a[2*n];
		for(int i=0; i<n; i++){
			cin >> a[i];
			a[i+n] = a[i];
		}
		int maxPeopleForLuckyDraw = 0;
		for(int i=0; i<n; i++){
			int temp = findLengthOfLIS(i, n, a);
			if(temp > maxPeopleForLuckyDraw)
				maxPeopleForLuckyDraw = temp;
		}
		cout << maxPeopleForLuckyDraw << endl;
	}
	return 0;
}

