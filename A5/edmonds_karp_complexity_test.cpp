#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
//Alpay Nacar
using namespace std;

#define INF 1e9
int n;
vector<unordered_map<int, int>> capacity;
vector<unordered_set<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({ s, INF });

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({ next, new_flow });
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    time_t start, finish;
    for (int m = 200; m <= 3000; m += 200) {

        // nodes
        // 0 : source
        // 1 - m : students
        // m+1 - 2m: projects
        // 2m+1 : sink

        n = 2 * m + 2;
        adj = vector<unordered_set<int>>(2 * m + 2, unordered_set<int>());
        capacity = vector<unordered_map<int, int>>(2 * m + 2, unordered_map<int, int>());

        // connect source to student
        for (int student = 1; student <= m; student++) {
            adj[0].insert(student);
            capacity[0][student] = 1;
        }

        // connect student to project
        for (int student = 1; student <= m; student++) {
            for (int project = m + 1; project <= 2 * m; project++) {
                adj[student].insert(project);
                capacity[student][project] = 1;
            }
        }

        // connect project to sink
        for (int project = m + 1; project <= 2 * m; project++) {
            adj[project].insert(2 * m + 1);
            capacity[project][2 * m + 1] = 1;
        }

        time(&start);
        int res = maxflow(0, 2 * m + 1);
        time(&finish);

        cout << "Result of m " << m << ": " << res << " took " << difftime(finish, start) << " seconds" << endl;
    }

    return 0;
}
