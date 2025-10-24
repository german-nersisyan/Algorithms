#include <iostream>
#include <vector>
#include <queue>

std::pair<int, int> up(const std::vector<std::vector<int>>& matrix, std::pair<int, int> coordinate)
{
    if(coordinate.first == 0 || matrix[coordinate.first - 1][coordinate.second] == 1) {
        return {-1, -1};
    }
    return {coordinate.first - 1, coordinate.second};
}

std::pair<int, int> down(const std::vector<std::vector<int>>& matrix, std::pair<int, int> coordinate)
{
    if(coordinate.first == matrix.size() - 1 || matrix[coordinate.first + 1][coordinate.second] == 1) {
        return {-1, -1};
    }
    return {coordinate.first + 1, coordinate.second};
}

std::pair<int, int> right(const std::vector<std::vector<int>>& matrix, std::pair<int, int> coordinate)
{
    if(coordinate.second == matrix[0].size() - 1 || matrix[coordinate.first][coordinate.second + 1] == 1) {
        return {-1, -1};
    }
    return {coordinate.first, coordinate.second + 1};
}

std::pair<int, int> left(const std::vector<std::vector<int>>& matrix, std::pair<int, int> coordinate)
{
    if(coordinate.second == 0 || matrix[coordinate.first][coordinate.second - 1] == 1) {
        return {-1, -1};
    }
    return {coordinate.first, coordinate.second - 1};
}

void WaveAlgorithm(std::vector<std::vector<int>> matrix, std::pair<int, int> source, std::pair<int, int> destination)
{
    int n = matrix.size();
    int m = matrix[0].size();
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, -1));
    distance[source.first][source.second] = 0;
    
    std::queue<std::pair<int, int>> q;
    q.push(source);
    
    while(!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        
        if(up(matrix, current) != std::pair<int, int>{-1, -1} && distance[up(matrix, current).first][up(matrix, current).second] == -1) {
            q.push(up(matrix, current));
            distance[up(matrix, current).first][up(matrix, current).second] = distance[current.first][current.second] + 1;
        }
        if(left(matrix, current) != std::pair<int, int>{-1, -1} && distance[left(matrix, current).first][left(matrix, current).second] == -1) {
            q.push(left(matrix, current));
            distance[left(matrix, current).first][left(matrix, current).second] = distance[current.first][current.second] + 1;
        }
        if(down(matrix, current) != std::pair<int, int>{-1, -1} && distance[down(matrix, current).first][down(matrix, current).second] == -1) {
            q.push(down(matrix, current));
            distance[down(matrix, current).first][down(matrix, current).second] = distance[current.first][current.second] + 1;
        }
        if(right(matrix, current) != std::pair<int, int>{-1, -1} && distance[right(matrix, current).first][right(matrix, current).second] == -1) {
            q.push(right(matrix, current));
            distance[right(matrix, current).first][right(matrix, current).second] = distance[current.first][current.second] + 1;
        }
    }
    
    if(distance[destination.first][destination.second] != -1) {
        std::cout << "Shortest path length is " << distance[destination.first][destination.second] << std::endl;
    }
}

int main()
{
    std::vector<std::vector<int>> matrix = { { 0, 0, 0, 1 },
                                             { 0, 1, 1, 0 },
                                             { 0, 0, 0, 0 },
                                             { 0, 1, 1, 0 } };
    WaveAlgorithm(matrix, std::pair<int, int>{0, 0}, std::pair<int, int>{1, 3});                                      
    return 0;
}