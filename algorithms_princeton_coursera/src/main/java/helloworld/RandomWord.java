package helloworld;

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdRandom;


public class RandomWord {
    public static void main(String[] args) {
        String selected=StdIn.readString();
        int i = 1;
        while (!StdIn.isEmpty())
        {
            ++i;
            String current_string = StdIn.readString();
            double p = 1. / i;
            if (StdRandom.bernoulli(p)) {
                selected = current_string;
            }
        }
        System.out.println(selected);
    }
}
