//Tests for workout_plan 4-15-19
//Created by Rose Dinh 

#include "../126_final_project/src/exercise.h"
#include "../126_final_project/src/workout_plan.h"
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

Exercise ex1 = Exercise("name", "equipment");

//-----------------------------Tests for Exercises------------------------------
TEST_CASE("Exercise Constructor") {
	REQUIRE(ex1.GetName() == "name");
	REQUIRE(ex1.GetEquipment() == "equipment");
}

TEST_CASE("Exercise Reps") {
	REQUIRE(ex1.GetReps().size() == 0);
	ex1.AddReps(10);
	vector<int> vec{ 10 };
	REQUIRE(ex1.GetReps().size() == 1);
	REQUIRE(ex1.GetReps()[0] == 10);
	REQUIRE(ex1.GetReps() == vec);
}

TEST_CASE("Exercise Weights") {
	REQUIRE(ex1.GetWeights().size() == 0);
	ex1.AddWeight(10);
	vector<int> vec{ 10 };
	REQUIRE(ex1.GetWeights().size() == 1);
	REQUIRE(ex1.GetWeights()[0] == 10);
	REQUIRE(ex1.GetWeights() == vec);
}


//----------------------------------Tests for WorkoutPlan-----------------------------
//--------------------Tests for Getters/Setters-------------------------------------
TEST_CASE("Workout Plan Get/Set Name") {
	vector<Exercise> vec;
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetName() == "name");
	w1.SetName("new name");
	REQUIRE(w1.GetName() == "new name");
}

TEST_CASE("Workout Plan Get Exercises") {
	Exercise ex1 = Exercise("a", "none");
	Exercise ex2 = Exercise("b", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetExercises().size() == 2);
	REQUIRE(w1.GetExercises()[0].GetName() == "a");
}

TEST_CASE("Workout Plan Set Exercises") {
	Exercise ex1 = Exercise("a", "none");
	Exercise ex2 = Exercise("b", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);

	REQUIRE(w1.GetExercises().size() == 2);
	vec.pop_back();

	//Test that w1's exercise list isn't tied to vec
	REQUIRE(w1.GetExercises().size() == 2);

	//Set w1's exercises
	w1.SetExercises(vec);
	REQUIRE(w1.GetExercises().size() == 1);
	REQUIRE(w1.GetExercises()[0].GetName() == "a");
}

//-----------------------------Tests for ContainsExercise--------------------------
TEST_CASE("Workout Plan Does Contain Exercise") {
	Exercise ex1 = Exercise("a", "none");
	Exercise ex2 = Exercise("b", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.ContainsExercise("a"));
	REQUIRE(w1.ContainsExercise("b"));
}

TEST_CASE("Workout Plan Doesn't Contain Exercise") {
	Exercise ex1 = Exercise("a", "none");
	Exercise ex2 = Exercise("b", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(!w1.ContainsExercise("c"));
}

TEST_CASE("Workout Plan Has No Exercises") {
	vector<Exercise> vec;
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(!w1.ContainsExercise("c"));
}