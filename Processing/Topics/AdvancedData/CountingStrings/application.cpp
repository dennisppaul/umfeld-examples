/**
 * 
 * This example demonstrates how to use the std::map to store 
 * a number associated with a String. The Processing(Java) counterpart
 * of this example uses IntDict, a class that is part of the Processing core.
 * But in this C++ version, we use the std::map from the C++ STL
 * to achieve the same functionality.
 *
 * This example uses the IntDict to perform a simple concordance
 * http://en.wikipedia.org/wiki/Concordance_(publishing)
 *
 */

#include "Umfeld.h"
#include <algorithm>

using namespace umfeld;

// An IntDict pairs Strings with integers
std::map<std::string, int> concordance; //@diff(std::map)

// The raw array of words in
std::vector<std::string> tokens; //@diff(std::vector)
int counter = 0;


void settings() {
    size(640, 360);
}

void setup() {
    // Load file and chop it up
    std::vector<std::string> lines = loadStrings("dracula.txt");
    std::string allText = join(lines, " ");
    std::transform(allText.begin(), allText.end(), allText.begin(), [](unsigned char c){ return std::tolower(c); }); //@diff(tolower)
    tokens = splitTokens(allText, " ,.?!:;[]-\"");

    // Create the font
    textFont(loadFont("SourceCodePro-Regular.ttf", 24)); //@diff(createFont)
}

void draw() {
    background(.2f); //@diff(color_range)
    fill(1.f); //@diff(color_range)

    // Look at words one at a time
    if (counter < tokens.size()) { //@diff(std::vector)
        std::string s = tokens[counter]; //@diff(std::string)
        counter++;
        concordance[s]++;
    }

    // x and y will be used to locate each word
    float x = 0;
    float y = 48;

    // sort by values in ascending order
    // in c++ we can use std::sort with a custom comparator
    // to sort the map by its values
    // note that the std::map is sorted by keys by default, so we need to create
    // a vector of pairs to sort by values
    // This is a custom sort lambda function that sorts the map by its values
    //@diff(std::map,std::sort)
    std::vector<std::pair<std::string, int>> sortedConcordance(concordance.begin(), concordance.end());
    std::sort(sortedConcordance.begin(), sortedConcordance.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second < b.second;
              });

    // Create a vector of keys from the sorted map
    std::vector<std::string> keys;
    for (const auto& pair : sortedConcordance) {
        keys.push_back(pair.first);
    }

    // Look at each word
    for (std::string word: keys) {
        int count = concordance[word]; //@diff(std::map)

        // Only display words that appear 3 times
        if (count > 3) {
            // The size is the count
            int fsize = constrain(count, 0, 48);
            textSize(fsize);
            text(word, x, y);
            // Move along the x-axis
            x += textWidth(word + " ");
        }

        // If x gets to the end, move y
        if (x > width) {
            x = 0;
            y += 48;
            // If y gets to the end, we're done
            if (y > height) {
                break;
            }
        }
    }
}