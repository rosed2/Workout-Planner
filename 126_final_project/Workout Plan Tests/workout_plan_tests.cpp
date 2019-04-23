//Tests for workout_plan 4-15-19
//Created by Rose Dinh 

#include "../src/exercise.h"
#include "../src/workout_plan.h"

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

Exercise ex1 = Exercise("name", "arm", "equipment");


//----------------------------------Tests for WorkoutPlan-----------------------------
//------------------Tests for Getters/Setters------------------------
TEST_CASE("Workout Plan Get/Set Name") {
	vector<Exercise> vec;
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetName() == "name");
	w1.SetName("new name");
	REQUIRE(w1.GetName() == "new name");
}

TEST_CASE("Workout Plan Get Exercises") {
	Exercise ex1 = Exercise("a", "arm", "none");
	Exercise ex2 = Exercise("b", "leg", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetExercises().size() == 2);
	REQUIRE(w1.GetExercises()[0].GetName() == "a");
}

TEST_CASE("Workout Plan Set Exercises") {
	Exercise ex1 = Exercise("a", "arm", "none");
	Exercise ex2 = Exercise("b", "leg", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };

	WorkoutPlan w1 = WorkoutPlan("name", vec);

	REQUIRE(w1.GetExercises().size() == 2);
	vec.pop_back();

	//Set w1's exercises
	w1.SetExercises(vec);
	REQUIRE(w1.GetExercises().size() == 1);
	REQUIRE(w1.GetExercises()[0].GetName() == "a");
}

//-----------------------Tests for ContainsExercise--------------------
TEST_CASE("Workout Plan Does Contain Exercise") {
	Exercise ex1 = Exercise("Exercise 1", "arm", "none");
	Exercise ex2 = Exercise("Exercise 2", "leg", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);

	REQUIRE(w1.ContainsExercise("1"));
	REQUIRE(w1.ContainsExercise("exercise 1"));
	REQUIRE(w1.ContainsExercise("Exercise 1"));
	REQUIRE(w1.GetExercises()[0].GetName() == "Exercise 1");
}

TEST_CASE("Workout Plan Doesn't Contain Exercise") {
	Exercise ex1 = Exercise("a", "arm", "none");
	Exercise ex2 = Exercise("b", "leg", "dumbbells");
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(!w1.ContainsExercise("c"));
}

TEST_CASE("Workout Plan Has No Exercises") {
	vector<Exercise> vec;
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(!w1.ContainsExercise("c"));
}

//-------------------Tests for AddExercise-----------
TEST_CASE("Workout Plan Add Exercise to Empty") {
	vector<Exercise> vec;
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetExercises().size() == 0);
	Exercise ex1 = Exercise("exer", "arm", "none");
	w1.AddExercise(ex1);
	REQUIRE(w1.GetExercises().size() == 1);
	REQUIRE(w1.GetExercises()[0].GetName() == "exer");
}

TEST_CASE("Workout Plan Add Exercise") {
	Exercise ex0 = Exercise("exer1", "arm", "none");
	vector<Exercise> vec{ ex0 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
	REQUIRE(w1.GetExercises().size() == 1);
	Exercise ex1 = Exercise("exer", "arm", "none");
	w1.AddExercise(ex1);
	REQUIRE(w1.GetExercises().size() == 2);
}



