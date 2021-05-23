package datastructure;

import org.junit.jupiter.api.Test;

public class StackTest {
    @Test
    void linkedListStack() {
        LinkedListStack<Integer> st = new LinkedListStack<Integer>();

        assert(st.isEmpty());
        st.push(1);
        st.push(4);
        assert(!st.isEmpty());
        assert(st.pop() == 4);
        assert(st.pop() == 1);
    }
}
