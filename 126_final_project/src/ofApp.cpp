#include "ofApp.h"
#include "parser.h"
#include "exercise.h"
#include "library.h"
#include "workout_plan.h"
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;


//--------------------------------------------------------------
void ofApp::setup(){
	
	//Setup data
	Parser parser = Parser();
	exercises_ = parser.ReadExercises();
	library_ = Library(&workout_plans_, &exercises_);

	//Set window size and position
	ofSetWindowPosition(0, 0);
	int width = ofGetScreenWidth();
	int height = ofGetScreenHeight();
	
	ofSetWindowShape(width, height);
	ofSetWindowPosition((ofGetScreenWidth() / 2) - (width / 2), 0);

	//Title
	title_ = new ofxDatGuiLabel("Workout Planner");
	title_->setPosition(ofGetScreenWidth() / 2 - title_->getWidth() / 2, 0);
	title_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	title_->setBackgroundColor(ofColor::blueSteel);
	title_->setLabelColor(ofColor::floralWhite);
	title_->setStripeVisible(false);

	SetupGui();

	SetupCreateWorkout();

	SetupSeeLibrary();

	SetupSearchForExercise();

}

void ofApp::SetupGui() {

	first_column_x_ = kFirstWidth;

	//Create 3 gui's, one column for each function
	guiCreateWorkout = new ofxDatGui();
	guiCreateWorkout->setTheme(new ofxDatGuiThemeAqua);
	guiCreateWorkout->setPosition(first_column_x_, kFirstHeight);
	//guiCreateWorkout->setWidth(300);

	second_column_x_ = first_column_x_ + guiCreateWorkout->getWidth() + kHorizontalBreak;

	guiSeeLibrary = new ofxDatGui();
	guiSeeLibrary->setPosition(second_column_x_, kFirstHeight);
	guiSeeLibrary->setTheme(new ofxDatGuiThemeAqua);

	third_column_x_ = second_column_x_ + guiSeeLibrary->getWidth() + kHorizontalBreak;

	guiSearchForExercise = new ofxDatGui();
	guiSearchForExercise->setTheme(new ofxDatGuiThemeAqua);
	guiSearchForExercise->setPosition(third_column_x_, kFirstHeight);

	

}

void ofApp::SetupSeeLibrary() {
	
	//Set up see library folder, button, text inputs
	ofxDatGuiFolder* see_library_folder_ =
									guiSeeLibrary->addFolder("Search Library for Workout Plans");

	ofxDatGuiButton* see_whole_library_ = see_library_folder_->addButton("See All Workout Plans");
	guiSeeLibrary->onButtonEvent(this, &ofApp::onButtonSeeLibrary);

	ofxDatGuiTextInput* library_workout_name_ = see_library_folder_->
																addTextInput("Workout Name", "");
	ofxDatGuiTextInput* library_exercise_name_ = see_library_folder_->
																addTextInput("Exercise Name", "");
	guiSeeLibrary->onTextInputEvent(this, &ofApp::onTextSeeLibrary);

	//Scroll views for library searching
	scroll_see_library_ = new ofxDatGuiScrollView("Library of Workouts", kScrollLibrary);
	scroll_see_library_->setPosition(second_column_x_, kFirstHeight 
							+ kGuiSeeLibraryHeight * guiSeeLibrary->getHeight() + kVerticalBreak);
	scroll_see_library_->onScrollViewEvent(this, &ofApp::onScrollSeeLibrary);
	scroll_see_library_->setBackgroundColor(background_color_);

	scroll_see_workout_ = new ofxDatGuiScrollView("Workouts", kScrollViewElements);
	scroll_see_workout_->setPosition(second_column_x_, kFirstHeight 
							+ kGuiSeeLibraryHeight * guiSeeLibrary->getHeight()	
							+ scroll_see_library_->getHeight() + 2 * kVerticalBreak);
	scroll_see_workout_->setBackgroundColor(background_color_);
}

