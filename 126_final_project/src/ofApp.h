#pragma once

#include "ofMain.h"
#include "exercise.h"
#include "ofxDatGui.h"
#include "library.h"
#include "workout_plan.h"
#include "day.h"
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
		void SetupDays();

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

		//Methods for weekly planner
		void onDropdownDay(ofxDatGuiDropdownEvent e);
		void onButtonDaySeeLibrary(ofxDatGuiButtonEvent e);
		void onTextDaySelectWorkout(ofxDatGuiTextInputEvent e);
		void onScrollDaySelectWorkout(ofxDatGuiScrollViewEvent e);
		void onScrollDayAddWorkout(ofxDatGuiScrollViewEvent e);
		void onScrollDayRemoveWorkout(ofxDatGuiScrollViewEvent e);
		void UpdateScrollDaySeeDay();


private:
	Library library_;
	std::vector<Exercise> exercises_;
	std::vector<WorkoutPlan> workout_plans_;
	WorkoutPlan current_workout_;
	WorkoutPlan selected_workout_;

	std::vector<Day> days_;
	Day* current_day_;

	ofxDatGuiLabel* title_;
	ofxDatGui* guiSeeLibrary;
	ofxDatGui* guiSearchForExercise;
	ofxDatGui* guiCreateWorkout;
	ofxDatGui* guiDays;

	ofxDatGuiScrollView* scroll_search_exercises_;

	ofxDatGuiScrollView* scroll_see_library_;
	ofxDatGuiScrollView* scroll_see_workout_;

	ofxDatGuiScrollView* scroll_select_exercises_;
	ofxDatGuiScrollView* scroll_edit_plan_;

	ofxDatGuiScrollView* scroll_day_select_workout_;
	ofxDatGuiScrollView* scroll_day_add_workout_;
	ofxDatGuiScrollView* scroll_day_see_day_;

	const int kFirstHeight = 40;
	//const int kFirstWidth = 275;
	const int kFirstWidth = 45;
	const int kHorizontalBreak = 10;
	const int kVerticalBreak = 10;
	const int kScrollViewElements = 12;
	const int kSearchExerciseScrollHeight = 18;
	const int kScrollLibrary = 5;

	const int kGuiSeeLibraryHeight = 4;
	const int kGuiSearchForExerciseHeight = 4;
	const int kGuiCreateWorkoutHeight = 7;

	int first_column_x_;
	int second_column_x_;
	int third_column_x_;
	int fourth_column_x_;

	ofColor background_color_ = ofColor::red;
};
