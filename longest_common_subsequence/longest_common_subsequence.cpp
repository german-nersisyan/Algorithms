#include <iostream>
#include <vector>
#include <algorithm>

std::string lcs(std::string X, std::string Y)
{
    int n = X.size(), m = Y.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::string result;
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result.push_back(X[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    std::reverse(result.begin(), result.end());
    
    return result;
}

int main() {
    std::string X = "ABCBDAB";
    std::string Y = "BDCAB";

    std::cout << "LCS: " << lcs(X, Y) << std::endl;
    return 0;
}