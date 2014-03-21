/*
	Project developed by Bhargava Reddy
	Implementation of a Hidden Markov Model
*/
/*

Creating a hidden markow model for given numer of states, observations
start probabilities, transition probabilities and emission probabilities


Assume that we have 's' number of states
also we also have 'o' number of observations

Also assume that X denotes the random variable for a state 
and Y denote the random variable for an oservation

so the states can be implemented as a map or a vector. The size would be 's'
the oservation is also implemented the same as above. The size would be 'o'

--> the start probabilities should add up to 1. and the data should be given so
	A check wwill be performed every instant the probabilites have been inititated.
	
	The probability and state should be mapped to each other so that the access is very simple

--> The transition probabilities is represented by a 2D array of size 's * s'
	Contains information about the probability to go from one state to another after a given instant of time

--> Emission probability would be an array of 'o * s' size because it gives the probability of P(Y/X)
	So the number of such probabilities is 'o * s'

*/


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <utility>

#include "hmm.h"

using namespace std;

hmm::hmm(	map<string,int> _loc_s, 
			map<string,int> _loc_c, 
			map<string,float> _prob_start, 
			map<pair<int,int>,float> _prob_trans, 
			map<pair<int,int>,float> _prob_emis)
{
	loc_s = _loc_s;
	loc_c = _loc_c;
	prob_start = _prob_start;
	prob_trans = _prob_trans;
	prob_emis = _prob_emis;
}

void hmm::load_obs_list(vector<int> _exec_list)
{
	exec_list = _exec_list;
}

float hmm::P_O_i(int y,int x)
{
	pair<int,int> myp;
	myp = make_pair(x,y);
	float result;

	result = prob_emis[myp];

	return result;
}


float hmm::P_S_i(int x2,int x1)
{
	pair<int,int> myp;
	myp = make_pair(x2,x1);
	float result;

	result = prob_trans[myp];

	return result;
}

float hmm::prob_t(int t)
{
	float result = 0.2;

	return result;
}


float hmm::prob_t_1(int t)
{
	float result = 0.2;

	return result;
}