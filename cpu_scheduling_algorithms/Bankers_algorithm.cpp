#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int R = 3;

class BankersAlgorithm {
private:
    vector<int> processes;
    vector<int> available;
    vector<vector<int>> maxm;
    vector<vector<int>> allocation;
    vector<vector<int>> need;
    int num_processes, num_resources;

public:
    BankersAlgorithm(vector<int> p, vector<int> a, vector<vector<int>> m, vector<vector<int>> alloc, int n, int r) {
        num_processes = n;
        num_resources = r;
        processes = p;
        available = a;
        maxm = m;
        allocation = alloc;
        need = vector<vector<int>>(n, vector<int>(r, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < r; j++) {
                need[i][j] = maxm[i][j] - allocation[i][j];
            }
        }
    }

    bool isSafe() {
        vector<int> work(available.begin(), available.end());
        vector<bool> finish(num_processes, false);
        vector<int> safeSeq(num_processes, 0);

        int count = 0;
        while (count < num_processes) {
            bool found = false;
            for (int p = 0; p < num_processes; p++) {
                if (!finish[p]) {
                    bool can_allocate = true;
                    for (int j = 0; j < num_resources; j++) {
                        if (need[p][j] > work[j]) {
                            can_allocate = false;
                            break;
                        }
                    }
                    if (can_allocate) {
                        for (int j = 0; j < num_resources; j++) {
                            work[j] += allocation[p][j];
                        }
                        safeSeq[count++] = processes[p];
                        finish[p] = true;
                        found = true;
                    }
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
};

void test_algorithm() {
    // Test Case 1
    vector<int> processes1 = {0, 1, 2, 3, 4};
    vector<int> avail1 = {3, 3, 2};
    vector<vector<int>> maxm1 = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> allot1 = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    BankersAlgorithm banker1(processes1, avail1, maxm1, allot1, 5, 3);
    cout << "Test Case 1: " << (banker1.isSafe() ? "Safe" : "Not Safe") << endl;

    // Test Case 2
    vector<int> processes2 = {0, 1, 2};
    vector<int> avail2 = {1, 2, 2};
    vector<vector<int>> maxm2 = {{2, 2, 2}, {3, 2, 2}, {2, 2, 2}};
    vector<vector<int>> allot2 = {{1, 0, 1}, {2, 0, 0}, {1, 2, 1}};

    BankersAlgorithm banker2(processes2, avail2, maxm2, allot2, 3, 3);
    cout << "Test Case 2: " << (banker2.isSafe() ? "Safe" : "Not Safe") << endl;
}

int main() {
    test_algorithm();
    return 0;
}
