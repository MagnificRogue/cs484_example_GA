#include <cstdlib>
#include <vector>
#include <climits>
#include <iostream>

const int POPULATION_SIZE = 2000;
const unsigned int TERMINATION = UINT_MAX ;
const float MUTATION_RATE = .1;
const float CROSSOVER_RATE = .6;

struct Candidate {
  unsigned int gene;
  unsigned int fitness;
};


void evaluatePopulation(Candidate* population, unsigned long long &currentFitness);
void selectFitterIndividuals(Candidate* population);
void matePopulation(Candidate* population);
void mutateIndividuals(Candidate* population);

using namespace std;

int main(int argc, char** argv){


  srand(time(0));

  // Step 1: Initialize the population
  //   just to demonstrate the changes 
  //   in our population, we'll ensure
  //   that our population doesn't have
  //   too great of an initial condition
  Candidate population[POPULATION_SIZE];
  for(int i=0; i < POPULATION_SIZE; i++){
    population[i].gene = rand() % 100; 
  }

  // Step 2: Evaluate the population
  //  for our example, the fitness of a particular member of the population
  //  is just how "large" the value in their gene is
  //  for convenience, we'll output the average fitness of our population as well
  unsigned long long currentFitness = 0;
  evaluatePopulation(population, currentFitness);
  std::cout << "Initial Population Fitness: " << int(double(currentFitness) / double(POPULATION_SIZE)) << "\n";  

  unsigned int iteration = 0;
  // Step 3 While Termination condition not met do
  while(currentFitness < TERMINATION) { 
    iteration++;
    // Step 4 Select fitter individuals for reproduction
    selectFitterIndividuals(population);

    // Step 5 Recombine Individuals
    matePopulation(population);

    // Step 6  Mutate individuals
//    mutateIndividuals(population);

    // Step 7 Evaluate the fitness of the modified individuals
    evaluatePopulation(population, currentFitness);


    std::cout << "Iteration " << iteration << " Population Fitness: " << currentFitness << "\n";  
  }


  return 0;
}


void evaluatePopulation(Candidate* population, unsigned long long &currentFitness) {
  currentFitness = 0; 
  for(int i=0; i < POPULATION_SIZE; i++) {
    population[i].fitness = population[i].gene; 
    currentFitness += population[i].fitness;
  }
  currentFitness = long(double(currentFitness) / double(POPULATION_SIZE));
}

// The goal of this function is to take the input population and return a population
// of the same size but with the individuals chosen at random. The probability of 
// a member of the popluation being chosen is proportional to their total fitness. 
// Meaning, a fitter individual has a better chance at being chosen than a less fit
// individual
void selectFitterIndividuals(Candidate* population) {

  unsigned long long totalFitness = 0;
  //first, get the total sum of fitness from the population
  for(int i=0; i < POPULATION_SIZE; i++) {
    totalFitness += population[i].fitness; 
  }
  
  //second, depending on the fitness of each candidate, push it into a vector of
  //candidates
  std::vector<Candidate> candidates;
  
  for(int i=0; i < POPULATION_SIZE; i++) {
    for(int j=0; j < population[i].fitness; i++) {
      candidates.push_back(population[i]);
    } 
  }
  // last, generate a new population depending on our candidates
  for(int i=0; i < POPULATION_SIZE; i++) {
    population[i] = candidates[ rand() % candidates.size()]; 
  }
  
}

void matePopulation(Candidate*  population) {

  for (int i=0; i < POPULATION_SIZE; i += 2) {
    if( float((rand()%11)/10) < CROSSOVER_RATE ) {

      unsigned int crossOverPoint = rand() % 32;
      unsigned int lowerMask = crossOverPoint - 1;
      unsigned int upperMask = UINT_MAX ^ lowerMask;
      
      Candidate a = population[i];
      Candidate b = population[i+1];
      unsigned int tmp = b.gene; 
      b.gene = (b.gene & upperMask) | (a.gene & lowerMask);
      a.gene = (a.gene & upperMask) | (tmp & lowerMask);
      population[i] = a;
      population[i+1] = b;
    }   
  }
}

void mutateIndividuals(Candidate* population) {
  for(int i=0; i < POPULATION_SIZE; i++) {
    for (int j=0; j < 32; j++){
      if( rand() % 11 <= int(MUTATION_RATE * 10)){
        population[i].gene |= 1 << j; 
      } 
    } 
  }
}

