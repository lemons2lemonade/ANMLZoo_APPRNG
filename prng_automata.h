class Prng_Automata {
 public:

};
void create(int numMarkovChains, int numStates,std::vector<char>alphArr);
void addNewMarkovChain(Automata* a,int numStates,std::vector<std::vector<char>>splitArr);
  std::vector<std::vector<char>> alphDivider(int numStates, std::vector<char> alphArray);
  std::vector<char> createSymbolArray(uint32_t length);
  
