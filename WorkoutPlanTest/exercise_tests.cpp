//Tests for workout_plan 4-15-19
//Created by Rose Dinh 

#include "../126_final_project/src/exercise.h"
#include "../126_final_project/src/workout_plan.h"
#include "../126_final_project/src/library.h"
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

Exercise ex1 = Exercise("name", "muscle", "equipment");

//-----------------------------Tests for Exercises------------------------------
TEST_CASE("Exercise Constructor") {
	REQUIRE(ex1.GetName() == "name");
	REQUIRE(ex1.GetEquipment() == "equipment");
	REQUIRE(ex1.GetMuscle() == "muscle");
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