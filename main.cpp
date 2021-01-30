#include "parameters.h"

long double simpson_integral(const std::vector<double>& x,const std::vector<double>& y)
{
    long double sum = 0, h, integral;
    unsigned int n = x.size()-1;
    if(n%2 != 0)
    {
        std::cout<<"wrong division"<<std::endl;
        return 0;
    }
    h = (x.back()-x.front())/n;
    for(int i = 1; i < n; i+= 2){sum += 4.0 * y[i];}
    for(int i = 2; i < n-1; i+= 2){sum += 2.0 * y[i];}
    integral = h/3.0 * (y[0] + y[n] + sum);
    return integral;
}

void solver(std::vector<double>& results_XX, std::vector<double>& results_X,std::vector<double>& results_CX,std::vector<double>& k_results, double dt,  double k,  double t) {
    parameters par;
    states state;
    double a = 0;
    for(int i = 0; i < 50; i++){
        while (a < t) {
            state.update_state(par, a, dt, k);
            a += dt;



        }

    }
    a = 0;
    std::vector<double> X;
    std::vector<double> XX;
    std::vector<double> CX;
    std::vector<double> time;
    while (a < t) {
        state.update_state(par, a, dt, k);
        state.lumis(X, CX, XX);
        time.push_back(a);
        a += dt;
    }
    results_X.push_back(simpson_integral(time,X));
    results_XX.push_back(simpson_integral(time,XX));
    results_CX.push_back(simpson_integral(time,CX));
    k_results.push_back(k);
}

void photon_calculator(double dt)
{
    parameters par;
    states state;
    for(int i=0; i<50; i++)
    {
        double t  = 0;
        while(t<5)
        {

            state.update_state(par, t, dt);
            t+=dt;

        }


    }
    state.return_states();

    std::vector<double> X;
    std::vector<double> XX;
    std::vector<double> CX;
    std::vector<double> time;


    double t  = 0;
    while(t<5)
    {


        state.update_state(par,t, dt);
        state.lumis(X,CX,XX);
        time.push_back(t);
        t+=dt;
    }

    std::cout<<"Lum of X  "<<simpson_integral(time,X)<<std::endl;
    std::cout<<"Lum of XX "<<simpson_integral(time,XX)<<std::endl;
    std::cout<<"Lum of CX "<<simpson_integral(time,CX)<<std::endl;

}


int main() {



    parameters par;
    states state;
//  Punkt 1
//    std::fstream fil;
//    fil.open("results.txt", std::ios::out);
//    double t  = 0;
//    double dt = 0.0003;
//    while(t<5)
//    {
//
//        state.update_state(par, t, dt);
//        state.save_state(fil, t);
//        t+=dt;
//
//    }
//    fil.close();



//  Punkt 2
//    for(int i=0; i<100; i++)
//    {
//        double t  = 0;
//        double dt = 0.0003;
//        while(t<5)
//        {
//
//            state.update_state(par, t, dt);
//            t+=dt;
//
//        }
//
//
//    }
//
//
//
//    double t  = 0;
//    double dt = 0.0003;
//    std::fstream file;
//    file.open("results_1.txt", std::ios::out);
//    state.save_state(file, t);
//    while(t<5)
//    {
//
//
//        state.update_state(par,t, dt);
//        //state.return_states();
//        state.save_state(file, t)
//        t+=dt;
//    }
//    file.close();
//
//

// punkt 3

    photon_calculator(0.0005);


// punkt 4


//    std::vector<double> results_X;
//    std::vector<double> results_XX;
//    std::vector<double> results_CX;
//    std::vector<double> results_k;
//
//    float k =0;
//    while(k<10)
//    {
//        k+=0.01;
//        solver(results_XX,results_X,results_CX,results_k,0.0005,k,5);
//
//
//    }
//    std::fstream file3;
//    file3.open("results3.txt", std::ios::out);
//    for(int i = 0; i< results_X.size();i++)
//    {
//        file3<< results_XX[i] << "," << results_CX[i] << "," << results_X[i] << "," << results_k[i] << std::endl;
//    }
//
//
//    file3.close();












    return 0;
}
