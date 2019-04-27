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

//Got text pop up from https://forum.openframeworks.cc/t/workaround-ofxgui-text-input/19630/3

//--------------------------------------------------------------
void ofApp::setup(){
	
	//Setup data
	Parser parser = Parser();
	exercises_ = parser.ReadExercises();
	library_ = Library(&workout_plans_, &exercises_);

	//Set window size and position
	ofSetWindowPosition(0, 0);
	int width = ofGetScreenWidth() * .9;
	int height = ofGetScreenHeight() * .9;
	
	ofSetWindowShape(width, height);
	ofSetWindowPosition((ofGetScreenWidth() / 2) - (width / 2), 0);

	//Title
	title_ = new ofxDatGuiLabel("Workout Planner");
	title_->setPosition(ofGetScreenWidth() / 3, 0);
	title_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	title_->setBackgroundColor(ofColor::blueSteel);
	title_->setLabelColor(ofColor::floralWhite);
	title_->setStripeVisible(false);

	SetupGui();

	SetupSeeLibrary();

	SetupSearchForExercise();

	SetupCreateWorkout();

}

void ofApp::SetupGui() {
	//Create 3 gui's, one column for each function
	guiSeeLibrary = new ofxDatGui();
	guiSeeLibrary->setPosition(kFirstWidth, kFirstHeight);
	guiSeeLibrary->setTheme(new ofxDatGuiThemeAqua);

	guiSearchForExercise = new ofxDatGui();
	guiSearchForExercise->setTheme(new ofxDatGuiThemeAqua);
	guiSearchForExercise->setPosition(kFirstWidth + guiSeeLibrary->getWidth() + kHorizontalBreak,
											kFirstHeight);

	guiCreateWorkout = new ofxDatGui();
	guiCreateWorkout->setTheme(new ofxDatGuiThemeAqua);
	guiCreateWorkout->setPosition(kFirstWidth + guiSeeLibrary->getWidth() +
		guiSearchForExercise->getWidth() + 2 * kHorizontalBreak, kFirstHeight);
}

void ofApp::SetupSeeLibrary() {
	//Set up see library folder, button, text inputs
	ofxDatGuiFolder* see_library_folder_ =
		guiSeeLibrary->addFolder("Search Library for Workout Plans", ofColor::white);
	ofxDatGuiButton* see_whole_library_ = see_library_folder_->addButton("See All Workout Plans");
	guiSeeLibrary->onButtonEvent(this, &ofApp::onButtonSeeLibrary);
	ofxDatGuiTextInput* library_workout_name_ = see_library_folder_->addTextInput("Workout Name", "");
	ofxDatGuiTextInput* library_exercise_name_ = see_library_folder_->addTextInput("Exercise Name", "");
	library_workout_name_->onTextInputEvent(this, &ofApp::onTextSeeLibrary);
	library_exercise_name_->onTextInputEvent(this, &ofApp::onTextSeeLibrary);

	//Scroll views for library searching
	scroll_see_library_ = new ofxDatGuiScrollView("Library of Workouts", 5);
	scroll_see_library_->setPosition(kFirstWidth, kFirstHeight + 4 * guiSeeLibrary->getHeight() 
																				+ kVerticalBreak);
	scroll_see_library_->onScrollViewEvent(this, &ofApp::onScrollSeeLibrary);
	scroll_see_library_->setBackgroundColor(ofColor::lightGray);

	scroll_see_workout_ = new ofxDatGuiScrollView("Workouts", kScrollViewElements);
	scroll_see_workout_->setPosition(kFirstWidth, kFirstHeight + 4 * guiSeeLibrary->getHeight()
		+ scroll_see_library_->getHeight() + 2 * kVerticalBreak);
	scroll_see_workout_->setBackgroundColor(ofColor::lightGray);
}

void ofApp::SetupSearchForExercise() {
	//Set up search for exercise function
	ofxDatGuiFolder* folder_search_ = guiSearchForExercise->addFolder("Search Library for Exercises",
		ofColor::white);
	ofxDatGuiTextInput* exercise_name_ = folder_search_->addTextInput("Exercise Name", "");
	ofxDatGuiTextInput* muscle_name_ = folder_search_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* equipment_name_ = folder_search_->addTextInput("Equipment Name", "");
	exercise_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);
	muscle_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);
	equipment_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);

	//Scroll view for search for exercises
	scroll_search_exercises_ = new ofxDatGuiScrollView("Exercises", kScrollViewElements);
	scroll_search_exercises_->setPosition(kFirstWidth + guiSeeLibrary->getWidth() + kHorizontalBreak,
		kFirstHeight + 4 * guiSearchForExercise->getHeight() + kVerticalBreak);
	scroll_search_exercises_->setBackgroundColor(ofColor::lightGray);
}

