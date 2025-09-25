#include <fst/fstlib.h>
#include <iostream>
#include <string>

using namespace fst;

int main() {
    StdVectorFst fst;

    
    int start = fst.AddState();
    fst.SetStart(start);
    int accept = fst.AddState();
    fst.SetFinal(accept, TropicalWeight::One());

   
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghjklmnpqrstvwxyz";

    
    for (char c : vowels) {
        fst.AddArc(start, StdArc(c, 'V', TropicalWeight::One(), accept));
    }

    
    for (char c : consonants) {
        fst.AddArc(start, StdArc(c, 'C', TropicalWeight::One(), accept));
    }

    
    for (char c : vowels) {
        fst.AddArc(start, StdArc(toupper(c), 'V', TropicalWeight::One(), accept));
    }
    for (char c : consonants) {
        fst.AddArc(start, StdArc(toupper(c), 'C', TropicalWeight::One(), accept));
    }

    
    for (char c = 32; c < 127; ++c) {
        if (vowels.find(tolower(c)) == std::string::npos &&
            consonants.find(tolower(c)) == std::string::npos) {
            fst.AddArc(start, StdArc(c, c, TropicalWeight::One(), accept));
        }
    }

    
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    
    std::string output;
    for (char c : input) {
        bool matched = false;
        for (ArcIterator<StdVectorFst> aiter(fst, start); !aiter.Done(); aiter.Next()) {
            const StdArc &arc = aiter.Value();
            if (arc.ilabel == c) {
                output.push_back(static_cast<char>(arc.olabel));
                matched = true;
                break;
            }
        }
        if (!matched) {
            
            output.push_back('?');
        }
    }

    std::cout << "Output: " << output << std::endl;

    return 0;
}

