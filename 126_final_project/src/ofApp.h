#pragma once

#include "ofMain.h"
#include "exercise.h"
#include "ofxDatGui.h"
#include "library.h"
#include "workout_plan.h"
#include <vector>
#include <string>

class ofApp : public ofBaseApp{

	public:
		void setup();

		//Setup helper methods
		void SetupGui();
		void SetupSeeLibrary();
		void SetupSearchForExercise();
		void SetupCreateWorkout();

		void update();
		void draw();

		void SearchForExerciseByName(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByMuscle(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByEquipment(std::string, ofxDatGuiScrollView*);

		
		
		void onButtonSeeLibrary(ofxDatGuiButtonEvent e);
		void onTextSearchExercise(ofxDatGuiTextInputEvent e);

		void onTextCreateWorkout(ofxDatGuiTextInputEvent e);
		void onTextSeeLibrary(ofxDatGuiTextInputEvent e);

		
		void onScrollSeeLibrary(ofxDatGuiScrollViewEvent e);
		

		//Methods for creating workout
		void onButtonDoneCreateWorkout(ofxDatGuiButtonEvent e);
		void CreateWorkout(std::string);
		void onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e);
		void onScrollRemoveExerciseFromWorkout(ofxDatGuiScrollViewEvent e);

		//void onScrollSeeWorkout(ofxDatGuiScrollViewEvent e);
private:
	Library library_;
	std::vector<Exercise> exercises_;
	std::vector<WorkoutPlan> workout_plans_;

	ofxDatGuiLabel* title_;
	ofxDatGui* guiSeeLibrary;
	ofxDatGui* guiSearchForExercise;
	ofxDatGui* guiCreateWorkout;

	ofxDatGuiScrollView* scroll_search_exercises_;

	ofxDatGuiScrollView* scroll_see_library_;
	ofxDatGuiScrollView* scroll_see_workout_;

	ofxDatGuiScrollView* scroll_select_exercises_;
	ofxDatGuiScrollView* scroll_edit_plan_;

	vector<Exercise> new_workout_exercises;
	std::string new_workout_name;
	WorkoutPlan current_workout;

	const int kFirstHeight = 40;
	const int kFirstWidth = 180;
	const int kHorizontalBreak = 10;
	const int kVerticalBreak = 10;
	const int kScrollViewElements = 12;
};
