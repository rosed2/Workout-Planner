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

//Setup
Exercise ex1 = Exercise("Exercise 1", "bicep", "none");
Exercise ex2 = Exercise("Exercise 2", "bicep", "dumbbells");
Exercise ex3 = Exercise("Exercise 3", "back", "none");

vector<Exercise> all_exercises{ ex1, ex2, ex3 };

vector<Exercise> vec1{ ex1, ex2 };
vector<Exercise> vec2{ ex2, ex3 };
vector<Exercise> vec3{ ex3 };

WorkoutPlan w1 = WorkoutPlan("Plan 1", vec1);
WorkoutPlan w2 = WorkoutPlan("Plan 2", vec2);
WorkoutPlan w3 = WorkoutPlan("Plan 3", vec3);


//---------------------Tests for GetWorkoutPlans----------
TEST_CASE("Library GetWorkoutPlans") {
	vector<WorkoutPlan> work{ w1 };

	Library library = Library(work, all_exercises);
	REQUIRE(library.GetWorkoutPlans().size() == 1);
}

TEST_CASE("Library GetWorkoutPlans Empty") {
	vector<WorkoutPlan> work{ };

	Library library = Library(work, all_exercises);
	REQUIRE(library.GetWorkoutPlans().size() == 0);
}



//--------------------Tests for AddWorkoutPlan---------------
TEST_CASE("Library AddWorkoutPlan") {
	vector<WorkoutPlan> work{ w1 };

	Library library = Library(work, all_exercises);
	REQUIRE(library.GetWorkoutPlans().size() == 1);
	REQUIRE(library.GetWorkoutPlans()[0].GetName() == "Plan 1");

	library.AddWorkoutPlan(w2);
	REQUIRE(library.GetWorkoutPlans().size() == 2);
	REQUIRE(library.GetWorkoutPlans()[1].GetName() == "Plan 2");
}



//--------------------Tests for SearchForPlanByName--------
TEST_CASE("Library SearchForPlanByName Test Case Insensitive") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByName("plA");
	REQUIRE(results.size() == 2);
	REQUIRE(results[0].GetName() == "Plan 1");
	REQUIRE(results[1].GetName() == "Plan 2");
}

TEST_CASE("Library SearchForPlanByName Number") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByName("1");
	REQUIRE(results.size() == 1);
	REQUIRE(results[0].GetName() == "Plan 1");
}

TEST_CASE("Library SearchForPlanByName No Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByName("ze");
	REQUIRE(results.size() == 0);
}



//------------------Tests for SearchForPlanByExercise------------
TEST_CASE("Library SearchForPlanByExercise No Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByExercise("ze");
	REQUIRE(results.size() == 0);
}

TEST_CASE("Library SearchForPlanByExercise Test Case Insensitive") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByExercise("eXEr");
	REQUIRE(results.size() == 2);
}

TEST_CASE("Library SearchForPlanByExercise One Result") {
	vector<WorkoutPlan> work{ w1, w3 };

	Library library = Library(work, all_exercises);

	vector<WorkoutPlan> results = library.SearchForPlanByExercise("3");
	REQUIRE(results.size() == 1);
	REQUIRE(results[0].GetName() == "Plan 3");
}


//------------------Test for GetAllExercises----------
TEST_CASE("GetAllExercises") {
	vector<WorkoutPlan> work{ w1, w3 };
	Library library = Library(work, all_exercises);
	REQUIRE(library.GetAllExercises().size() == 3);
}



//---------------Test for SearchForExercisesByName-------------
TEST_CASE("Library SearchForExerciseByName Test Case Insensitive") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByName("eXErCi");
	REQUIRE(results.size() == 3);
	REQUIRE(results[0].GetName() == "Exercise 1");
	REQUIRE(results[1].GetName() == "Exercise 2");
	REQUIRE(results[2].GetName() == "Exercise 3");
}

TEST_CASE("Library SearchForExerciseByName No Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByName("zbs");
	REQUIRE(results.size() == 0);
}

TEST_CASE("Library SearchForExerciseByName Number") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByName("1");
	REQUIRE(results.size() == 1);
	REQUIRE(results[0].GetName() == "Exercise 1");
}



//---------------Test for SearchForExercisesByMuscle-------------
TEST_CASE("Library SearchForExerciseByMuscle Test Case Insensitive") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByMuscle("bAck");
	REQUIRE(results.size() == 1);
	REQUIRE(results[0].GetName() == "Exercise 3");
}

TEST_CASE("Library SearchForExerciseByMuscle No Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByMuscle("zbs");
	REQUIRE(results.size() == 0);
}

TEST_CASE("Library SearchForExerciseByMuscle 2 Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByMuscle("biCeP");
	REQUIRE(results.size() == 2);
	REQUIRE(results[0].GetName() == "Exercise 1");
	REQUIRE(results[1].GetName() == "Exercise 2");
}



//---------------Test for SearchForExercisesByEquipment-------------
TEST_CASE("Library SearchForExerciseByEquipment Test Case Insensitive") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByEquipment("dumBBell");
	REQUIRE(results.size() == 1);
	REQUIRE(results[0].GetName() == "Exercise 2");
}

TEST_CASE("Library SearchForExerciseByEquipment No Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByEquipment("cable");
	REQUIRE(results.size() == 0);
}

TEST_CASE("Library SearchForExerciseByEquipment 2 Results") {
	vector<WorkoutPlan> work{ w1, w2 };

	Library library = Library(work, all_exercises);

	vector<Exercise> results = library.SearchForExercisesByEquipment("noNe");
	REQUIRE(results.size() == 2);
	REQUIRE(results[0].GetName() == "Exercise 1");
	REQUIRE(results[1].GetName() == "Exercise 3");
}