void ofApp::SetupCreateWorkout() {
	//Set up create workout function
	ofxDatGuiFolder* folder_create_workout_ = guiCreateWorkout->addFolder("Create Workout Plan",
		ofColor::red);
	ofxDatGuiTextInput* workout_name_ = folder_create_workout_->addTextInput("Workout Plan Name", "");
	workout_name_->onTextInputEvent(this, &ofApp::onTextCreateWorkout);
	ofxDatGuiButton* done_create_workout_ = folder_create_workout_->addButton("Done Creating/Editing Workout");
	guiCreateWorkout->onButtonEvent(this, &ofApp::onButtonDoneCreateWorkout);

	ofxDatGuiTextInput* create_exercise_name_ = folder_create_workout_->addTextInput("Exercise Name", "");
	ofxDatGuiTextInput* create_muscle_name_ = folder_create_workout_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* create_equipment_name_ = folder_create_workout_->addTextInput("Equipment Name", "");
	create_exercise_name_->onTextInputEvent(this, &ofApp::onTextCreateWorkout);
	create_muscle_name_->onTextInputEvent(this, &ofApp::onTextCreateWorkout);
	create_equipment_name_->onTextInputEvent(this, &ofApp::onTextCreateWorkout);

	//Scroll view for selecting exercises
	scroll_select_exercises_ = new ofxDatGuiScrollView("Exercises", kScrollViewElements);
	scroll_select_exercises_->setPosition(kFirstWidth + guiSeeLibrary->getWidth() +
		guiSearchForExercise->getWidth() + 2 * kHorizontalBreak,
		kFirstHeight + 6 * guiSearchForExercise->getHeight() + kVerticalBreak);
	scroll_select_exercises_->onScrollViewEvent(this, &ofApp::onScrollAddExerciseToWorkout);
	scroll_select_exercises_->setBackgroundColor(ofColor::lightGray);

	//Scroll view for editing workout
	scroll_edit_plan_ = new ofxDatGuiScrollView("Exercises of Workout", kScrollViewElements);
	scroll_edit_plan_->setPosition(kFirstWidth + guiSeeLibrary->getWidth() +
		guiSearchForExercise->getWidth() + 2 * kHorizontalBreak,
		kFirstHeight + 18 * guiSearchForExercise->getHeight() + kVerticalBreak);
	scroll_edit_plan_->onScrollViewEvent(this, &ofApp::onScrollRemoveExerciseFromWorkout);
	scroll_edit_plan_->setBackgroundColor(ofColor::black);
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


void ofApp::onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	vector<Exercise> exercises = library_.SearchForExercisesByName(exercise_name);
	Exercise* exercise = &exercises[0];
	current_workout.AddExercise(*exercise);
}

void ofApp::onScrollRemoveExerciseFromWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	current_workout.RemoveExercise(exercise_name);
	std::cout << exercise_name << std::endl;
	std::cout << current_workout.GetExercises().size() << std::endl;
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


void ofApp::onTextCreateWorkout(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Plan Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		if (results.size() == 0) {
			vector<Exercise> empty_exercises{};
			current_workout = WorkoutPlan(e.text, empty_exercises);
		} else {
			current_workout = results[0];
			scroll_edit_plan_->clear();
			scroll_edit_plan_->add("Exercises in this Workout");
			for (int i = 0; i < current_workout.GetExercises().size(); i++) {
				scroll_edit_plan_->add(current_workout.GetExercises()[i].GetName());
				scroll_edit_plan_->add("		Muscle: " + current_workout.GetExercises()[i].GetMuscle());
				scroll_edit_plan_->add("		Equipment: " + current_workout.GetExercises()[i].GetEquipment());
			}
		}
		//new_workout_exercises.clear();
	} else if (e.target->is("Exercise Name")) {
		SearchForExerciseByName(e.text, scroll_select_exercises_);
	} else if (e.target->is("Muscle Name")) {
		SearchForExerciseByMuscle(e.text, scroll_select_exercises_);
	} else if (e.target->is("Equipment Name")) {
		SearchForExerciseByEquipment(e.text, scroll_select_exercises_);
	}
}









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



void ofApp::CreateWorkout(std::string name) {
	Exercise ex1 = (*library_.GetAllExercises())[0];
	Exercise ex2 = (*library_.GetAllExercises())[1];
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan(name, vec);
	library_.AddWorkoutPlan(w1);
}


void ofApp::onButtonDoneCreateWorkout(ofxDatGuiButtonEvent e) {
	if (e.target->is("Done Creating/Editing Workout")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(current_workout.GetName());
		if (results.size() == 0) {
			library_.AddWorkoutPlan(current_workout);
		} else {
			library_.RemoveWorkoutPlan(current_workout.GetName());
			library_.AddWorkoutPlan(current_workout);
		}
		scroll_select_exercises_->clear();
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






