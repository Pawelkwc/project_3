
#ifndef PROJECT_3_PARAMETERS_H
#define PROJECT_3_PARAMETERS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

struct parameters{
    double alpha = 0, beta = 0 , ksi = 0;
    double t_X  = 3.45;
    double t_CX = 3.03;
    double t_XX = 5.26;

    double alp(double t, double k = 1);

    double bet(double t, double k = 1);

    double ks(double t, double k = 1);

    void return_parameters() const;

};


class states {
private:
    double XX, CX, X, carrier, dot;

public:
    states();

    double dXXdt(parameters &par, double t, double dXX = 0,double dX =0, double dCX =0, double k = 1) const;
    double dCXdt(parameters &par, double t, double dX = 0, double dCX = 0, double dcarrier = 0,  double k = 1) const;
    double dXdt(parameters &par, double t, double dXX = 0,double dX = 0, double ddot = 0, double dcarrier = 0,  double k = 1) const;
    double ddotdt(parameters &par, double t, double ddot = 0,double dX =0, double k = 1) const;
    double dcarrier(parameters &par, double t, double dCX, double ddot = 0, double dcarrier = 0, double k = 1) const;

    void update_state(parameters &par, double t, double dt, double k = 1);

    void return_states() const;

    void save_state(std::fstream &file, double t) const;

    void lumis(std::vector<double> &vec_x, std::vector<double> &vec_xx, std::vector<double> &vec_cx) const ;


};




#endif //PROJECT_3_PARAMETERS_H
