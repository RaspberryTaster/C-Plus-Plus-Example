
#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H
#include <map>
#include <string>
#include <tuple>
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace AnsiColors {
    const string RESET   = "\033[0m";
    const string BLACK   = "\033[30m"; 
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
    const string WHITE   = "\033[37m";

    map<string, tuple<int, int, int>> ansiToRgb = {
        {BLACK,   make_tuple(0, 0, 0)},
        {RED,     make_tuple(255, 0, 0)},
        {GREEN,   make_tuple(0, 255, 0)},
        {YELLOW,  make_tuple(255, 255, 0)},
        {BLUE,    make_tuple(0, 0, 255)},
        {MAGENTA, make_tuple(255, 0, 255)},
        {CYAN,    make_tuple(0, 255, 255)},
        {WHITE,   make_tuple(255, 255, 255)}
    };


    tuple<int, int, int> getRgb(string ansi, float saturation)
    {
        if (ansiToRgb.count(ansi))
        {
            return ansiToRgb[ansi];
        }
        else
        {
            vector<string> splitted;
            string s;
            istringstream ss(ansi);
            while (getline(ss, s, ';')) {
                splitted.push_back(s);
            }
            int r = int(stoi(splitted[2]));
            int g = int(stoi(splitted[3]));
            size_t nonNumeric = splitted[4].find_first_not_of("0123456789");
            if (nonNumeric != std::string::npos) {
                splitted[4] = splitted[4].substr(0, nonNumeric);
            }
            int b = int(stoi(splitted[4]));
            r *= saturation;
            g *= saturation;
            b *= saturation;
            
            return make_tuple(r,g,b);          
        }
        __throw_runtime_error("No Color Found");  
        return make_tuple(-1, -1, -1);   
    }
    
    tuple<int, int, int> getRgb(string ansi)
    {
        if (ansiToRgb.count(ansi))
        {
            return ansiToRgb[ansi];
        }
        else
        {
            vector<string> splitted;
            string s;
            istringstream ss(ansi);
            while (getline(ss, s, ';')) {
                splitted.push_back(s);
            }
            int r = int(stoi(splitted[2]));
            int g = int(stoi(splitted[3]));
            size_t nonNumeric = splitted[4].find_first_not_of("0123456789");
            if (nonNumeric != std::string::npos) {
                splitted[4] = splitted[4].substr(0, nonNumeric);
            }
            int b = int(stoi(splitted[4]));
            return make_tuple(r,g,b);          
        }
        __throw_runtime_error("No Color Found");  
        return make_tuple(-1, -1, -1);   
    }
    
    string getAnsiColor(tuple<int, int, int> color)
    {
        int r, g, b;

        tie(r,g,b) = color;

        return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";        
    }   
    //could benefit from a saturation value, basically dividing the all color values by a different value
    // x/255 which would normalize to 0 to 1
    //perhaps in next iteration.
    string getAnsiColor(int r,int g, int b)
    {
        return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";        
    }
    tuple<int, int, int> lerp(tuple<int, int, int> color1, tuple<int, int, int> color2, float t) {

        t = clamp(t, 0.0f, 1.0f);

        int r1, g1, b1;
        int r2, g2, b2;

        tie(r1, g1, b1) = color1;
        tie(r2, g2, b2) = color2;

        int r = static_cast<int>(r1 + t * (r2 - r1));
        int g = static_cast<int>(g1 + t * (g2 - g1));
        int b = static_cast<int>(b1 + t * (b2 - b1));

        return make_tuple(r, g, b);
    }

    string getAnsiLerp(string a, string b, float t)
    {
        tuple<int, int, int> color1 = getRgb(a);
        tuple<int, int, int> color2 = getRgb(b);
        return getAnsiColor(lerp(color1, color2,t));
    }

    string getAnsiLerp(tuple<int, int, int> color1, tuple<int, int, int> color2, float t)
    {
        return getAnsiColor(lerp(color1, color2,t));
    }

    void printWithGradient(string text, tuple<int, int, int> colorA, tuple<int, int, int> colorB) {
        for (int i = 0; i < text.length(); ++i) {
            float t = static_cast<float>(i) / text.length();
            auto [r, g, b] = lerp(colorA, colorB, t);
            string colorCode = getAnsiColor(r, g, b);
            cout << colorCode << text[i];
        }
        cout << RESET; 
    }
}

#endif 
