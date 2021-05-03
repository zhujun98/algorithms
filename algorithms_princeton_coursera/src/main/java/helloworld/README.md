# Test Code for Absolute Beginners

## Prerequisite

Download the `algs4.jar` file and put it in `<project folder>/libs

## Compile and run manually

```sh
# To run the compiled file, you must be in this folder!
cd <project folder>/src/main/java
```

Test 1:

```sh
javac helloworld/HelloWorld.java
java helloworld.HelloWorld
# Output:
# Hello, World
```

Test 2:

```sh
javac helloworld/HelloGoodbye.java
java helloworld.HelloGoodbye Tom Jerry
# Output:
# Hello Tom and Jerry
# Goodbye Jerry and Tom
```

Test 3:

```sh
javac -cp ../../../module/algs4.jar RandomWord.java
java -cp ../../../module/algs4.jar:./ RandomWord
# Input (ctrl + D to finish):
# a b c d
# Output (random pickup of the input string):
# b
```

## Use Maven

### Install the dependency locally

```sh
cd <project folder>
mvn install:install-file -Dfile=./libs/algs4.jar -DgroupId=edu.princeton.cs -DartifactId=algs4 -Dversion=1.0.4 -Dpackaging=jar
```

And add the dependency in the `pom.xml`
```xml
        <dependency>
            <groupId>edu.princeton.cs</groupId>
            <artifactId>algs4</artifactId>
            <version>1.0.4</version>
        </dependency>
```

For `IntelliJ`, you will need to `Reload Project` to make the newly install 
dependency visiable.

### Adding directly the dependency as system scope

```xml
<dependency>
    <groupId>edu.princeton.cs</groupId>
    <artifactId>algs4</artifactId>
    <version>1.0.4</version>
    <scope>system</scope>
    <systemPath>${basedir}/libs/algs4.jar</systemPath>
</dependency>
```