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
	const int kFirstWidth = 180;
	const int kHorizontalBreak = 10;
	const int kVerticalBreak = 10;
	const int kScrollViewElements = 12;
	const int kScreenRatio = .9;
	const int kColumns = 3;
	const int kScrollLibrary = 5;
};
