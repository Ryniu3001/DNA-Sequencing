#ifndef graf_hpp
#define graf_hpp

class GraphClass{
public:
    static int vertex;
    static int maxWeight;
    static int **matrix;
    void create(); //Tworzenie grafu
    void print();   //Wypisanie grafu na ekran
    ~GraphClass();    // Destruktor
};
extern GraphClass Graph;
#endif // graf_hpp
