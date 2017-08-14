#include "automata.h"
#include "prng_automata.h"
#include <vector>
#include <random>
#include <iostream>
#include <array>
#include <stack>
#define FROM_INPUT_STRING false

using namespace std;

void createSymbolArray(uint32_t length, vector<unsigned char> &randomChars) 
{
  
    //randomChars.resize(length);
    for(uint32_t i = 0; i < length; i++) {
        randomChars.push_back( (unsigned char)i);
    }

}

void randomizeSymbolArray(uint32_t numSymbols, vector<unsigned char> &orderedArray) {

    vector<unsigned char> temp;
    for(unsigned char c : orderedArray) {
        temp.push_back(c);
    }

    for(uint32_t i = 0; i < numSymbols; i++) {
        uint32_t randIndex = ((uint32_t)rand()) % temp.size();
        orderedArray[i] = temp[randIndex];
        if(orderedArray[i] > 255)
            cout << "WRONG!!!: " << i << endl;
        temp.erase(temp.begin() + randIndex);
    }
}

int main(int argc, char * argv[]) {
  
    cout << "Starting Main..." <<endl;

    uint32_t numStates = 2;
    uint32_t numSymbols = 256;

    Automata ap;

    // For each Markove chain "star" state
    for(int startState = 0; startState < numStates; startState++) {

        // Generate reporting "star" state STE
        string starId = "S_" + startState;
        STE * ste = new STE(starId, "*", "none");
        ap.rawAddSTE(ste);
        
        //
        vector<unsigned char> alphArray;
        vector<vector<unsigned char>> symbolSetArray;

        // create contiguous symbols in array
        vector<unsigned char> randoms;
        createSymbolArray(numSymbols, randoms);
        randomizeSymbolArray(numSymbols, randoms);

        // Generate transition STEs
        for(int transitionState = 0; transitionState < numStates; transitionState++) {

            // T_#_#"
            string id = "T_" + to_string(startState) + "_" + to_string(transitionState);
            STE * ste = new STE(id, "[]", "none");

            // Add symbols to STE
            uint32_t offset = numSymbols/numStates;
            uint32_t startIndex = offset * transitionState;
            for(uint32_t index = startIndex; index < startIndex + offset; index++) {
                ste->addSymbolToSymbolSet(randoms[index]);
            }

            // Add STE to automata
            ap.rawAddSTE(ste);
        }
   
    }

    ap.automataToANMLFile("markov.anml");
}


