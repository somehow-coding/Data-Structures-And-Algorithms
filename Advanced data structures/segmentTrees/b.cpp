#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector<int> seg;
    SegmentTree() {
    }

    void setSize(int N) {
        seg.resize(4 * N);
    }

    void build(int index, vector<int> &nums, int low, int high) {
        if (low == high) {
            seg[index] = nums[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * index + 1, nums, low, mid);
        build(2 * index + 2, nums, mid + 1, high);
        seg[index] = seg[2 * index + 1] + seg[2 * index + 2];
    }

    void update(int index, int low, int high, int i, int val) {
        if (low == high) {
            seg[index] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid) {
            update(2 * index + 1, low, mid, i, val);
        } else {
            update(2 * index + 2, mid + 1, high, i, val);
        }
        seg[index] = seg[2 * index + 1] + seg[2 * index + 2];
    }

    int query(int index, int low, int high, int l, int r) {
        // no overlapping
        if (high < l or r < low) {
            return 0;
        }
        // complete overlapping
        if (l <= low and high <= r) {
            return seg[index];
        }
        // partial overlapping
        int mid = (low + high) / 2;
        int left = query(2 * index + 1, low, mid, l, r);
        int right = query(2 * index + 2, mid + 1, high, l, r);
        return left + right;
    }
};

class NumArray {
public:
    SegmentTree st;
    int N;
    NumArray(vector<int> &nums) {
        N = nums.size();
        st.setSize(N);
        st.build(0, nums, 0, N - 1);
    }

    void update(int index, int val) {
        st.update(0, 0, N - 1, index, val);
    }

    int sumRange(int left, int right) {
        return st.query(0, 0, N - 1, left, right);
    }
};