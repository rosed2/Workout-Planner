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

		//Methods for searching for an exercise
		void SearchForExerciseByName(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByMuscle(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByEquipment(std::string, ofxDatGuiScrollView*);
		void onTextSearchExercise(ofxDatGuiTextInputEvent e);

		//Methods for searching library for workouts
		void onButtonSeeLibrary(ofxDatGuiButtonEvent e);		
		void onTextSeeLibrary(ofxDatGuiTextInputEvent e);
		void onScrollSeeLibrary(ofxDatGuiScrollViewEvent e);


		//Methods for creating workout
		void onTextCreateWorkout(ofxDatGuiTextInputEvent e);
		void onButtonCreateWorkout(ofxDatGuiButtonEvent e);
		void onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e);
		void onScrollRemoveExerciseFromWorkout(ofxDatGuiScrollViewEvent e);
		void UpdateScrollEditPlan();

private:
	Library library_;
	std::vector<Exercise> exercises_;
	std::vector<WorkoutPlan> workout_plans_;
	WorkoutPlan current_workout;

	ofxDatGuiLabel* title_;
	ofxDatGui* guiSeeLibrary;
	ofxDatGui* guiSearchForExercise;
	ofxDatGui* guiCreateWorkout;

	ofxDatGuiScrollView* scroll_search_exercises_;

	ofxDatGuiScrollView* scroll_see_library_;
	ofxDatGuiScrollView* scroll_see_workout_;

	ofxDatGuiScrollView* scroll_select_exercises_;
	ofxDatGuiScrollView* scroll_edit_plan_;

	const int kFirstHeight = 40;
	const int kFirstWidth = 275;
	//const int kFirstWidth = 0;
	const int kHorizontalBreak = 10;
	const int kVerticalBreak = 10;
	const int kScrollViewElements = 12;
	const int kScrollLibrary = 5;

	const int kGuiSeeLibraryHeight = 4;
	const int kGuiSearchForExerciseHeight = 4;
	const int kGuiCreateWorkoutHeight = 7;

	int first_column_x_;
	int second_column_x_;
	int third_column_x_;

	ofColor background_color_ = ofColor::lightGray;
};
