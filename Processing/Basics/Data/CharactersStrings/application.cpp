/**
 * Characters Strings. 
 *  
 * The character datatype, abbreviated as char, stores letters and 
 * symbols in the Unicode format, a coding system developed to support 
 * a variety of world languages. Characters are distinguished from other
 * symbols by putting them between single quotes ('P').
 * 
 * A string is a sequence of characters. A string is noted by surrounding 
 * a group of letters with double quotes ("Processing"). 
 * Chars and strings are most often used with the keyboard methods, 
 * to display text to the screen, and to load images or files.
 * 
 * The String datatype must be capitalized because it is a complex datatype.
 * A String is actually a class with its own methods, some of which are
 * featured below. 
 */

#include "Umfeld.h"

using namespace umfeld;

char letter;
std::string words = "Begin..."; //@diff(generic_type)

void settings() {
    size(640, 360);
}

void setup() {
    PFont* font = nullptr;
    // Load the font from the file
    font = loadFont("SourceCodePro-Regular.ttf", 36); // @diff(font_load)
    // Create the font
    textFont(font);
}

void draw() {
    background(0.f); // Set background to black

    // Draw the letter to the center of the screen
    textSize(14);
    text("Click on the program, then type to add to the String", 50, 50);
    text("Current key: " + letter, 50, 70);
    text("The String is " + std::to_string(words.length()) + " characters long", 50, 90); //@diff(text, type_conversion)

    textSize(36);
    text(words, 50, 120); //@diff(text)
}

// FIXME: keyTyped() has no response(6.15.8-arch1-1)
void keyTyped() {
    // The variable "key" always contains the value
    // of the most recent key pressed.
    if ((key >= 'A' && key <= 'z') || key == ' ') {
        letter = key;
        words  = words + (char)key; //@diff(type_casting,generic_type)
        // Write the letter to the console
        println(key);
    }
    println(key);
}