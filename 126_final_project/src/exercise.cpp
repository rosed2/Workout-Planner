//Created 4-15-19 by Rose Dinh

#include "exercise.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

Exercise::Exercise(string name, string equipment)
{
	name_ = name;
	equipment_ = equipment;
}

Exercise::~Exercise()
{
}

string Exercise::GetEquipment() {
	return equipment_;
}

string Exercise::GetName() {
	return name_;
}

vector<int> Exercise::GetReps() {
	return reps_;
}

vector<int> Exercise::GetWeights() {
	return weights_;
}

void Exercise::AddReps(int rep) {
	reps_.push_back(rep);
}

void Exercise::AddWeight(int weight) {
	weights_.push_back(weight);
}
