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
  //randomChars.resize(length);
    for(int i = 0; i < length; i++) {
      randomChars.push_back( (char)i);
    }

    return randomChars;
}


vector<vector<char>> alphDivider(int numStates, vector<char> alphArray){

  cout << "Starting alph divider..." << endl;
  
  vector<vector<char>> transitionList;
  int subListEntriesNum = alphArray.size()/(numStates*numStates);
  //transitionList.resize(numStates, vector<char>(subListEntriesNum));//Want to create a list of lists and have each sublist be subListEntriesNum large
  int numSq = numStates*numStates; 

  int rowCount = 0;
  //FIX THE TYPE ERRORS IN THE LOOPS IMMEDIATELY BELOW
  // Initialize Vectors
  for(int row = 0; row < numSq; row++) {
    vector<char> column;
    cout << "Row Count: "<<rowCount<<endl;
    for(int col = 0; col < subListEntriesNum; col++) {
      //transitionList.at(row).push_back('\0'); //CHECK THIS LINE
      int randIndex = rand() % alphArray.size();
      cout <<"Getting Pushed into array: "<< randIndex <<endl;
      column.push_back(alphArray[randIndex]);
      alphArray.erase(alphArray.begin()+randIndex);
      //column.push_back('\0');
      
    }
    transitionList.push_back(column);
    rowCount++;
  }

  cout << "FINAL ROW COUNT: "<<rowCount<<endl;
  /*
  // Fill vectors with data
  for(int row = 0; row < numSq; row++) {
    //cout << "Row: "<<row<<endl;
    for(int col = 0; col < subListEntriesNum; col++) {
      //cout << "Col: " <<col<<endl;
      int randIndex = rand() % alphArray.size();
      // cout << "AlphDivider Index Accessed: " << randIndex << endl;
      //cout << "AlphDivider Size: " << alphArray.size()<<endl;
      transitionList.at(row).at(col) = alphArray[randIndex];
      alphArray.erase(alphArray.begin()+randIndex);
    }
  }
  */
  cout << "Ending alphDivider..." << endl;
  
    return transitionList;

}

void create(int numMarkovChains, int numStates,vector<char> alphArr,Automata* a){


  for(int e = 0; e < numMarkovChains; e++){
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
  cout << "Starting addNewMarkovChain..."<<endl;
  std::unordered_map<string, Element *> elements = a->getElements();
  int countI = 0;
  int countJ = 0;
  cout <<"Before double for-loop..."<<endl;
  for (int i = 0; i < numStates; i++){
    cout <<"Starting first for-loop..."<<endl;
        STE *r = new STE("r"+to_string(i),"[*]","all-inputs");
	STE *s = new STE("s"+to_string(i), "", ""); //Check what string will cause this transition
	cout << "Starting first if branch..."<<endl;
	if(i == 0){
	//Set stay transition set for each report node
	  for (int z = 0; z < splitArr.size(); z++){
	    cout << "Row In splitArr..."<<endl;
	  }



	  
	  cout << "Inside first if branch..."<<endl;
	  cout << "SplitArr.size(): "<<splitArr.size()<<endl;
	  //  cout <<"splitArr.at(5).size(): "<<splitArr.at(5).size()<<endl;
	  for (int k = 0; k < splitArr.at(splitArr.size()-1).size(); k++){
	    cout << "K: " << k<<endl;
	    cout << "I: " <<i<<endl;
	    cout << "ITEM ADDED TO TRANSITION: " << splitArr.at(countI).at(k) << endl;
	    s->addSymbolToSymbolSet(splitArr.at(countI).at(k));

	  }
	}
        else{
	     for (int k = 0; k < splitArr.at(countI).size(); k++){
	       cout << "K: " << k<<endl;
	       cout << "I: " <<i<<endl;
	       cout << "ITEM ADDED TO TRANSITION: "<< splitArr.at(i).at(k) << endl;
	       s->addSymbolToSymbolSet(splitArr.at(countI).at(k));
	     }
	}
       
  
	
	a->rawAddSTE(r);
	a->rawAddSTE(s);
	
        a->addEdge(elements["r"+to_string(i)],elements["s"+to_string(i)]);
        a->addEdge(elements["s"+to_string(i)],elements["r"+to_string(i)]);

	
    for (int j = 0; j < numStates; j++){
       if (i != j){

	      countI++;
	      //countJ++;
	      string out_path = "t_"+to_string(i)+"-"+to_string(j);
	      string in_path = "t_"+to_string(j)+"-"+to_string(i);
	      //Creating outbound transition node and creating a path from the base node 
	      //to the outbound transition node and a path from the transition node to the j node
	      
	      //tOutDynamicVars.at(count) = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      //a->rawAddSTE(tOutDynamicVars.at(count));
	      a->rawAddSTE(new STE(out_path,"",""));
	      //add transition set for outpath
	      for (int l = 0; l < splitArr.at(countI).size(); l++){
		//add chars in here
		static_cast<STE*>(elements[out_path])->addSymbolToSymbolSet(splitArr.at(countI).at(l));
	      }

	      
	      a->addEdge(elements["r"+to_string(i)],elements[out_path]); //mcs[count]
	      a->addEdge(elements[out_path],elements["r"+to_string(j)]); //mcs[count]

	      //Creating inbound transition node and connecting it to the base node and j node
	      // OLD WAY: STE *t_in+path = new STE("t_in"+path,!str+to_string(i+1),""); // Check what string will cause this transition
	      // tInDynamicVars.at(count) = new STE(out_path,"",""); //SET TRANSITION STRING HERE
	      // a->rawAddSTE(tInDynamicVars.at(count));

	      
	      a->rawAddSTE(new STE(in_path,"",""));
	      //add transition set for inpath
	      if (i == numStates-1 and j== numStates-1){
		for (int m = 0; m < splitArr.at(0).size(); m++){
	           //add chars in here
		  static_cast<STE*>(elements[out_path])->addSymbolToSymbolSet(splitArr.at(countI).at(m)); 
		}
	      }
	      else{
		for (int m = 0; m < splitArr.at(countI+1).size(); m++){
		   //add chars in here
		  static_cast<STE*>(elements[out_path])->addSymbolToSymbolSet(splitArr.at(countI).at(m));
		}
	      }
	      a->addEdge(elements["r"+to_string(j)],elements[in_path]); //mcs[count]
	      a->addEdge(elements[in_path],elements["r"+to_string(i)]); //mcs[count]

	    
      
    }
  }
    
  }
}


int main(int argc, char * argv[]) {
  
  cout << "Starting Main..." <<endl;
  
  std::vector<std::vector<char>> test = alphDivider(2,createSymbolArray(256));

  /*
  for(int i = 0; i < test.size(); i++){
    for(int j = 0; j < test.at(i).size(); j++){
      cout << "Row: "+ to_string(i)+ "Col: "+ to_string(j) <<endl;
      cout << test.at(i).at(j)<<endl;
    }
  }
  */

  cout << "Running example program..." << endl;
  
  Automata* a = new Automata;

  //create(int numMarkovChains, int numStates,vector<char> alphArr,Automata* a)
  create(1,2,createSymbolArray(256),a);
  
  /*
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
  */
  
  //print out how many reports we've seen (should be 2)
  cout << "Report Vector:"<<endl;
  cout << a->getReportVector().size() <<endl;
  

}


