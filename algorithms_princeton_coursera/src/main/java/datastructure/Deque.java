package datastructure;

import java.util.Iterator;

import edu.princeton.cs.algs4.StdOut;

public class Deque<Item> implements Iterable<Item> {

    private Node first;
    private Node last;
    private int count;

    private class Node {
        Item item;
        Node next;
        Node prev;

        Node(Item item) {
            this.item = item;
            next = null;
            prev = null;
        }
    }

    private class DequeIterator implements Iterator<Item> {
        private Node current;

        public DequeIterator(Deque<Item> deque) {
            current = deque.first;
        }

        public boolean hasNext() {
            return current != null;
        }

        public Item next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }
            Item item = current.item;
            current = current.next;
            return item;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public Deque() {
        first = null;
        last = null;
        count = 0;
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public int size() {
        return count;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }
        Node oldFirst = first;
        first = new Node(item);
        first.next = oldFirst;
        if (oldFirst == null) {
            last = first;
        } else {
            oldFirst.prev = first;
        }
        count++;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }
        Node oldLast = last;
        last = new Node(item);
        last.prev = oldLast;
        if (oldLast == null) {
            first = last;
        } else {
            oldLast.next = last;
        }
        count++;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        Item item = first.item;
        first = first.next;
        if (first == null) {
            last = null;
        } else {
            first.prev = null;
        }
        count--;
        return item;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        Item item = last.item;
        last = last.prev;
        if (last == null) {
            first = null;
        } else {
            last.next = null;
        }
        count--;
        return item;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new DequeIterator(this);
    }

    // unit testing (required)
    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<Integer>();

        StdOut.println("Constructed an empty deque");
        assert deque.isEmpty();

        for (int i = 0; i < 5; i++) {
            deque.addFirst(i);
            deque.addLast(i + 10);
        }
        StdOut.println("Added 10 elements to the deque.");
        assert deque.size() == 10;

        for (Integer i : deque) {
            StdOut.println(i);
        }
        StdOut.println("Iterated over the deque.");

        for (int i = 4; i >=0; i--) {
            Integer item = deque.removeLast();
            assert i + 10 == item;
            item = deque.removeFirst();
            assert i == item;
        }
        StdOut.println("Removed all elements in the deque.");
        assert deque.isEmpty();
    }

}
