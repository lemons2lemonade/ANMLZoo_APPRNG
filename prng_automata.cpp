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

int main(int argc, char* argv[]) {
  
  cout << "Starting Main..." <<endl;

  uint32_t numSymbols = 256; //Alphabet Size


  //Command line arguments
  int numStates = atoi(argv[1]); //let user set num of states
  int numMCs = atoi(argv[2]); //let user set num MCs
  static_cast<uint32_t>(numStates);
  static_cast<uint32_t>(numMCs);
  
  uint32_t mcId = 0;

  Automata ap;

  //generate all reporting nodes beforehand so that they exist
  // when referenced for edge creating in the double-for loop
  for (uint32_t j=0; j < numMCs; j++){
    for (uint32_t k = 0; k < numStates; k++){
      string starId = "S_" + to_string(k) + "_MC_"+to_string(mcId);
      if (j == 0 && k == 0){
	STE * ste = new STE(starId,"*","start-of-data");
	ap.rawAddSTE(ste);
	ste->setReporting(true);
      }

      else{
	STE * ste = new STE(starId, "*", "none");
	ap.rawAddSTE(ste);
	ste->setReporting(true);
      }
      cout << "Node ID Created: " << starId << endl;
    }
    mcId++;
  }
    
  //For each Markov Chain Set
  for(uint32_t a=0; a < numMCs; a++){
      
    // For each Markov chain "star" state
    for(uint32_t startState = 0; startState < numStates; startState++) {

      string starNodeId = "S_" + to_string(startState) + "_MC_"+to_string(a);
      //
      vector<unsigned char> alphArray;
      vector<vector<unsigned char>> symbolSetArray;

      // create contiguous symbols in array
      vector<unsigned char> randoms;
      createSymbolArray(numSymbols, randoms);
      randomizeSymbolArray(numSymbols, randoms);
	
      // Generate transition STEs
      for(uint32_t transitionState = 0; transitionState < numStates; transitionState++) {

	// T_#_#"
	string pathId = "T_" + to_string(startState) + "_" + to_string(transitionState) + "_MC_"+to_string(a);
	STE * ste = new STE(pathId, "[]", "none");
	    
	// Add symbols to STE
	uint32_t offset = numSymbols/numStates;
	uint32_t startIndex = offset * transitionState;
	for(uint32_t index = startIndex; index < startIndex + offset; index++) {
	  ste->addSymbolToSymbolSet(randoms[index]);
	}
	  
	// Add STE to automata
	ap.rawAddSTE(ste);

	//Add outgoing edge paths
	string pathToOtherNode = "S_"+to_string(transitionState) + "_MC_"+to_string(a);
	//cout <<"Node ID Referenced: " <<pathToOtherNode << endl;
	cout << "MC: "+to_string(a)+ " , Path: "+ pathId + " -> "+pathToOtherNode << endl;
	ap.addEdge(ap.getElement(starNodeId), ap.getElement(pathId));
	ap.addEdge(ap.getElement(pathId), ap.getElement(pathToOtherNode));

      }
   
    }

  }
  ap.automataToANMLFile("markov.anml");
}


