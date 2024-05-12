/*
 Q1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int maxMeetings(int start[], int end[], int N) {

    vector<pair<int, int>> meetings;


    for (int i = 0; i < N; i++) {
        meetings.push_back({ end[i], start[i] });
    }


    sort(meetings.begin(), meetings.end());


    int count = 0;

    int last_end_time = 0;


    for (int i = 0; i < N; i++) {

        if (meetings[i].second > last_end_time) {

            count++;

            last_end_time = meetings[i].first;
        }
    }

    return count;
}

int main() {
    // Example 1
    int N1 = 6;
    int start1[] = { 1, 3, 0, 5, 8, 5 };
    int end1[] = { 2, 4, 6, 7, 9, 9 };
    cout << "Maximum number for example 1: " << maxMeetings(start1, end1, N1) << endl;

    // Example 2
    int N2 = 3;
    int start2[] = { 10, 12, 20 };
    int end2[] = { 20, 25, 30 };
    cout << "Maximum numberr for example 2: " << maxMeetings(start2, end2, N2) << endl;

    return 0;
}
Q2
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>  

using namespace std;

int findMaxDeadline(const vector<tuple<int, int, int>>& tasks) {
    int maxDeadline = 0;
    for (const auto& task : tasks) {
        maxDeadline = max(maxDeadline, get<1>(task));
    }
    return maxDeadline;
}

vector<int> TaskScheduling(int N, vector<tuple<int, int, int>> tasks) {
    sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
        return get<2>(a) > get<2>(b);
        });

    int maxDeadline = findMaxDeadline(tasks);
    vector<bool> slot(maxDeadline + 1, false);

    int countTasks = 0, totalProfit = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = min(maxDeadline, get<1>(tasks[i])); j > 0; --j) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += get<2>(tasks[i]);
                countTasks++;
                break;
            }
        }
    }

    return { countTasks, totalProfit };
}

int main() {
    vector<tuple<int, int, int>> tasks1 = { {1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30} };
    auto result1 = TaskScheduling(4, tasks1);
    cout << "Number of tasks done: " << result1[0] << ", Maximum profit: " << result1[1] << endl;

    vector<tuple<int, int, int>> tasks2 = { {1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 1, 15} };
    auto result2 = TaskScheduling(5, tasks2);
    cout << "Number of tasks done: " << result2[0] << ", Maximum profit: " << result2[1] << endl;

    return 0;
}
Q3
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
    int first, second;
};

int calculateMaxChainLength(Pair arr[], int n) {
    sort(arr, arr + n, [](const Pair& a, const Pair& b) {
        return a.second < b.second;
        });

    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j].second < arr[i].first) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

int main() {
    Pair arr1[] = { {5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90} };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Maximum length of chain is " << calculateMaxChainLength(arr1, n1) << endl;

    Pair arr2[] = { {5, 10}, {1, 11} };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Maximum length of chain is " << calculateMaxChainLength(arr2, n2) << endl;

    return 0;
}
Q4
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
    int first, second;
};

int calculateMaxChainLength(Pair arr[], int n) {
    sort(arr, arr + n, [](const Pair& a, const Pair& b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
        });

    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j].second < arr[i].first && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

int main() {
    Pair arr1[] = { {5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90} };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Maximum length of chain is " << calculateMaxChainLength(arr1, n1) << endl;

    Pair arr2[] = { {5, 10}, {1, 11} };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Maximum length of chain is " << calculateMaxChainLength(arr2, n2) << endl;

    return 0;
}
Q5
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Pair {
    int x, y;
};

void explorePaths(vector<vector<int>>& matrix, int x, int y, vector<string>& paths, string path, int size) {
    if (x < 0 || x >= size || y < 0 || y >= size || matrix[x][y] == 0) return;
    if (x == size - 1 && y == size - 1) {
        paths.push_back(path);
        return;
    }

    matrix[x][y] = 0; // Mark the cell as visited
    // Explore all possible directions
    if (x < size - 1) { // Move down
        explorePaths(matrix, x + 1, y, paths, path + 'D', size);
    }
    if (y < size - 1) { // Move right
        explorePaths(matrix, x, y + 1, paths, path + 'R', size);
    }
    if (x > 0) { // Move up
        explorePaths(matrix, x - 1, y, paths, path + 'U', size);
    }
    if (y > 0) { // Move left
        explorePaths(matrix, x, y - 1, paths, path + 'L', size);
    }
    matrix[x][y] = 1; // Unmark the cell
}

vector<string> findPaths(int size, vector<vector<int>>& matrix) {
    vector<string> paths;
    if (matrix[0][0] == 1 && matrix[size - 1][size - 1] == 1) { // Check if start and end are accessible
        explorePaths(matrix, 0, 0, paths, "", size);
    }
    sort(paths.begin(), paths.end());
    return paths;
}

int main() {
    int size1 = 4;
    vector<vector<int>> matrix1 = { {1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1} };
    vector<string> result1 = findPaths(size1, matrix1);
    if (result1.empty()) {
        cout << "-1" << endl;
    }
    else {
        for (const string& s : result1) {
            cout << s << " ";
        }
        cout << endl;
    }

    int size2 = 2;
    vector<vector<int>> matrix2 = { {1, 0}, {1, 0} };
    vector<string> result2 = findPaths(size2, matrix2);
    if (result2.empty()) {
        cout << "-1" << endl;
    }
    else {
        for (const string& s : result2) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}
//
Q6
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void explorePathsUtil(vector<vector<int>>& matrix, int x, int y, string path, vector<string>& paths, vector<vector<bool>>& visited) {
    int N = matrix.size();
    if (x < 0 || y < 0 || x >= N || y >= N || matrix[x][y] == 0 || visited[x][y])
        return;

    if (x == N - 1 && y == N - 1) {
        paths.push_back(path);
        return;
    }

    visited[x][y] = true;

    // Move down
    if (x + 1 < N && !visited[x + 1][y] && matrix[x + 1][y] == 1)
        explorePathsUtil(matrix, x + 1, y, path + 'D', paths, visited);

    // Move right
    if (y + 1 < N && !visited[x][y + 1] && matrix[x][y + 1] == 1)
        explorePathsUtil(matrix, x, y + 1, path + 'R', paths, visited);

    // Move left
    if (y - 1 >= 0 && !visited[x][y - 1] && matrix[x][y - 1] == 1)
        explorePathsUtil(matrix, x, y - 1, path + 'L', paths, visited);

    visited[x][y] = false;
}

vector<string> findPaths(vector<vector<int>>& matrix) {
    int N = matrix.size();
    vector<string> paths;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    if (matrix[0][0] == 0)
        return paths; // No path if the starting cell is blocked
    explorePathsUtil(matrix, 0, 0, "", paths, visited);
    return paths;
}

int main() {
    vector<vector<int>> matrix1 = { {1, 0, 0, 0},
                                   {1, 1, 0, 1},
                                   {1, 1, 0, 0},
                                   {0, 1, 1, 1} };
    vector<string> paths1 = findPaths(matrix1);
    if (paths1.empty())
        cout << "-1" << endl;
    else {
        for (const string& path : paths1)
            cout << path << " ";
        cout << endl;
    }

    vector<vector<int>> matrix2 = { {1, 0},
                                   {1, 0} };
    vector<string> paths2 = findPaths(matrix2);
    if (paths2.empty())
        cout << "-1" << endl;
    else {
        for (const string& path : paths2)
            cout << path << " ";
        cout << endl;
    }

    return 0;
}
Q7
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c) {
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[v][i] && color[i] == c) return false;
    }
    return true;
}

bool paintGraph(vector<vector<int>>& graph, vector<int>& color, int m, int v) {
    int n = graph.size();
    if (v == n) return true;

    for (int c = 1; c <= m; ++c) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (paintGraph(graph, color, m, v + 1))
                return true;
            color[v] = 0;  // Backtrack
        }
    }
    return false;
}

int canColorGraph(vector<vector<int>>& graph, int m) {
    int n = graph.size();
    vector<int> color(n, 0);
    return paintGraph(graph, color, m, 0) ? 1 : 0;
}

vector<vector<int>> createGraph(int N, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(N, vector<int>(N, 0));
    for (auto& edge : edges) {
        graph[edge.first][edge.second] = 1;
        graph[edge.second][edge.first] = 1; // Since the graph is undirected
    }
    return graph;
}

int main() {
    // Example 1
    int N1 = 4, M1 = 3;
    vector<pair<int, int>> edges1 = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2} };
    vector<vector<int>> graph1 = createGraph(N1, edges1);
    cout << "Example 1: " << canColorGraph(graph1, M1) << endl;

    // Example 2
    int N2 = 3, M2 = 2;
    vector<pair<int, int>> edges2 = { {0, 1}, {1, 2}, {0, 2} };
    vector<vector<int>> graph2 = createGraph(N2, edges2);
    cout << "Example 2: " << canColorGraph(graph2, M2) << endl;

    return 0;
}
Q8
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool validateString(string str) {
    int n = str.length();
    if (n > 3)
        return false;
    if (str[0] == '0' && n > 1)
        return false;
    int num = stoi(str);
    return num >= 0 && num <= 255;
}

void generateIPAddress(string S, int pos, vector<string>& result, vector<string>& current) {
    if (current.size() == 4 && pos == S.length()) {
        result.push_back(current[0] + '.' + current[1] + '.' + current[2] + '.' + current[3]);
        return;
    }
    if (current.size() == 4 || pos == S.length())
        return;

    for (int len = 1; len <= 3 && pos + len <= S.length(); ++len) {
        string part = S.substr(pos, len);
        if (validateString(part)) {
            current.push_back(part);
            generateIPAddress(S, pos + len, result, current);
            current.pop_back();
        }
    }
}

vector<string> generateValidIPAddresses(string& S) {
    vector<string> result;
    if (S.length() < 4 || S.length() > 12)
        return { "-1" };
    vector<string> current;
    generateIPAddress(S, 0, result, current);
    if (result.empty())
        return { "-1" };
    return result;
}

int main() {
    string S = "99999999999";
    vector<string> result = generateValidIPAddresses(S);
    if (result.size() == 1 && result[0] == "-1")
        cout << "Output: -1" << endl;
    else {
        cout << "Output:";
        for (auto ip : result)
            cout << " " << ip;
        cout << endl;
    }

    return 0;
}
Q9
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool endWord;

    TrieNode() {
        for (int i = 0; i < 26; ++i)
            children[i] = nullptr;
        endWord = false;
    }
};

void addWord(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'A'; 
        if (!curr->children[index])
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    curr->endWord = true;
}

void searchWord(vector<vector<char>>& board, int row, int col, TrieNode* root, string path, unordered_set<string>& result, vector<vector<bool>>& visited) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || visited[row][col])
        return;

    int index = board[row][col] - 'A';
    if (!root->children[index])
        return;

    path += board[row][col];
    if (root->children[index]->endWord)
        result.insert(path);

    visited[row][col] = true;

    int rowMove[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int colMove[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (int i = 0; i < 8; ++i)
        searchWord(board, row + rowMove[i], col + colMove[i], root->children[index], path, result, visited);

    visited[row][col] = false;
}

vector<string> boggleWords(vector<vector<char>>& board, vector<string>& dictionary) {
    unordered_set<string> result;
    int rows = board.size();
    int cols = board[0].size();

    TrieNode* root = new TrieNode();
    for (string word : dictionary)
        addWord(root, word);

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            string path = "";
            searchWord(board, i, j, root, path, result, visited);
        }
    }

    vector<string> res(result.begin(), result.end());
    return res;
}

int main() {
    int R = 3, C = 3;
    vector<vector<char>> board = { {'G','I','Z'}, {'U','E','K'}, {'Q','S','E'} };
    int N = 4;
    vector<string> dictionary = { "GEEKS", "FOR", "QUIZ", "GO" };

    vector<string> words = boggleWords(board, dictionary);

    for (string word : words)
        cout << word << " ";
    cout << endl;

    return 0;
    Q10
#include <iostream>
#include <vector>

    using namespace std;

    int findKth(int arr1[], int arr2[], int n, int m, int k) {
        int i = 0, j = 0, count = 0;
        int result;

        while (i < n && j < m && count < k) {
            if (arr1[i] < arr2[j])
                result = arr1[i++];
            else
                result = arr2[j++];
            count++;
        }

        if (count == k)
            return result;

        while (i < n && count < k) {
            result = arr1[i++];
            count++;
        }
        while (j < m && count < k) {
            result = arr2[j++];
            count++;
        }

        return result;
    }

    int main() {
        int arr1[] = { 2, 3, 6, 7, 9 };
        int arr2[] = { 1, 4, 8, 10 };
        int n = sizeof(arr1) / sizeof(arr1[0]);
        int m = sizeof(arr2) / sizeof(arr2[0]);
        int k = 5;

        cout << "Output: " << findKth(arr1, arr2, n, m, k) << endl;

        return 0;
    Q12
#include <iostream>
#include <vector>
#include <algorithm>

    using namespace std;

    bool olasý(int arr[], int n, int m, int orta) {
        int gerekenOgrenciSayisi = 1;
        int ayrýlanSayfa = 0;

        for (int i = 0; i < n; ++i) {
            if (arr[i] > orta)
                return false;

            if (ayrýlanSayfa + arr[i] > orta) {
                gerekenOgrenciSayisi++;
                ayrýlanSayfa = arr[i];

                if (gerekenOgrenciSayisi > m)
                    return false;
            }
            else {
                ayrýlanSayfa += arr[i];
            }
        }

        return true;
    }

    int minSayfa(int arr[], int n, int m) {
        if (n < m)
            return -1;

        int toplam = 0, maxSayfa = 0;

        for (int i = 0; i < n; ++i) {
            toplam += arr[i];
            maxSayfa = max(maxSayfa, arr[i]);
        }

        int düþük = maxSayfa, yüksek = toplam, sonuç = -1;

       
        while (düþük <= yüksek) {
            int orta = (düþük + yüksek) / 2;

            if (olasý(arr, n, m, orta)) {
                sonuç = orta;
                yüksek = orta - 1;
            }
            else {
                düþük = orta + 1;
            }
        }

        return sonuç;
    }

    int main() {
        int N = 3;
        int A[] = { 15, 17, 20 };
        int M = 2;

        cout << "Çýktý: " << minSayfa(A, N, M) << endl;

        return 0;
    }*/