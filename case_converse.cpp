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

 
    for (char c = 'a'; c <= 'z'; ++c) {
        char upper = c - 'a' + 'A';
        fst.AddArc(start, StdArc(c, upper, TropicalWeight::One(), accept));
    }

  
    for (char c = 'A'; c <= 'Z'; ++c) {
        fst.AddArc(start, StdArc(c, c, TropicalWeight::One(), accept));
    }
    for (char c = '0'; c <= '9'; ++c) {
        fst.AddArc(start, StdArc(c, c, TropicalWeight::One(), accept));
    }
    fst.AddArc(start, StdArc(' ', ' ', TropicalWeight::One(), accept));

   
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
            
            output.push_back(c);
        }
    }

    
    std::cout << "Converted string: " << output << std::endl;

    return 0;
}