void ofApp::SetupSearchForExercise() {
	
	//Set up search for exercise function
	ofxDatGuiFolder* folder_search_ = guiSearchForExercise->
														addFolder("Search Library for Exercises");
	ofxDatGuiTextInput* exercise_name_ = folder_search_->addTextInput("Exercise Name", "");
	ofxDatGuiTextInput* muscle_name_ = folder_search_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* equipment_name_ = folder_search_->addTextInput("Equipment Name", "");
	guiSearchForExercise->onTextInputEvent(this, &ofApp::onTextSearchExercise);

	//Scroll view for search for exercises
	scroll_search_exercises_ = new ofxDatGuiScrollView("Exercises", kScrollViewElements);
	scroll_search_exercises_->setPosition(third_column_x_, kFirstHeight 
				+ kGuiSearchForExerciseHeight * guiSearchForExercise->getHeight() + kVerticalBreak);
	scroll_search_exercises_->setBackgroundColor(background_color_);
}

void ofApp::SetupCreateWorkout() {
	

	//Set up create workout function
	ofxDatGuiFolder* folder_create_workout_ = guiCreateWorkout->
														addFolder("Create/Edit Workout Plan");
	ofxDatGuiTextInput* workout_name_ = folder_create_workout_->
															addTextInput("Workout Plan Name", "");

	//Buttons
	ofxDatGuiButton* delete_workout_ = folder_create_workout_->addButton("Delete Workout");
	ofxDatGuiButton* done_create_workout_ = folder_create_workout_->
													addButton("Done Creating/Editing Workout");

	//Text input
	ofxDatGuiTextInput* create_exercise_name_ = folder_create_workout_->
															addTextInput("Exercise Name", "");
	ofxDatGuiTextInput* create_muscle_name_ = folder_create_workout_->
															addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* create_equipment_name_ = folder_create_workout_->
															addTextInput("Equipment Name", "");

	//Set events
	guiCreateWorkout->onButtonEvent(this, &ofApp::onButtonCreateWorkout);
	guiCreateWorkout->onTextInputEvent(this, &ofApp::onTextCreateWorkout);

	//Scroll view for selecting exercises
	scroll_select_exercises_ = new ofxDatGuiScrollView("Exercises", kScrollViewElements);
	scroll_select_exercises_->setPosition(first_column_x_, kFirstHeight 
						+ kGuiCreateWorkoutHeight * guiCreateWorkout->getHeight() + kVerticalBreak);
	scroll_select_exercises_->onScrollViewEvent(this, &ofApp::onScrollAddExerciseToWorkout);
	scroll_select_exercises_->setBackgroundColor(background_color_);

	//Scroll view for editing workout
	scroll_edit_plan_ = new ofxDatGuiScrollView("Exercises of Workout", kScrollViewElements);
	scroll_edit_plan_->setPosition(first_column_x_, kFirstHeight 
				+ (kGuiCreateWorkoutHeight + kScrollViewElements) * guiCreateWorkout->getHeight() 
				+ kVerticalBreak);
	scroll_edit_plan_->onScrollViewEvent(this, &ofApp::onScrollRemoveExerciseFromWorkout);
	scroll_edit_plan_->setBackgroundColor(background_color_);
}

//--------------------------------------------------------------
void ofApp::update(){
	scroll_search_exercises_->update();
	scroll_see_library_->update();
	scroll_see_workout_->update();
	scroll_select_exercises_->update();
	scroll_edit_plan_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::lightGray);

	ofSetHexColor(0x00FF00);
	title_->draw();
	scroll_search_exercises_->draw();
	scroll_see_library_->draw();
	scroll_see_workout_->draw();
	scroll_select_exercises_->draw();
	scroll_edit_plan_->draw();
}





//Methods for Creating/Editing Workout
void ofApp::onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	vector<Exercise> exercises = library_.SearchForExercisesByName(exercise_name);
	Exercise* exercise = &exercises[0];
	current_workout.AddExercise(*exercise);
}

void ofApp::onScrollRemoveExerciseFromWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	current_workout.RemoveExercise(exercise_name);
}

void ofApp::onTextCreateWorkout(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Plan Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		if (results.size() == 0) {
			vector<Exercise> empty_exercises{};
			current_workout = WorkoutPlan(e.text, empty_exercises);
		} else {
			current_workout = results[0];
			scroll_edit_plan_->clear();
			UpdateScrollEditPlan();
		}
	} else if (e.target->is("Exercise Name")) {
		SearchForExerciseByName(e.text, scroll_select_exercises_);
	} else if (e.target->is("Muscle Name")) {
		SearchForExerciseByMuscle(e.text, scroll_select_exercises_);
	} else if (e.target->is("Equipment Name")) {
		SearchForExerciseByEquipment(e.text, scroll_select_exercises_);
	}
}

