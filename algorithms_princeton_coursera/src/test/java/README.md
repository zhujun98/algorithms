# Test Code for Absolute Beginners

Test 1:

```sh
javac HelloWorld.java
java Helloworld
# Output:
# Hello, World
```

Test 2:

```sh
javac HelloGoodbye.java
java HelloGoodbye Tom Jerry
# Output:
# Hello Tom and Jerry
# Goodbye Jerry and Tom
```

Test 3:

```sh
javac -cp ../../../module/algs4.jar RandomWord.java
java -cp ../../../module/algs4.jar:. RandomWord
# Input (ctrl + D to finish):
# a b c d
# Output (random pickup of the input string):
# b
```