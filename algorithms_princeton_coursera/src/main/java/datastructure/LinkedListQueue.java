package datastructure;

public class LinkedListQueue<T> {
    private Node first, last;

    private class Node {
        T v;
        Node next;

        Node (T v_) {
            v = v_;
            next = null;
        }
    }

    void enqueue(T v) {
        Node oldLast = last;
        last = new Node(v);
        if (first == null) {
            first = last;
        } else {
            oldLast.next = last;
        }

    }

    T dequeue() {
        if (isEmpty()) {
            return null;
        }
        T v = first.v;
        first = first.next;
        if (isEmpty()) {
            last = first;
        }
        return v;
    }

    boolean isEmpty() {
        return first == null;
    }
}
