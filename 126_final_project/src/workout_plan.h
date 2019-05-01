//Represents a workout plan object
//Created 4-15-19 by Rose Dinh

#pragma once
#include <string>
#include <vector>
#include "exercise.h"

class WorkoutPlan 
{
public:
	WorkoutPlan(std::string, std::vector<Exercise>);
	WorkoutPlan();
	~WorkoutPlan();
	std::string GetName();
	std::vector<Exercise> GetExercises();
	void SetName(std::string);
	void SetExercises(std::vector<Exercise>);
	bool ContainsExercise(std::string);
	void AddExercise(Exercise);
	void RemoveExercise(std::string);

	friend std::ostream& operator<<(std::ostream& stream, WorkoutPlan &c);

private:
	std::string name_;
	std::vector<Exercise> exercises_;

};