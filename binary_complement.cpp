#include <fst/fstlib.h>
#include <iostream>
#include <string>

using namespace fst;

int main() {
    std::string input;
    std::cout << "Enter a binary string: ";
    std::getline(std::cin, input);

    StdVectorFst fst;
    int start = fst.AddState();
    fst.SetStart(start);
    int current = start;

    for (char c : input) {
        int next = fst.AddState();
        if (c == '0') {
            fst.AddArc(current, StdArc('0', '1', TropicalWeight::One(), next));
        } else if (c == '1') {
            fst.AddArc(current, StdArc('1', '0', TropicalWeight::One(), next));
        } else {
            std::cerr << "Invalid character: " << c << std::endl;
            return 1;
        }
        current = next;
    }

    fst.SetFinal(current, TropicalWeight::One());

    std::string output;
    for (StateIterator<StdVectorFst> siter(fst); !siter.Done(); siter.Next()) {
        int state = siter.Value();
        for (ArcIterator<StdVectorFst> aiter(fst, state); !aiter.Done(); aiter.Next()) {
            const StdArc &arc = aiter.Value();
            output += char(arc.olabel);
        }
    }

    std::cout << "Binary complement: " << output << std::endl;
}

