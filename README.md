# *APPRNG*

## **Description**
The Automata Processor pseudo random number generator application is meant to generate random output that passes multiple standard statisical tests. This repository can be used to generated 2,4, or 8 state markov chains in order to simulate the pseudorandom output process. Additionally, an arbitrary number of 2,4, or 8 state markov chains can be simulated while using this application.
 
** Note: markov chains with sizes other than 2,4, or 8 states are not supported. **

### **Automata Generator Program**

#### ** prng_automata.cpp **
prng_automata.cpp asks for two values when running its executable. The first parameter is the number of states per markov chain that will be generated, and the second parameter is the number of markov chains that will be generated in total.

Example Usage
```
$ make
$ ./example 2 50
```
The commands above will create 50 2-state markov chain automata.

Additionally, running the executable file after using the make command will generate an .ANML file that can be used in conjunction with the Automata visualizer web application (https://github.com/dankramp/ANMLViewer).

##### **prng_automata.cpp function documenatation**

**createSymbolArray**
This function takes in the length of the alphabet vector, and an alphabet vector of unsigned characters. This function's purpose is to cast each member of the original alphabet vector into an unsigned character symbol for later use in each markov chain state. 

**randomizeSymbolArray**
This function is meant to randomize the contents of the vector that createSymbolArray generates. A temporary vector is created and random indexes of the passed in vector are pushed onto the temporary vector without replacement, until a completely randomized vector has been created.

** main **
A user-specified number of Markov chains are generated, along with a user-specificied number of states. Each markov state functions independently of all other states in a given markov chain. In practice, this means that the total alphabet is split into the equal parts and assigned to each outward transition for each state in a given markov chain. As a result, there is a 100% chance that a transition will occur on a given input. 