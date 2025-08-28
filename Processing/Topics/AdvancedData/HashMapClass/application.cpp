/**
 *
 * This example demonstrates how to use a hash-map based std::unordered_map to store
 * a collection of objects referenced by a key. This is much like an array,
 * only instead of accessing elements with a numeric index, we use a String.
 * If you are familiar with associative arrays from other languages,
 * this is the same idea.
 *
 * A similar example is CountingStrings which uses std::map instead of
 * std::unordered_map. The Processing counterpart of the std::unordered_map is HashMap, in the sense that it is based on a hash table internally.
 * See: https://en.wikipedia.org/wiki/Unordered_associative_containers_(C%2B%2B)
 * 
 * In this example, words that appear in one book (Dracula) only are colored white 
 * while words the other (Frankenstein) are colored black.
 */
#include "Umfeld.h"
#include "Word.h"

using namespace umfeld;

std::unordered_map<std::string, Word> words; // unordered_map object

void loadFile(std::string filename); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    // Create the unordered_map
    words = std::unordered_map<std::string, Word>();

    // Load two files
    loadFile("dracula.txt");
    loadFile("frankenstein.txt");
    
    std::cout << "Total words loaded: " << words.size() << std::endl;
    
    int qualifyingWords = 0;
    for (auto& pair : words) {
        if (pair.second.qualify()) {
            qualifyingWords++;
        }
    }
    std::cout << "Qualifying words: " << qualifyingWords << std::endl;
    
    // Create the font
    textFont(loadFont("SourceCodePro-Regular.ttf", 24)); //@diff(createFont)
}

void draw() {
    background(.5f); //@diff(color_range)

    // Show words
    for (auto& pair: words) { //@diff(for_loop,std::unordered_map)
        Word& w = pair.second;
        if (w.qualify()) {
            w.display();
            w.move();
        }
    }
}

// Load a file
void loadFile(std::string filename) {
    std::vector<std::string> lines = loadStrings(filename); //diff(std::vector)
    std::string allText = join(lines, " ");
    std::transform(allText.begin(), allText.end(), allText.begin(), ::tolower); //@diff(tolowercase)
    std::vector<std::string> tokens = splitTokens(allText, " ,.?!:;[]-\"'");

    for (const std::string& s: tokens) {
        // Is the word in the std::unordered_map?
        if (words.count(s)) { //@diff(std::unordered_map)
            // Get the word object and increase the count
            // We access objects from a std::unordered_map via its key, the String
            Word& w = words[s]; //@diff(std::unordered_map)
            // Which book am I loading?
            if (filename.find("dracula") != std::string::npos) { //@diff(std::string)
                w.incrementDracula();
            } else if (filename.find("frankenstein") != std::string::npos) { //@diff(std::string)
                w.incrementFranken();
            }
        } else {
            // Otherwise make a new word
            Word w(s);
            // And add to the std::unordered_map using the assignment operator(=)
            // The key for us is the std::string and the value is the Word object
            words[s] = w; //@diff(std::unordered_map)
            if (filename.find("dracula") != std::string::npos) { //@diff(std::string)
                w.incrementDracula();
            } else if (filename.find("frankenstein") != std::string::npos) { //@diff(std::string)
                w.incrementFranken();
            }
        }
    }
}