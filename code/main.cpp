#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <fstream>
#include <sstream>

#include "hmm.h"

using namespace std;


map<string,int> s_loc;					// To give the location of a string
map<string,int> o_loc;					// To give the location of the observation in the list 
map<string,float> start_prob;			// the start probabilities of state
map<pair<int,int>,float> trans_prob;	// The transition probability
map<pair<int,int>,float> emis_prob;		// The emission probability
vector<int> observation_vec;

float give_prob_T(string s1,string s2)
{
	int i1 = s_loc[s1];
	int i2 = s_loc[s2];

	pair<int,int> p = make_pair(i1,i2);

	float result;
	result = trans_prob[p];

	return result;
}

float give_prob_E(string s1,string s2)
{
	int i1 = s_loc[s1];
	int i2 = o_loc[s2];

	pair<int,int> p = make_pair(i1,i2);

	float result;
	result = emis_prob[p];

	return result;
}

int main()
{
	int s;	// number of states
	int o;	// number of possible observations something can make
	int i,j; 	// Temporary variable used in for statements
	string temp_s = "";
	string temp_o = "";
	float prob_s;
	float total_prob;
	string temp_line = "";

	ifstream myfile ("input_file/state_obs");

	// cout<<"Give the number of states: ";
	getline(myfile,temp_line);
	istringstream buffer(temp_line);
	buffer >> s;
	// cout<<s<<endl;

	// cout<<"Give the number of observations: ";
	getline(myfile,temp_line);
	istringstream buffer1(temp_line);
	buffer1 >> o;
	// cout<<o<<endl;

	myfile.close();
	
	// The values of s,o are available with us

	// Assuming that each state is represented by a string
	// Taking the input of all the states

	ifstream states_list ("input_file/states_list");

	// cout<<"Please give me the states: "<<endl;
	vector<string> state_vec;

	for(i=0;i<s;i++)
	{
		// cout<<"state "<<i<<": ";
		getline(states_list ,temp_s);
		//cin>>temp_s;
		state_vec.push_back(temp_s);
		// cout << temp_s <<endl;

		s_loc[temp_s] = i;
	}

	states_list.close();

	ifstream obs_list ("input_file/obs_list");

	// cout<<"Please give me all the possile observations: "<<endl;
	vector<string> obs_vec;

	for(i=0;i<o;i++)
	{
		// cout<<"state "<<i<<": ";
		getline(obs_list ,temp_o);
		obs_vec.push_back(temp_o);
		// cout << temp_o <<endl;
		o_loc[temp_o] = i;
	}
		obs_list.close();
	//Creating a map for start probabilities

	// cout<<"Please give me the probabilities for each of the states: "<<endl;
	ifstream state_prob ("input_file/start_prob");
	total_prob = 0.0;
	for(i=0;i<s;i++)
	{
		// cout<<state_vec[i]<<": ";
		getline(state_prob,temp_s);
		prob_s = stof(temp_s);
		// cout<<temp_s<<endl;
		total_prob = total_prob + prob_s;
		if(total_prob < 1.0 || i== (s - 1))
			{
				if(i == (s - 1))
					start_prob[state_vec[i]] = 1.0 - (total_prob - prob_s);
				else
					start_prob[state_vec[i]] = prob_s;
			}
		else
			{
				// cout<<"The total probability is exceeding 1. Program Exiting...."<<endl;
				exit(1);
			}

	}

	state_prob.close();

	//// Taking the inputs for transitions..
	// cout<<"Give the inputs for transition probabilities: \n";
	ifstream tran_prob ("input_file/trans_prob");
	pair<int,int> my_pair;
	for(i=0;i<s;i++)
	{
		total_prob = 0.0;
		for(j=0;j<s;j++)
		{
			tran_prob>>temp_s;
			prob_s = stof(temp_s);
			// cout<<prob_s<<" ";
			total_prob = total_prob + prob_s;
			my_pair = make_pair(i,j);
			if(total_prob < 1 || j==(s - 1))
			{
				if(j == (s - 1))
				{
					trans_prob[my_pair] = 1.0 - (total_prob - prob_s);
				}
				else
				{
					trans_prob[my_pair] = prob_s;
				}
			}
			else
			{
				// cout<<"The total probability is exceeding 1. Program Exiting...."<<endl;
				exit(1);
			}
		}
		// cout<<endl;
	}

	tran_prob.close();

	// cout<<"Give the inputs for emission probabilities: \n";
	ifstream emi_prob ("input_file/emis_prob");
	for(i=0;i<s;i++)
	{
		total_prob = 0.0;
		for(j=0;j<o;j++)
		{
			emi_prob>>temp_s;
			prob_s = stof(temp_s);
			// cout<<prob_s<<" ";
			total_prob = total_prob + prob_s;
			my_pair = make_pair(i,j);
			if(total_prob <= 1.0 || j==(o - 1))
			{
				if(j == (o - 1))
				{
					emis_prob[my_pair] = 1.0 - (total_prob - prob_s);
				}
				else
				{
					emis_prob[my_pair] = prob_s;
				}
			}
			else
			{
				// cout<<"The total probability is exceeding 1. Program Exiting...."<<endl;
				exit(1);
			}
		}
		// cout<<endl;
	}

	emi_prob.close();

	// cout<<"All inputs have been succesfully provided"<<endl;

	/// Now we need to take the values for evaluation
	/// we need to first take the input of number of observations recorded by the computer

	ifstream observatons ("input_file/comp_obsv");

	int obs;
	// cout<<"Please provide the number of oservations: ";
	observatons>>temp_s;

	obs = stoi(temp_s);
	// cout<<obs<<endl;

	// cout<<"The observations are: \n";

	for(i=0;i<obs;i++)
	{
		observatons>>temp_o;
		// cout<<temp_o<<" ";
		observation_vec.push_back(o_loc[temp_o]);
	}

	// cout<<endl;

	hmm HMM =  hmm(state_vec,obs_vec,s_loc,o_loc,start_prob,trans_prob,emis_prob);

	HMM.load_obs_list(observation_vec);

	cout<<"String whose probability is to be calculated: ";
	cin>>temp_s;

	float ss = HMM.execute_x(temp_s);
	cout<<"Result is: "<<ss<<endl;

	return 0;
}