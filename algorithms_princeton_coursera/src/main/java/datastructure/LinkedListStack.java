package datastructure;

public class LinkedListStack<T> {
    private Node first = null;

    private class Node {
        T v;
        Node next;
    }

    public boolean isEmpty() {
        return first == null;
    }

    public void push(T item) {
        Node prev = first;
        first = new Node();
        first.v = item;
        first.next = prev;
    }

    public T pop() {
        T item = first.v;
        first = first.next;
        return item;
    }
}
