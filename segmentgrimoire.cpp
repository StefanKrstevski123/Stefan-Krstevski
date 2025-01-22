#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> data;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;

            build(leftChild, start, mid);
            build(rightChild, mid + 1, end);
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            data[idx] = val;
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;

            if (start <= idx && idx <= mid) {
                update(leftChild, start, mid, idx, val);
            } else {
                update(rightChild, mid + 1, end, idx, val);
            }
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        int leftSum = query(leftChild, start, mid, l, r);
        int rightSum = query(rightChild, mid + 1, end, l, r);
        return leftSum + rightSum;
    }

public:
    SegmentTree(vector<int>& input) {
        n = input.size();
        data = input;
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> input = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(input);

    cout << "Sum of range (1, 3): " << segTree.query(1, 3) << endl;

    segTree.update(1, 10);
    cout << "After update, sum of range (1, 3): " << segTree.query(1, 3) << endl;

    return 0;
}
