package unionfind;

public class WeightedQuickUnion {
    protected int[] id;
    protected int[] sz;

    public WeightedQuickUnion(int N) {
        id = new int[N];
        sz = new int[N];
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    private int root(int i) {
        while (i != id[i]) i = id[i];
        return i;
    }

    // Time complexity O(N) worst case
    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }

    // Time complexity O(logN)
    public void union(int p, int q) {
        int i = root(p);
        int j = root(q);
        if (i == j) return;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
}
