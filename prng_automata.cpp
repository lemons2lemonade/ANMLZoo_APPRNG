#include "automata.h"
#include "prng_automata.h"
#include <vector>
#include <random>
#include <iostream>
#include <array>
#include <stack>
#define FROM_INPUT_STRING false

using namespace std;

vector<char> createSymbolArray(uint32_t length) 
{
  
  vector<char> randomChars;
  randomChars.resize(length);
    for(int i = 0; i < length; i++) {
      randomChars[i] = (char)i;
    }

    return randomChars;
}


vector<vector<char>> alphDivider(int numStates, vector<char> alphArray){
  
  vector<vector<char>> transitionList;
  int subListEntriesNum = alphArray.size()/(numStates*numStates);
  transitionList.resize(numStates, vector<char>(subListEntriesNum));//Want to create a list of lists and have each sublist be subListEntriesNum large
  int numSq = numStates*numStates; 
  vector< vector<char> >::iterator row;
  vector<char>::iterator col;
  
  for(int row = 0; row < numSq; row++) {

    for(int col = 0; col < subListEntriesNum; col++) {

      int randIndex = rand() % alphArray.size();
      cout << randIndex<<endl;
      cout << alphArray.size()<<endl;
      transitionList.at(row).at(col) = alphArray[randIndex];
      alphArray.erase(alphArray.begin()+randIndex);
     
    }
  }

    return transitionList;

}

void create(int numMarkovChains, int numStates,vector<char> alphArr){

  Automata* a = new Automata;

  for(int i = 0; i < numMarkovChains; i++){
    vector<vector<char>> splitArray = alphDivider(numStates,alphArr);
    addNewMarkovChain(a,numStates,splitArray);
  }
}

void addNewMarkovChain(Automata* a,int numStates,vector<vector<char>> splitArr){

  //TODO: ASSIGN TRANSITION STRINGS TO GENERATED STES
  //vector<STE *> mcs;
  //mcs.resize(numStates * numStates);
  /*
  vector<STE *> tOutDynamicVars;
  vector<STE *> tInDynamicVars;
  tOutDynamicVars.resize(numStates*numStates);
  tInDynamicVars.resize(numStates*numStates);
  */
  std::unordered_map<string, Element *> elements = a->getElements();
  int countI = 0;
  int countJ = 0;
  for (int i = 0; i < numStates; i++){
        STE *r = new STE("r"+to_string(i),"[*]","all-inputs");
	STE *s = new STE("s"+to_string(i), "", ""); // Check what string will cause this transition
	a->rawAddSTE(r);
	a->rawAddSTE(s);
	
        a->addEdge(elements["r"+to_string(i)],elements["s"+to_string(i)]);
        a->addEdge(elements["s"+to_string(i)],elements["r"+to_string(i)]);

	
    for (int j = 0; j < numStates; j++){
       if (i != j){
	      string out_path = "t_"+to_string(i)+"-"+to_string(j);
	      string in_path = "t_"+to_string(j)+"-"+to_string(i);
	      //Creating outbound transition node and creating a path from the base node 
	      //to the outbound transition node and a path from the transition node to the j node
	      
	      //tOutDynamicVars.at(count) = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      //a->rawAddSTE(tOutDynamicVars.at(count));
	      a->rawAddSTE(new STE(out_path,"",""));

	      
	      a->addEdge(elements["r"+to_string(i)],elements[out_path]); //mcs[count]
	      a->addEdge(elements[out_path],elements["r"+to_string(j)]); //mcs[count]

	      //Creating inbound transition node and connecting it to the base node and j node
	      // OLD WAY: STE *t_in+path = new STE("t_in"+path,!str+to_string(i+1),""); // Check what string will cause this transition
	      // tInDynamicVars.at(count) = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      // a->rawAddSTE(tInDynamicVars.at(count));
	      a->rawAddSTE(new STE(in_path,"",""));
	      
	      a->addEdge(elements["r"+to_string(j)],elements[in_path]); //mcs[count]
	      a->addEdge(elements[in_path],elements["r"+to_string(i)]); //mcs[count]

	      countI++;
	      countJ+=3;
      
    }
  }
    	countI++;
  }
}


int main(int argc, char * argv[]) {
  
  cout << "printing" <<endl;

  std::vector<std::vector<char>> test = alphDivider(8,createSymbolArray(256));
  for(int i = 0; i < test.size(); i++){
    for(int j = 0; j < test.at(i).size(); j++){
      cout << test.at(i).at(j)<<endl;
    }
  }

  Automata ap;

  STE *start = new STE("start", "[Matt]","all-input");
  STE *stop = new STE("stop", "[Bimmy]", "none");
  stop->setReporting(true);

  //Add them to data structure
  ap.rawAddSTE(start);
  ap.rawAddSTE(stop);

  //add edge between them
  ap.addEdge(start,stop);

  // Emit automata as anml file
  ap.automataToANMLFile("example.anml");
  ap.automataToMNRLFile("example.mrnl");

  //print out how many reports we've seen (should be zero)
  cout << ap.getReportVector().size() << endl;
  
  //enable report gathering for the automata
  ap.enableReport();
  
  //initialize simulation
  ap.initializeSimulation();
  
  //simulate the automata on two inputs
  ap.simulate('M');
  ap.simulate('J');
  
  
  //print out how many reports we've seen (should be 2)
  cout << ap.getReportVector().size() <<endl;
  

}


