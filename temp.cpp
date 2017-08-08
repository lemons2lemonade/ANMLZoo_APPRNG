#include "automata.h"
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
  int subListEntriesNum = alphArray.size()/numStates;
  transitionList.resize(numStates, vector<char>(subListEntriesNum));//Want to create a list of lists and have each sublist be subListEntriesNum large
  
  vector< vector<char> >::iterator row;
  vector<char>::iterator col;
  
  for(int row = 0; row < subListEntriesNum; row++) {

    for(int col = 0; col < numStates; col++) {

      int randIndex = rand() % 256;
      transitionList.at(row).at(col) = alphArray[randIndex];
      alphArray.erase(alphArray.begin()+randIndex);
     
    }
  }

    return transitionList;

}

void create(int numMarkovChains, int numStates){
  Automata* a = new Automata;
  for (int i= 0: numMarkovChains){
    addNewMarkovChain(numStates);
  }
}
void addNewMarkovChain(Automata a,int numStates){

  //TODO: ASSIGN TRANSITION STRINGS TO GENERATED STES
  vector<STE> mcs;
  mcs.resize(numStates*numStates);
  
  vector<STE*> tOutDynamicVars;
  vector<STE*> tInDynamicVars;
  tOutDynamicVars.resize(numStates*numStates);
  tInDynamicVars.resize(numStates*numStates);

  int count = 0;
  for (int i = 0; i < numStates; i++){
        STE *r = new STE("r"+to_string(i),"[*]","all-inputs");
	STE *s = new STE("s"+to_string(i), leftOverSplit, ""); // Check what string will cause this transition
        mcs[count].addEdge("r"+to_string(i),"s"+to_string(i));
        mcs[count].addEdge("s"+to_string(i),"r"+to_string(i));

	
    for (int j = 0; j < numStates; j++){
       if (i != j){
	      string out_path = "t_"+to_string(i)+"-"+to_string(j);
	      string in_path = "t_"+to_string(j)+"-"+to_string(i);
	      //Creating outbound transition node and creating a path from the base node 
	      //to the outbound transition node and a path from the transition node to the j node
	      
	      tOutDynamicVars[count] = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      a->rawAddEdge(a->getElement("r"+to_string(i)),a->getElement(out_path)); //mcs[count]
	      a->rawAddEdge(a->getElement(out_path),a->getElement("r"+to_string(j))); //mcs[count]

	      //Creating inbound transition node and connecting it to the base node and j node
	      // OLD WAY: STE *t_in+path = new STE("t_in"+path,!str+to_string(i+1),""); // Check what string will cause this transition
	      tInDynamicVars[count] = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      a->rawAddEdge(a->getElement("r"+to_string(j)),a->getElement(in_path)); //mcs[count]
	      a->rawAddEdge(a->getElement(in_path),a->getElement("r"+to_string(i))); //mcs[count]

	      count++;

      
    }
  }
}
