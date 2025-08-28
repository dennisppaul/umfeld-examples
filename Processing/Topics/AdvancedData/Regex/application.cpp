/**
 * Regular Expression example
 * by Daniel Shiffman.  
 * 
 * This example demonstrates how to use matchAll() to create
 * a list of all matches of a given regex.
 *
 * Here we'll load the raw HTML from a URL and search for any
 * <a href=" "> links
 */
#include "Umfeld.h"

using namespace umfeld;

// Our source url
std::string url = "https://github.com/dennisppaul/umfeld";
// We'll store the results in a vector
std::vector<std::string> links;

std::vector<std::string> loadLinks(std::string s); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    // Load the links
    links = loadLinks(url);

    // load a font
    PFont* font = loadFont("SourceCodePro-Regular.ttf", 12.f); //@diff(font)
    textFont(font);
}

void draw() {
    background(0.f); //@diff(color_range)
    // Display the raw links
    fill(1.f); //@diff(color_range)
    noStroke();
    for (int i = 0; i < links.size(); i++) {
        text(links[i], 10, 16 + i * 16);
    }
}

std::vector<std::string> loadLinks(std::string s) {
    // Load the raw HTML
    std::vector<std::string> lines = loadStrings(s);
    // Put it in one big string
    std::string html = join(lines, "\n");

    // A wacky regex for matching a URL
    std::string regexStr = "<\\s*a\\s+href\\s*=\\s*\"(.*?)\"";
    std::regex regex(regexStr); //@diff(regex)
    // The matches are in a two dimensional array
    // The first dimension is all matches
    // The second dimension is the groups
    std::vector<std::vector<std::string>> matches = matchAll(html, regex);

    // A vector for the results
    std::vector<std::string> results(matches.size());

    // We want group 1 for each result
    for (int i = 0; i < results.size(); i++) {
        results[i] = matches[i][1];
    }

    // Return the results
    return results;
}
