//Represents a day object
//Created 4-28-19 by Rose Dinh

#pragma once
#include <vector>
#include <string>
#include "workout_plan.h"

class Day
{
public:
	Day();
	Day(std::string);
	~Day();

	void AddWorkoutPlan(WorkoutPlan);
	void RemoveWorkoutPlan(std::string);
	std::vector<WorkoutPlan>* GetWorkoutPlans();
	std::string GetName();

private:
	std::string name_;
	std::vector<WorkoutPlan> workout_plans_;
};

