#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>
using namespace std; 

int board[201][201]; 
int dist[201][201][31];

int dy[] = { -1, 1, 0, 0 }; 
int dx[] = { 0, 0 ,1, -1 }; 

int hy[] = { -2, -2, -1, -1, 1, 1, 2, 2 }; 
int hx[] = { -1, 1, -2, 2, -2, 2, -1, 1}; 

int k, n, m;

bool isOut(int y, int x) {
	return y < 0 || y >= n || x < 0 || x >= m; 
}

void bfs() {
	queue<tuple<int, int, int>> q; 
	q.push(make_tuple(0, 0, k)); 
	dist[0][0][k] = 0;
	while(!q.empty()) {
		int y, x, jump; tie(y, x, jump) = q.front(); q.pop(); 
		if (jump > 0) {
			for (int direction = 0; direction < 8; direction++) {
				int ny = y + hy[direction], nx = x + hx[direction]; 
				if (isOut(ny, nx) || dist[ny][nx][jump - 1] != -1 || board[ny][nx] == 1) continue; 
				q.push(make_tuple(ny, nx, jump - 1));
				dist[ny][nx][jump - 1] = dist[y][x][jump] + 1; 
			}
		}
		for (int direction = 0; direction < 4; direction++) {
			int ny = y + dy[direction], nx = x + dx[direction]; 
			if (isOut(ny, nx) || dist[ny][nx][jump] != -1 || board[ny][nx] == 1) continue;
			q.push(make_tuple(ny, nx, jump)); 
			dist[ny][nx][jump] = dist[y][x][jump] + 1; 
		}
	}
}

int main() {
	cin >> k >> m >> n; 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j]; 
	memset(dist, -1, sizeof(dist)); 
	bfs(); 
	
	int ret = -1; 
	for (int i = 0; i <= k; i++)
		if (dist[n - 1][m - 1][i] != -1)
			if (ret == -1 || ret > dist[n - 1][m - 1][i]) 
				ret = dist[n - 1][m - 1][i]; 
	cout << ret << endl;
	return 0; 
}