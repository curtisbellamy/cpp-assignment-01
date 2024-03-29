#include <iostream>
#include "matrix.hpp"
#include "GooglePageRank.hpp"
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {

    int input;
    vector<int> input2;

    fstream infile("connectivity.txt");

    if(!(infile.is_open())){
        cerr << "Unable to open file." << endl;
        exit(1);
    } else {
        while(infile >> input){
            input2.push_back(input);
        }
    }

    double arr[input2.size()];
    for (int i = 0; i < input2.size(); ++i) {
        arr[i] = input2[i];
    }

    double array2[16] = {0,1,1,0,
                         1,0,1,0,
                         1,1,0,0,
                         0,0,0,0};

    matrix test(arr, input2.size());

    GooglePageRank pr(arr, input2.size());

    matrix importance = pr.importanceMatrix(test);

    matrix teleport = pr.teleportationMatrix(test);

    matrix transition = pr.transitionMatrix(importance, teleport);

    matrix markov = pr.markov(transition);

    pr.print(markov);

    return 0;
}