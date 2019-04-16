//Tests for library 4-15-19
//Created by Rose Dinh 

#include "../src/exercise.h"
#include "../src/workout_plan.h"
#include "../src/library.h"

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;


//-----------------------------------------Tests for Library---------------------------------

//---------------------Tests for GetWorkoutPlans----------
TEST_CASE("Library GetWorkoutPlans") {
	Exercise ex1 = Exercise("Exercise 1", "none");
	Exercise ex2 = Exercise("Exercise 2", "dumbbells");
	Exercise ex3 = Exercise("Exercise 3", "none");

	vector<Exercise> vec1{ ex1, ex2 };
	vector<Exercise> vec2{ ex2, ex3 };

	WorkoutPlan w1 = WorkoutPlan("Plan 1", vec1);
	WorkoutPlan w2 = WorkoutPlan("Plan 2", vec2);
	vector<WorkoutPlan> work{ w1 };

	Library library = Library(work);
	REQUIRE(library.GetWorkoutPlans().size() == 1);
}

TEST_CASE("Library GetWorkoutPlans Empty") {
	vector<WorkoutPlan> work{ };

	Library library = Library(work);
	REQUIRE(library.GetWorkoutPlans().size() == 0);
}

//--------------------Tests for AddWorkoutPlan---------------
TEST_CASE("Library AddWorkoutPlan") {
	Exercise ex1 = Exercise("Exercise 1", "none");
	Exercise ex2 = Exercise("Exercise 2", "dumbbells");
	Exercise ex3 = Exercise("Exercise 3", "none");

	vector<Exercise> vec1{ ex1, ex2 };
	vector<Exercise> vec2{ ex2, ex3 };

	WorkoutPlan w1 = WorkoutPlan("Plan 1", vec1);
	WorkoutPlan w2 = WorkoutPlan("Plan 2", vec2);
	vector<WorkoutPlan> work{ w1 };

	Library library = Library(work);
	REQUIRE(library.GetWorkoutPlans().size() == 1);
	REQUIRE(library.GetWorkoutPlans()[0].GetName() == "Plan 1");

	library.AddWorkoutPlan(w2);
	REQUIRE(library.GetWorkoutPlans().size() == 2);
	REQUIRE(library.GetWorkoutPlans()[1].GetName() == "Plan 2");
}