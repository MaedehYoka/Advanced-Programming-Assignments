#include "getPath.hpp"
#include <queue>
typedef pair<int, int> pii;

pii findStart(const vector<vector<char>>& board,int rows,int cols){
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (board[i][j] == 'S')
                return {i, j};
    
    return {0,0};
}

vector<pii> getPath(const vector<vector<char>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pii> path;

    int dx[] = { 1, 0,-1, 0};
    int dy[] = { 0, -1,0, 1};

    pii start= findStart(board,rows,cols);
    queue<pii> q;
    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        pii current = q.front(); q.pop();
        path.push_back(current);

        if (board[current.first][current.second] == 'F')
            break;

        for (int d = 0; d < 4; d++) {
            int ni = current.first + dx[d];
            int nj = current.second + dy[d];

            if (ni >= 0 && nj >= 0 && ni < rows && nj < cols &&
                !visited[ni][nj] &&
                (board[ni][nj] == 'O' || board[ni][nj] == 'F')) {
                visited[ni][nj] = true;
                q.push({ni, nj});
                break;
            }
        }
    }
    return path;
}
