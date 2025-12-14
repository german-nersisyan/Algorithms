#include <iostream>
#include <vector>
#include <climits>

int mcm(int i, int j, const std::vector<int>& p, std::vector<std::vector<int>>& dp)
{
    if (i == j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int ans = INT_MAX;

    for (int k = i; k < j; k++) {
        int cost = mcm(i, k, p, dp) + mcm(k + 1, j, p, dp)+ p[i - 1] * p[k] * p[j];
        ans = std::min(ans, cost);
    }

    dp[i][j] = ans;
    return ans;
}

int main()
{
    std::vector<int> p = {10, 30, 5, 60};
    int n = p.size() - 1;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, -1));

    std::cout << "Minimum number of multiplications: " << mcm(1, n, p, dp) << std::endl;

    return 0;
}