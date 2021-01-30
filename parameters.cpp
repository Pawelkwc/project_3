#include "parameters.h"
double parameters::alp(double t, double k)
{
        double a;
        int unit = 1000;
        if (t > 0)
        {
            a = k * 160 * std::exp(-t   *unit/ 5);
        }
        else
        {
            a = 0;
        }
        return a;
}
double parameters::bet(double t, double k)
{
    double b;
    int unit = 1000;
    if (t > 0)
    {
        b = k * 172 * std::exp(-t   *unit/ 5);
    }
    else{
        b = 0;
    }
    return b;

}

double parameters::ks(double t, double k) {
    double c;

    int unit = 1000;

    if (t > 0) {
        c = k * 52 * std::exp(-t * unit / 5);
    } else {
        c = 0;
    }
    return c;
}

void parameters::return_parameters() const
{
    std::cout << alpha <<" " << beta <<" " << ksi <<" " << t_X <<" "<<t_CX<<std::endl;
}

states::states() {
    XX = 0.2;
    CX = 0.2;
    X = 0.2;
    dot = 0.2;
    carrier = 0.2;
}

double states::dXXdt(parameters &par, double t, double dXX ,double dX , double dCX , double k ) const
{
    double dyXX = -(XX + dXX) * par.t_XX + (X + dX) * par.ks(t, k) + (CX + dCX) * par.alp(t, k);
    return dyXX;
}

double states::dCXdt(parameters &par, double t, double dX , double dCX , double dcarrier ,  double k ) const
{
    double dydCX = (X + dX) * par.bet(t, k) - (CX + dCX) * par.alp(t, k) - (CX + dCX) * par.t_CX + (carrier + dcarrier) * par.ks(t, k);
    return dydCX;
}

double states::dXdt(parameters &par, double t, double dXX ,double dX , double ddot , double dcarrier ,  double k ) const
{
    double dydx = (XX + dXX) * par.t_XX - (X + dX) * par.ks(t, k) - (X + dX) * par.bet(t, k) - (X + dX) * par.t_X  + (dot + ddot) * par.ks(t, k) + (carrier + dcarrier) * par.alp(t, k);
    return dydx;
}

double states::ddotdt(parameters &par, double t, double ddot ,double dX , double k ) const
{
    double dyddot = (X + dX) * par.t_X - (dot + ddot) * par.ks(t, k) - (dot + ddot) * par.bet(t, k);
    return dyddot;
}

double states::dcarrier(parameters &par, double t, double dCX, double ddot , double dcarrier , double k ) const
{
    double dydcarrier = (dot + ddot) * par.bet(t, k) - (carrier + dcarrier) * par.alp(t, k) - (carrier + dcarrier) * par.ks(t, k) + (CX + dCX) * par.t_CX;
    return dydcarrier;
}

void states::update_state(parameters &par, double t, double dt, double k) {
    double k1_XX, k2_XX, k3_XX, k4_XX;
    double k1_CX, k2_CX, k3_CX, k4_CX;
    double k1_X, k2_X, k3_X, k4_X;
    double k1_dot, k2_dot, k3_dot, k4_dot;
    double k1_carrier, k2_carrier, k3_carrier, k4_carrier;

    k1_XX = dt * dXXdt(par, t, 0,0,0, k);
    k1_CX = dt * dCXdt(par, t, 0,0,0, k);
    k1_X = dt * dXdt(par, t, 0,0,0,0, k);
    k1_dot = dt * ddotdt(par, t, 0,0, k);
    k1_carrier = dt * dcarrier(par, t, 0,0,0, k);

    k2_XX= dt * dXXdt(par, t + 0.5 * dt, 0.5 * k1_XX,0.5 * k1_X,0.5 * k1_CX, k);
    k2_CX = dt * dCXdt(par, t + 0.5 * dt, 0.5 * k1_X,0.5 * k1_CX,0.5 * k1_carrier, k);
    k2_X = dt * dXdt(par, t + 0.5 * dt,0.5 * k1_XX,0.5 * k1_X,0.5 * k1_dot,0.5 * k1_carrier, k);
    k2_dot = dt * ddotdt(par, t + 0.5 * dt, 0.5 * k1_dot,0.5 * k1_X, k);
    k2_carrier = dt * dcarrier(par, t + 0.5 * dt, 0.5 * k1_CX,0.5 * k1_dot,0.5 * k1_carrier, k);

    k3_XX= dt * dXXdt(par, t + 0.5 * dt, 0.5 * k2_XX,0.5 * k2_X,0.5 * k2_CX, k);
    k3_CX = dt * dCXdt(par, t + 0.5 * dt, 0.5 * k2_X,0.5 * k2_CX,0.5 * k2_carrier, k);
    k3_X = dt * dXdt(par, t + 0.5 * dt,0.5 * k2_XX,0.5 * k2_X,0.5 * k2_dot,0.5 * k2_carrier, k);
    k3_dot = dt * ddotdt(par, t + 0.5 * dt, 0.5 * k2_dot,0.5 * k2_X, k);
    k3_carrier = dt * dcarrier(par, t + 0.5 * dt, 0.5 * k2_CX,0.5 * k2_dot,0.5 * k2_carrier, k);

    k4_XX= dt * dXXdt(par, t +dt,  k3_XX,k3_X,k3_CX, k);
    k4_CX = dt * dCXdt(par, t +dt, k3_X,k3_CX,k3_carrier, k);
    k4_X = dt * dXdt(par, t +dt,k3_XX,k3_X,k3_dot,k3_carrier, k);
    k4_dot = dt * ddotdt(par, t + dt, k3_dot,k3_X, k);
    k4_carrier = dt * dcarrier(par, t + dt, k3_CX,k3_dot,k3_carrier, k);


    XX += (1.0 / 6.0) * (k1_XX + 2 * k2_XX + 2 * k3_XX + k4_XX);
    CX += (1.0 / 6.0) * (k1_CX + 2 * k2_CX + 2 * k3_CX + k4_CX);
    X  += (1.0 / 6.0) * (k1_X + 2 * k2_X + 2 * k3_X + k4_X);
    dot +=(1.0 / 6.0) * (k1_dot + 2 * k2_dot  + 2 * k3_dot  + k4_dot );
    carrier += (1.0 / 6.0) * (k1_carrier + 2 * k2_carrier  + 2 * k3_carrier + k4_carrier );

}
 void states::return_states() const
 {
    std::cout << XX << " " << CX << " " << X << " " << dot << " " << carrier << std::endl;
 }

 void states::save_state(std::fstream &file, double t) const
 {
    file << XX << "," << CX << "," << X << "," << dot << "," << carrier << "," << t << std::endl;
 }

 void states::lumis(std::vector<double> &vec_x, std::vector<double> &vec_xx, std::vector<double> &vec_cx) const
 {
        vec_x.push_back(X);
        vec_cx.push_back(CX);
        vec_xx.push_back(XX);
 }





