package datastructure;

import org.junit.jupiter.api.Test;

public class QueueTest {
    @Test
    void linkedListQueue() {
        LinkedListQueue<String> q = new LinkedListQueue<String>();

        assert(q.isEmpty());
        q.enqueue("abc");
        q.enqueue("efg");
        assert("abc".equals(q.dequeue()));
        assert("efg".equals(q.dequeue()));
        assert(q.isEmpty());
        assert(null == q.dequeue());
    }
}
