#ifndef alg_hpp
#define alg_hpp

class BruteForceClass{
private:
    int optTime,l; //optymalny czas, licznik w tablicy z optymalna droga,
    int *optPath;
    bool *visited;
    int *path;
public:
    BruteForceClass(int v);
    void start(int x,int time,int v);
    void result(int v);
    ~BruteForceClass();

};

struct ListStruct{
    int value;
    ListStruct *next;
};

class GeneticClass{
private:
    short int ** chromosom;
    short int ** children;
    int *ratings;
    int lc; // populacja
    ListStruct *head;
    int bestScoreInAll;
    int bestChromosomInAll;
    void DrawingPopulation(int liczbaChromosomow);
    void CreateList();
    int removeFromList(int a);
    void PrintList();
    int Rating(int liczbaChromosomow, int *bestChromosom);
    void Crossover(int par1, int par2, short int child1[], short int child2[]);
    void Mutation(short int chomosome[]);
    int TournamentSelection(int x,int liczbaChromosomow); //x - liczba chromosow w turnieju
public:
    void Interface();
    ~GeneticClass();
};



#endif // alg_hpp
