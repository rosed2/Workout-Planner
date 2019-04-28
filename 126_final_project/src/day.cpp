#include "day.h"
#include<string>
#include<vector>
using std::string;
using std::vector;

Day::Day()
{
}

Day::Day(string name) {
	name_ = name;
	workout_plans_ = vector<WorkoutPlan>{};
}

Day::~Day()
{
}

void Day::AddWorkoutPlan(WorkoutPlan to_add) {
	workout_plans_.push_back(to_add);
}

void Day::RemoveWorkoutPlan(string name) {
	for (vector<WorkoutPlan>::iterator it = workout_plans_.begin(); it != workout_plans_.end(); 
																							++it) {
		if (it->GetName() == name) {
			workout_plans_.erase(it);
			return;
		}
	}
}

vector<WorkoutPlan>* Day::GetWorkoutPlans() {
	return &workout_plans_;
}

string Day::GetName() {
	return name_;
}
