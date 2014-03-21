#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;

class hmm
{
	map<string,int> loc_s;
	map<string,int> loc_c;
	vector<string> vec_state;
	vector<string> vec_obs;
	map<string,float> prob_start;			// the start probabilities of state
	map<pair<int,int>,float> prob_trans;	// The transition probability
	map<pair<int,int>,float> prob_emis;		// The emission probability
	vector<int> exec_list;	
	float den_p ;

	////// we need maps for storing the values of Prob_t and Prob_t_1

	map<pair<int,int>,float> map_t;
	map<pair<int,int>,float> map_t_1;
	map<int,float> D;

public:
	hmm(vector<string> _vec_state,
		vector<string> _vec_obs,
		map<string,int> _loc_s, 
		map<string,int> _loc_c, 
		map<string,float> _prob_start, 
		map<pair<int,int>,float> _prob_trans, 
		map<pair<int,int>,float> _prob_emis);

	void load_obs_list(vector<int> _exec_list);

	/*
		We need to give some notation to various variables like
		P(Y/X)     		since it is constant for all t it is same
		P(Xt/Y1:t) 		this is denoted as prob_t();
		P(Xt/Y1:t-1) 	This is denoted as prob_t_1();
 	*/


	void set_den(int t);
	float P_O_i(int y,int x);
	float P_S_i(int x2,int x1);
	float prob_t(int x, int t);
	float prob_t_1(int x, int t);
	float execute_x(string x);
};