#include <bits/stdc++.h>
using namespace std;

int longestZigZag(int inputSequence[], int n)
{

    int dp1[n], dp2[n];
    /*dp1[i] = Length of the longest Zig-Zag subsequence ending at index i and
      dp2[i]= Length of the longest Zig-Zag subsequence ending at index i and dp[i]<dp[i-1]
    */

    for (int i = 0; i < n; i++)
        dp1[i] = dp2[i] = 1;

    int answer = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // If inputSequence[i] is greater, then check with dp2[j]
            if (inputSequence[j] < inputSequence[i] && dp1[i] < dp2[j] + 1)
                dp1[i] = dp2[j] + 1;

            // If inputSequence[i] is smaller, then check with dp1[j]
            if( inputSequence[j] > inputSequence[i] && dp2[i] < dp1[j] + 1)
                dp2[i] = dp1[j] + 1;
        }

        //maximum of both values at index i will be the answer
        if (answer < max(dp1[i], dp2[i]))
            answer = max(dp1[i], dp2[i]);
    }

    return answer;
}

int main()
{
    int inputSequence[] = { 10, 22, 9, 33, 49, 50, 31, 60 };
    int n = sizeof(inputSequence)/sizeof(inputSequence[0]);
    printf("Length of Longest Zig-Zag subsequence is %d\n",
            longestZigZag(inputSequence, n) );

    return 0;
}
