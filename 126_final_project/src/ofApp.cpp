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
	int first_height = 40;
	int first_width = 180;
	ofSetWindowShape(width, height);
	ofSetWindowPosition((ofGetScreenWidth() / 2) - (width / 2), 0);

	//Title
	title_ = new ofxDatGuiLabel("Workout Planner");
	title_->setPosition(ofGetScreenWidth() / 3, 0);
	title_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	title_->setBackgroundColor(ofColor::blueSteel);
	title_->setLabelColor(ofColor::floralWhite);
	title_->setStripeVisible(false);

	//Create gui
	guiSeeLibrary = new ofxDatGui();
	guiSeeLibrary->setPosition(first_width, first_height);
	guiSeeLibrary->setTheme(new ofxDatGuiThemeAqua);

	guiSearchForExercise = new ofxDatGui();
	guiSearchForExercise->setTheme(new ofxDatGuiThemeAqua);
	guiSearchForExercise->setPosition(first_width + guiSeeLibrary->getWidth() + 10, first_height);

	guiCreateWorkout = new ofxDatGui();
	guiCreateWorkout->setTheme(new ofxDatGuiThemeAqua);
	guiCreateWorkout->setPosition(first_width + guiSeeLibrary->getWidth() + 
											guiSearchForExercise->getWidth() + 20, first_height);
	/*gui->addButton("Create Workout Plan");
	gui->addButton("Search For Exercises");*/


	//Set up see library button
	ofxDatGuiFolder* see_library_folder_ = 
		guiSeeLibrary->addFolder("Search Library for Workout Plans", ofColor::white);
	ofxDatGuiButton* see_whole_library_ = see_library_folder_->addButton("See All Workout Plans");
	guiSeeLibrary->onButtonEvent(this, &ofApp::onButtonSeeLibrary);
	ofxDatGuiTextInput* library_workout_name_ = see_library_folder_->addTextInput("Workout Name", "");
	ofxDatGuiTextInput* library_exercise_name_ = see_library_folder_->addTextInput("Exercise Name", "");
	library_workout_name_->onTextInputEvent(this, &ofApp::onTextSeeLibrary);
	library_exercise_name_->onTextInputEvent(this, &ofApp::onTextSeeLibrary);


	//Set up search for exercise function
	ofxDatGuiFolder* folder_search_ = guiSearchForExercise->addFolder("Search Library for Exercises",
																				ofColor::white);
	ofxDatGuiTextInput* exercise_name_ = folder_search_->addTextInput("Exercise Name", "");
	ofxDatGuiTextInput* muscle_name_ = folder_search_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* equipment_name_ = folder_search_->addTextInput("Equipment Name", "");
	exercise_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);
	muscle_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);
	equipment_name_->onTextInputEvent(this, &ofApp::onTextSearchExercise);


	//Set up create workout function
	ofxDatGuiFolder* folder_create_workout_ = guiCreateWorkout->addFolder("Create Workout Plan", 
																				ofColor::red);
	ofxDatGuiTextInput* workout_name_ = folder_create_workout_->addTextInput("Workout Plan Name", "");
	workout_name_->onTextInputEvent(this, &ofApp::onTextCreateWorkout);


	//Scroll view for search for exercises
	scroll_search_exercises_ = new ofxDatGuiScrollView("Exercises", 15);
	scroll_search_exercises_->setPosition(first_width + guiSeeLibrary->getWidth() + 10,
		first_height + 4*guiSearchForExercise->getHeight() + 10);
	scroll_search_exercises_->onScrollViewEvent(this, &ofApp::addExerciseToWorkout);
	scroll_search_exercises_->setBackgroundColor(ofColor::lightGray);


	//Scroll view for library
	scroll_see_library_ = new ofxDatGuiScrollView("Library of Workouts", 8);
	scroll_see_library_->setPosition(first_width, first_height + 4*guiSeeLibrary->getHeight() + 10);
	scroll_see_library_->onScrollViewEvent(this, &ofApp::onScrollSeeLibrary);
	scroll_see_library_->setBackgroundColor(ofColor::lightGray);


	//Scroll view for workouts
	scroll_see_workout_ = new ofxDatGuiScrollView("Workouts", 8);
	scroll_see_workout_->setPosition(first_width, first_height + 4*guiSeeLibrary->getHeight() 
		+ scroll_see_library_->getHeight() + 20);
	scroll_see_workout_->setBackgroundColor(ofColor::lightGray);
}

//--------------------------------------------------------------
void ofApp::update(){
	scroll_search_exercises_->update();
	scroll_see_library_->update();
	scroll_see_workout_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::lightGray);

	ofSetHexColor(0x00FF00);
	title_->draw();
	scroll_search_exercises_->draw();
	scroll_see_library_->draw();
	scroll_see_workout_->draw();
}


void ofApp::addExerciseToWorkout(ofxDatGuiScrollViewEvent e) {
	if (e.target->is("item 1")) {
		std::cout << "hello" << std::endl;
	}
}


void ofApp::onButtonSeeLibrary(ofxDatGuiButtonEvent e) {
	if (e.target->is("See All Workout Plans")) {
		vector<WorkoutPlan> results = *library_.GetWorkoutPlans();
		scroll_see_library_->clear();

		for (int i = 0; i < results.size(); i++) {
			scroll_see_library_->add(results[i].GetName());
		}
	}
}

void ofApp::onTextSearchExercise(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Exercise Name")) {
		SearchForExerciseByName(e.text);
	} else if (e.target->is("Muscle Name")) {
		SearchForExerciseByMuscle(e.text);
	} else if (e.target->is("Equipment Name")) {
		SearchForExerciseByEquipment(e.text);
	} else if (e.target->is("Workout Plan Name")) {
		CreateWorkout(e.text);
	}
}


void ofApp::onTextCreateWorkout(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Plan Name")) {
		CreateWorkout(e.text);
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




void ofApp::SearchForExerciseByName(string input) {
	vector<Exercise> results = library_.SearchForExercisesByName(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
		scroll_search_exercises_->add("		Muscle: " + results[i].GetMuscle());
		scroll_search_exercises_->add("		Equipment: " + results[i].GetEquipment());
	}

}

void ofApp::SearchForExerciseByMuscle(string input) {
	vector<Exercise> results = library_.SearchForExercisesByMuscle(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
		scroll_search_exercises_->add("		Muscle: " + results[i].GetMuscle());
		scroll_search_exercises_->add("		Equipment: " + results[i].GetEquipment());
	}
}

void ofApp::SearchForExerciseByEquipment(string input) {
	vector<Exercise> results = library_.SearchForExercisesByEquipment(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
		scroll_search_exercises_->add("		Muscle: " + results[i].GetMuscle());
		scroll_search_exercises_->add("		Equipment: " + results[i].GetEquipment());
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


void ofApp::CreateWorkout(std::string name) {
	Exercise ex1 = (*library_.GetAllExercises())[0];
	Exercise ex2 = (*library_.GetAllExercises())[1];
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan(name, vec);
	library_.AddWorkoutPlan(w1);
}














////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//	
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}
