//
// Created by curti on 2019-01-29.
//

#include "matrix.hpp"
#include <iomanip>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>



matrix::matrix() {
    myVector.resize(1, vector<double>(1));
}


matrix::matrix(int n) {
    try{
        if(n <= 0)
            throw exception();
    }catch (exception e){
        cerr << "Error occurred. Integer must be positive and greater than zero." << endl;
    }
    myVector.resize(n, vector<double>(n));

}


matrix::matrix(int r, int c) {
    try {
        if (r <= 0 || c <= 0) {
            throw exception();
        }

        myVector.resize(r, vector<double>(c));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                myVector[i][j] = 0.0;
            }
        }

    } catch (exception &e) {
        cerr << "Exception occurred. Input numbers must be greater than zero." << endl;
    }
}


matrix::matrix(vector<vector<double>> vec) {
    double squareRoot = sqrt(vec.size());
    try {
        if (squareRoot - floor(squareRoot) != 0) {
            throw exception();
        } else {

            myVector.resize(vec.size(), vector<double>(vec.size()));
            for (int i = 0; i < vec.size(); i++) {
                for (int j = 0; j < vec[i].size(); j++) {
                    myVector[i][j] = vec[i][j];
                }
            }
        }

    } catch (exception e) {
        cerr << "Error occurred. Vector size must be a perfect square." << endl;
    }
}

//Ask jeff what integers too large means
void matrix::set_value(int r, int c, double val) {
    try{
        if(r < 0 || r > myVector.size())
            throw exception();
        else if(c < 0 || c > myVector[0].size())
            throw exception();
        else
            myVector[r][c] = val;
    } catch (exception e){
        cerr << "Error occurred. Array indexes do not exist." << endl;
    }
}


//Ask jeff what integers too large means
double matrix::get_value(int r, int c) const {
    try{
        if(r < 0 || r > myVector.size())
            throw exception();
        else if(c < 0 || c > myVector[0].size())
            throw exception();
        else
            return myVector[r][c];
    } catch (exception e){
        cerr << "Error occurred. Array indexes do not exist." << endl;
    }
}

void matrix::clear() {
    for (int i = 0; i < myVector.size(); ++i) {
        for (int j = 0; j < myVector[i].size(); ++j) {
            myVector[i][j] = 0.0;
        }
    }
}


matrix::~matrix() {
    myVector.clear(); // better way to do this??
    // because not using new keyword, gets dealloocated on stack
}


ostream &operator<<(std::ostream &os, const matrix& obj) {
    for (int i = 0; i < obj.myVector.size(); i++) {
        for (int j = 0; j < obj.myVector[i].size(); j++) {
//            cout << showpoint << setprecision(2) <<  myVector[i][j] << " ";
            os << obj.myVector[i][j] << " ";
        }
        os << endl;
    }
    return os;
}


bool operator== (const matrix& lhs, const matrix& rhs){
    if (lhs.myVector.size() != rhs.myVector.size())
        return false;
    else {
        for (int i = 0; i < lhs.myVector.size(); i++) {
            for (int j = 0; j < lhs.myVector[i].size(); j++) {
//                if (lhs.get_value(i, j) != rhs.get_value(i, j)) {
                if((std::max(lhs.get_value(i, j), rhs.get_value(i, j)) - std::min(lhs.get_value(i, j), rhs.get_value(i, j))) > matrix::TOLERANCE){
                    return false;
                }
            }
        }
    }
    return true;

}

bool operator!= (const matrix& lhs, const matrix& rhs){
    if (lhs.myVector.size() != rhs.myVector.size())
        return true;
    else {
        for (int i = 0; i < lhs.myVector.size(); i++) {
            for (int j = 0; j < lhs.myVector[i].size(); j++) {
//                if (lhs.get_value(i, j) != rhs.get_value(i, j)) {
                if((std::max(lhs.get_value(i, j), rhs.get_value(i, j)) - std::min(lhs.get_value(i, j), rhs.get_value(i, j))) > matrix::TOLERANCE){
                    return true;
                }
            }
        }
    }
    return false;

}


