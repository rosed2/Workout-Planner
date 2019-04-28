//Tests for day 4-28-19
//Created by Rose Dinh 

#include "../126_final_project/src/day.h"
#include "../126_final_project/src/workout_plan.h"
#include "../126_final_project/src/exercise.h"
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

//Setup
Exercise ex1 = Exercise("Exercise 1", "bicep", "none");
Exercise ex2 = Exercise("Exercise 2", "bicep", "dumbbells");
Exercise ex3 = Exercise("Exercise 3", "back", "none");

vector<Exercise> all_exercises{ ex1, ex2, ex3 };

vector<Exercise> vec1{ ex1, ex2 };
vector<Exercise> vec2{ ex2, ex3 };

WorkoutPlan w1 = WorkoutPlan("Plan 1", vec1);
WorkoutPlan w2 = WorkoutPlan("Plan 2", vec2);

//-----------------------------Tests for Day------------------------------
TEST_CASE("Day AddWorkoutPlan") {
	Day day = Day("name");
	REQUIRE(day.GetWorkoutPlans()->size() == 0);
	day.AddWorkoutPlan(w1);
	REQUIRE(day.GetWorkoutPlans()->size() == 1);
	REQUIRE((*day.GetWorkoutPlans())[0].GetName() == "Plan 1");
}

TEST_CASE("Day RemoveWorkoutPlan") {
	Day day = Day("name");
	day.AddWorkoutPlan(w1);
	day.AddWorkoutPlan(w2);
	REQUIRE(day.GetWorkoutPlans()->size() == 2);
	day.RemoveWorkoutPlan("Plan 1");
	REQUIRE(day.GetWorkoutPlans()->size() == 1);
	REQUIRE((*day.GetWorkoutPlans())[0].GetName() == "Plan 2");
}

TEST_CASE("Day RemoveWorkoutPlan Doesnt' Contain") {
	Day day = Day("name");
	day.AddWorkoutPlan(w1);
	day.AddWorkoutPlan(w2);
	REQUIRE(day.GetWorkoutPlans()->size() == 2);
	day.RemoveWorkoutPlan("Plan 3");
	REQUIRE(day.GetWorkoutPlans()->size() == 2);
	REQUIRE((*day.GetWorkoutPlans())[0].GetName() == "Plan 1");
	REQUIRE((*day.GetWorkoutPlans())[1].GetName() == "Plan 2");
}

TEST_CASE("Day GetName") {
	Day day = Day("name");
	REQUIRE(day.GetName() == "name");
}