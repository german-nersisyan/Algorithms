#include <iostream>
#include <vector>
#include <climits>

int matrixChainMultiplication(const std::vector<int>& p)
{
    int n = p.size() - 1;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

    for (int length = 2; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = std::min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];
}

int main()
{
    std::vector<int> p = {10, 30, 5, 60};

    std::cout << "Minimum number of multiplications: " << matrixChainMultiplication(p) << std::endl;

    return 0;
}