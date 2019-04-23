//Created 4-15-19

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "exercise.h"
#include "workout_plan.h"

class Library
{
public:
	Library(std::vector<WorkoutPlan>*, std::vector<Exercise>*);
	Library();
	~Library();
	std::vector<WorkoutPlan> SearchForPlanByName(std::string);
	std::vector<WorkoutPlan> SearchForPlanByExercise(std::string);
	void AddWorkoutPlan(WorkoutPlan);
	std::vector<WorkoutPlan>* GetWorkoutPlans();
	std::vector<Exercise>* GetAllExercises();
	std::vector<Exercise> SearchForExercisesByName(std::string);
	std::vector<Exercise> SearchForExercisesByMuscle(std::string);
	std::vector<Exercise> SearchForExercisesByEquipment(std::string);

private:
	std::vector<WorkoutPlan>* workout_plans_;
	std::vector<Exercise>* all_exercises_;
};