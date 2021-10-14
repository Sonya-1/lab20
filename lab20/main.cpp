#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

void open_fill (vector<vector<int>>& r, int& s, int& n) {
    ifstream file("C:\\tmp\\file.txt", ios::ate);
    if (!file) {
        cout << "File not open" << endl;
        return;
    }

    streamoff size = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> buffer(size);
    file.read(buffer.data(), size);
    file.close();

    int start = 0;
    char* pch;
    int line_number = 0;
    vector<char*> lines(0);

    pch = strtok(&buffer[0], "\r\n");
    while (pch != NULL) {
        line_number++;
        if (line_number == 1) {
            start = stoi(pch);
        }
        else {
            lines.push_back(pch);
        }
        pch = strtok(NULL, "\r\n");
    }
    s = start;
    //cout << start << endl;
    vector<vector<int>> rows(0);
    unsigned long i;
    for (i = 0; i < lines.size(); i++) {
        vector<int> row(0);
        pch = strtok(lines[i], " \t");
        while (pch != NULL) {
            row.push_back(stoi(pch));
            pch = strtok(NULL, " \t");
        }
        rows.push_back(row);
    }
    /*
    unsigned long j;
    for (i = 0; i < rows.size(); i++) {
        auto row = rows[i];
        for (j = 0; j < row.size(); j++) {
            cout << row[j];
        }
        cout << endl;
    }
    */
    r = rows;
    n = rows.size();
   // return rows;
    //cout << "rows[1][1]=" << rows[1][1] << endl;
}

void dfs(vector<int>& visited, vector<vector<int>>& matrix, int cur, int n, vector<int>& colors, ofstream& out) {
    colors[cur] = GRAY;
    visited[cur] = 1;
    /*
    ofstream out;
    out.open("C:\\tmp\\fileout.txt", ios::trunc);// , ios::app&& ios::trunc);
    if (!out) {
        cout << "Fule not open" << endl;
    }
    */
    for (int i = 0; i < n; i++) {
        if (matrix[cur][i] == 1) {
            if (cur != i) {
                if (colors[i] == GRAY) {
                    out << cur << " " << i << " : back edge" << endl;
                }
                else if (colors[i] == BLACK) {
                    out << cur << " " << i << " : cross edge" << endl;
                }
                else {
                    out << cur << " " << i << " : forward edge" << endl;
                }
            }
            if (visited[i] == 0) {
                dfs(visited, matrix, i, n, colors, out);
            }
        }
    }
    colors[cur] = BLACK;
    //out.close();
}

int main() {
    int start = 0, n = 0;
    vector<vector<int>> matrix;
    open_fill(matrix, start, n);
    vector<int> visited(n, 0);
    vector<int> colors(n, WHITE);
    ofstream out;
    out.open("C:\\tmp\\fileout.txt", ios::trunc);
    if (!out) {
        cout << "Fule not open" << endl;
        return 1;
    }
    dfs(visited, matrix, start, n, colors, out);
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            dfs(visited, matrix, i, n, colors, out);
        }
    }
    out.close();
    return 0;
}