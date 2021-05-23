package unionfind;

import org.junit.jupiter.api.Test;

public class UnionFindTest {
    @Test
    void quickFind() {
        QuickFind uf = new QuickFind(10);
        uf.union(1, 2);
        uf.union(2, 3);
        assert(uf.connected(1, 2));
        assert(!uf.connected(1, 4));
    }

    @Test
    void quickUnion() {
        QuickUnion uf = new QuickUnion(10);
        uf.union(1, 2);
        uf.union(2, 3);
        assert(uf.connected(1, 2));
        assert(!uf.connected(1, 4));
    }

    @Test
    void weightedQuickUnion() {
        WeightedQuickUnion uf = new WeightedQuickUnion(10);
        uf.union(1, 2);
        uf.union(2, 3);
        assert(uf.connected(1, 2));
        assert(!uf.connected(1, 4));
    }
}
