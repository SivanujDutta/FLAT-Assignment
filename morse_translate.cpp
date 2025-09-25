#include <fst/fstlib.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace fst;

int main() {
    std::unordered_map<char, std::string> morse = {
        {'A',".-"}, {'B',"-..."}, {'C',"-.-."}, {'D',"-.."}, {'E',"."}, {'F',"..-."},
        {'G',"--."}, {'H',"...."}, {'I',".."}, {'J',".---"}, {'K',"-.-"}, {'L',".-.."},
        {'M',"--"}, {'N',"-."}, {'O',"---"}, {'P',".--."}, {'Q',"--.-"}, {'R',".-."},
        {'S',"..."} , {'T',"-"}, {'U',"..-"}, {'V',"...-"}, {'W',".--"}, {'X',"-..-"},
        {'Y',"-.--"}, {'Z',"--.."}, {'0',"-----"}, {'1',".----"}, {'2',"..---"}, {'3',"...--"},
        {'4',"....-"}, {'5',"....."}, {'6',"-...."}, {'7',"--..."}, {'8',"---.."}, {'9',"----."},
        {' ', "/"}
    };

    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);

    StdVectorFst fst;
    int start = fst.AddState();
    fst.SetStart(start);
    int current = start;

    for (char c : text) {
        auto it = morse.find(c);
        if (it == morse.end()) continue;

        const std::string &code = it->second;
        int prev = current;
        for (char mc : code) {
            int next = fst.AddState();
            int out_label = fst.AddState(); // just needs unique number
            fst.AddArc(prev, StdArc(mc, mc, TropicalWeight::One(), next));
            prev = next;
        }
        current = prev;
        // add space between letters
        int space_state = fst.AddState();
        fst.AddArc(current, StdArc(' ', ' ', TropicalWeight::One(), space_state));
        current = space_state;
    }
    fst.SetFinal(current, TropicalWeight::One());

    // extract output
    std::string morse_output;
    for (StateIterator<StdVectorFst> siter(fst); !siter.Done(); siter.Next()) {
        int state = siter.Value();
        for (ArcIterator<StdVectorFst> aiter(fst, state); !aiter.Done(); aiter.Next()) {
            const StdArc &arc = aiter.Value();
            morse_output += char(arc.olabel);
        }
    }

    std::cout << "Morse code: " << morse_output << std::endl;
}

