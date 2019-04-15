//Created 4-15-19 by Rose Dinh

#pragma once
#include <string>
#include <vector>

class Exercise
{
public:
	Exercise(std::string name, std::string equipment);
	~Exercise();
	void AddWeight(int);
	void AddReps(int);
	std::vector<int> GetWeights();
	std::vector<int> GetReps();
	std::string GetName();
	std::string GetEquipment();

private:
	std::string name_;
	std::string equipment_;
	std::vector<int> weights_;
	std::vector<int> reps_;

};

