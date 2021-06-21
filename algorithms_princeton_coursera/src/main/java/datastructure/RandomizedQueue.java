package datastructure;

import java.util.Iterator;

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private int count;
    private Item[] data;

    private class RandomizedQueueIterator implements Iterator<Item> {

        private Item[] randomQueue;
        private int current;

        public RandomizedQueueIterator(RandomizedQueue<Item> queue) {
            randomQueue = (Item[]) new Object[count];
            current = 0;
            System.arraycopy(data, 0, randomQueue, 0, count);
            StdRandom.shuffle(randomQueue);
        }

        public boolean hasNext() {
            return current < randomQueue.length;
        }

        public Item next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }
            return randomQueue[current++];
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    // construct an empty randomized queue
    public RandomizedQueue() {
        count = 0;
        data = (Item[]) new Object[1];
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return count == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return count;
    }

    private void resize(int size) {
        Item[] temp = (Item[]) new Object[size];
        for (int i = 0; i < count; ++i) {
            temp[i] = data[i];
        }
        data = temp;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }
        if (count == data.length) resize(2 * count);
        data[count++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        int index = StdRandom.uniform(count);
        Item item = data[index];

        // "Move" the dequeued slot to the end of the array.
        data[index] = data[count-1];
        data[count-1] = null;
        count--;

        if (count > 0 && count == data.length / 4) {
            resize(data.length / 2);
        }

        return item;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        int index = StdRandom.uniform(count);
        return data[index];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator(this);
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> queue = new RandomizedQueue<Integer>();

        StdOut.println("Constructed an empty deque");
        assert queue.isEmpty();

        for (int i = 0; i < 10; ++i) {
            queue.enqueue(i);
        }
        StdOut.println("Added 10 elements to the deque.");
        assert queue.size() == 10;

        for (Integer i : queue) {
            StdOut.println(i);
        }
        StdOut.println("Iterated over the deque.");

        for (int i = 0; i < 10; ++i) {
            Integer item = queue.dequeue();
            StdOut.println("Dequeue element: " + item);
        }
        StdOut.println("Removed all elements in the deque.");
        assert queue.isEmpty();
    }

}
