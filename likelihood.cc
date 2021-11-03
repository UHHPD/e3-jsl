#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return (pow(mu,k)*exp(-mu))/(tgamma(k+1));
}

double prob(std::vector<int> datenvector, double mu){
  long double L=1;
  for(int k : datenvector){
    L *= (pow(mu,k)*exp(-mu))/(tgamma(k+1));
  }
  return L;
}

int main() {
    using namespace std;

    vector<int> daten;

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }

    cout << "Likelihood = " << prob(daten, 3.11538) << std :: endl ;

    ofstream fout_l("likelihood.txt");
    ofstream fout_log("nll.txt");
    ofstream fout_del("deltanll.txt");
    ofstream fout_int("interval.txt");
    for(double mu = 0; mu < 6; mu+=0.01){
    fout_l << mu << " " << prob(daten, mu) << std :: endl;
    fout_log << mu << " " << -2*log(prob(daten,mu)) << std :: endl;
    fout_del << mu << " " << (-2*log(prob(daten,mu)))-(-2*log(prob(daten,3.11538))) << std :: endl;
    if(-2*log((prob(daten,mu))/prob(daten,3.11538))<1.0){
      fout_int << mu << " " << -2*log((prob(daten,mu))/prob(daten,3.11538)) << std :: endl;
    }
    }
    
    fout_l.close();
    fout_int.close();
    fout_del.close();
    fin.close();
    
}