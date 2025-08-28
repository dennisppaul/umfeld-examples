# note

Since this category of the processing examples seem to demonstrate the use of the language(java), I write this note to remark the difference between the languages. Decision is required in long term, on how interpret the level of the examples(how much depth of the language you want to show) as well as the key-take of the difference between processing and umfeld.



## conditionals(if)


conditional in java and c++ are almost identical, except roughly two thinks afaik.

1. java allows only `boolean`, but cpp allows arithmetic types(int, float etc.) as well as pointers.


2. Below is legal in cpp>=c++17, but not possible in java(afaik)


```cpp
if (int n = computeValue(); n > 0) { 
    // n is legal inside this scope
}else{
    // n is legal inside this scope as well
}
```

which is often cleaner and safer for variable life cycle management.



## iteration(for)

iteration, too, is almost identical in both language, when speaking of syntax.

1. In java, type of the iterator variable must always be an integer type(byte, short, int etc.) or char, whereas c++ is more permissive(but you gotta handle it if using eg. pointer)


2. `for-each` vs `auto`: in java, the iteration with `for-each` provides a copy of the element, where as the `auto` in cpp>=c++11 can be used with the reference op `auto&`, allowing to modify the element directly.

## logical operators(boolean ops)

this also seems identical, but the `!` (logical NOT) in c++ is more permissive, whereas, in java, it works only with `boolean`.