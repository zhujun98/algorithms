package unionfind;

public class UnionFind extends WeightedQuickUnion {
    public UnionFind(int N) {
        super(N);
    }

    private int root(int i) {
        while (i != id[i]) {
            id[i] = id[id[i]]; // path compaction
            i = id[i];
        }
        return i;
    }
}
