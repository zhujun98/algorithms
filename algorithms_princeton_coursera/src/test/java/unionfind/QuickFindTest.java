package unionfind;

import org.junit.jupiter.api.Test;

public class QuickFindTest {
    @Test
    void unionFind() {
        QuickFind uf = new QuickFind(10);
        uf.union(1, 2);
        uf.union(2, 3);
        assert(uf.connected(1, 2));
        assert(!uf.connected(1, 4));
    }
}