void ofApp::UpdateScrollEditPlan() {
	scroll_edit_plan_->add("Exercises in this Workout");
	scroll_edit_plan_->add("Click Exercise to Remove");
	for (int i = 0; i < current_workout.GetExercises().size(); i++) {
		scroll_edit_plan_->add(current_workout.GetExercises()[i].GetName());
		scroll_edit_plan_->add("		Muscle: " + current_workout.GetExercises()[i].GetMuscle());
		scroll_edit_plan_->add("		Equipment: " 
											+ current_workout.GetExercises()[i].GetEquipment());
	}
}

void ofApp::onButtonCreateWorkout(ofxDatGuiButtonEvent e) {
	if (e.target->is("Done Creating/Editing Workout")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(current_workout.GetName());
		if (results.size() == 0) {
			library_.AddWorkoutPlan(current_workout);
		} else {
			library_.RemoveWorkoutPlan(current_workout.GetName());
			library_.AddWorkoutPlan(current_workout);
		}
		scroll_select_exercises_->clear();
		scroll_edit_plan_->clear();
	} else if (e.target->is("Delete Workout")) {
		library_.RemoveWorkoutPlan(current_workout.GetName());
		scroll_select_exercises_->clear();
		scroll_edit_plan_->clear();
	}
}





//Methods for searching for exercise

void ofApp::SearchForExerciseByName(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByName(input);
	scroll->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll->add(results[i].GetName());
		scroll->add("		Muscle: " + results[i].GetMuscle());
		scroll->add("		Equipment: " + results[i].GetEquipment());
	}

}

void ofApp::SearchForExerciseByMuscle(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByMuscle(input);
	scroll->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll->add(results[i].GetName());
		scroll->add("		Muscle: " + results[i].GetMuscle());
		scroll->add("		Equipment: " + results[i].GetEquipment());
	}
}

void ofApp::SearchForExerciseByEquipment(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByEquipment(input);
	scroll->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll->add(results[i].GetName());
		scroll->add("		Muscle: " + results[i].GetMuscle());
		scroll->add("		Equipment: " + results[i].GetEquipment());
	}
}

void ofApp::onTextSearchExercise(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Exercise Name")) {
		SearchForExerciseByName(e.text, scroll_search_exercises_);
	} else if (e.target->is("Muscle Name")) {
		SearchForExerciseByMuscle(e.text, scroll_search_exercises_);
	} else if (e.target->is("Equipment Name")) {
		SearchForExerciseByEquipment(e.text, scroll_search_exercises_);
	}
}






//Methods for See Library
void ofApp::onButtonSeeLibrary(ofxDatGuiButtonEvent e) {
	if (e.target->is("See All Workout Plans")) {
		vector<WorkoutPlan> results = *library_.GetWorkoutPlans();
		scroll_see_library_->clear();
		scroll_see_workout_->clear();

		for (int i = 0; i < results.size(); i++) {
			scroll_see_library_->add(results[i].GetName());
		}
	}
}

void ofApp::onTextSeeLibrary(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		scroll_see_workout_->clear();
		scroll_see_library_->clear();
		for (int i = 0; i < results.size(); i++) {
			scroll_see_library_->add(results[i].GetName());
		}
	} else if (e.target->is("Exercise Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByExercise(e.text);
		scroll_see_workout_->clear();
		scroll_see_library_->clear();
		for (int i = 0; i < results.size(); i++) {
			scroll_see_library_->add(results[i].GetName());
		}
	}
}

void ofApp::onScrollSeeLibrary(ofxDatGuiScrollViewEvent e) {
	scroll_see_workout_->clear();
	scroll_see_workout_->add("Exercises");
	std::string workout_name = e.target->getLabel();
	vector<WorkoutPlan> workout = library_.SearchForPlanByName(workout_name);
	vector<Exercise> results = workout[0].GetExercises();
	for (int i = 0; i < results.size(); i++) {
		scroll_see_workout_->add("	" + results[i].GetName());
		scroll_see_workout_->add("		Muscle: " + results[i].GetMuscle());
		scroll_see_workout_->add("		Equipment: " + results[i].GetEquipment());
	}

}






