/**
 * Datatype Conversion. 
 * 
 * It is sometimes beneficial to convert a value from one type of 
 * data to another. Each of the conversion functions converts its parameter 
 * to an equivalent representation within its datatype. 
 * The conversion functions include int(), float(), char(), int8_t() and others. 
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    noStroke();
    PFont* font = loadFont("SourceCodePro-Regular.ttf", 24); //@diff(load_font)
    textFont(font);
}

void draw() {

    char   c = 'A'; // Char for alphanumeric symbols
    float  f;       // Float for decimal numbers
    int    i;       // Integer for whole numbers
    int8_t b;       // 8-bit signed integer (-128 to 127)


    f = static_cast<float>(c);      // Convert char to float (ASCII value of 'A' is 65)
    i = static_cast<int>(f * 1.4f); // Multiply float by 1.4 and convert to int
    b = static_cast<int8_t>(c / 2); // Divide char's ASCII value by 2 and convert to int8_t

    println(f);
    println(i);
    println(b);


    text(std::string("The value of variable c is ") + c, 50, 100);
    text("The value of variable f is " + std::to_string(f), 50, 150);
    text("The value of variable i is " + std::to_string(i), 50, 200);
    
    std::stringstream ss;
    ss << "The value of variable b is " << static_cast<int>(b);
    text(ss.str(), 50, 250);
}
