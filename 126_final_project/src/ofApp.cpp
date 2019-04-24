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

	//Create gui
	guiSeeLibrary = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	guiSeeLibrary->setTheme(new ofxDatGuiThemeAqua);

	guiSearchForExercise = new ofxDatGui();
	guiSearchForExercise->setTheme(new ofxDatGuiThemeAqua);
	guiSearchForExercise->setPosition(guiSeeLibrary->getWidth() + 10, 0);

	guiCreateWorkout = new ofxDatGui();
	guiCreateWorkout->setTheme(new ofxDatGuiThemeAqua);
	guiCreateWorkout->setPosition(guiSeeLibrary->getWidth() + guiSearchForExercise->getWidth() + 20, 0);
	/*gui->addButton("Create Workout Plan");
	gui->addButton("Search For Exercises");*/


	//Set up see library button
	ofxDatGuiButton* see_library_ = guiSeeLibrary->addButton("See Library of Workout Plans");
	guiSeeLibrary->onButtonEvent(this, &ofApp::onButtonEvent);


	//Set up search for exercise function
	ofxDatGuiFolder* folder_search_ = guiSearchForExercise->addFolder("Search for Exercises", ofColor::white);
	folder_search_->setWidth(1700, 1350);
	ofxDatGuiTextInput* exercise_name_ = folder_search_->addTextInput("Exercise Name", "");
	exercise_name_->setWidth(1700, 1350);
	ofxDatGuiTextInput* muscle_name_ = folder_search_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* equipment_name_ = folder_search_->addTextInput("Equipment Name", "");
	exercise_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);
	muscle_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);
	equipment_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);

	//gui->addBreak()->setHeight(900.0f);

	//Set up create workout function
	ofxDatGuiFolder* folder_create_workout_ = guiCreateWorkout->addFolder("Create Workout Plan", ofColor::red);
	ofxDatGuiTextInput* workout_name_ = folder_create_workout_->addTextInput("Workout Plan Name", "");
	workout_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);

	//Scroll view for search for exercises
	scroll_search_exercises_ = new ofxDatGuiScrollView("Exercises #1", 8);
	scroll_search_exercises_->setPosition(guiSeeLibrary->getWidth() + 10,
		4*guiSearchForExercise->getHeight());
	scroll_search_exercises_->onScrollViewEvent(this, &ofApp::addExerciseToWorkout);

	//Scroll view for library

}

//--------------------------------------------------------------
void ofApp::update(){
	scroll_search_exercises_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::lightGray);

	ofSetHexColor(0x00FF00);
	scroll_search_exercises_->draw();

}


void ofApp::addExerciseToWorkout(ofxDatGuiScrollViewEvent e) {
	if (e.target->is("item 1")) {
		std::cout << "hello" << std::endl;
	}
}


void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->is("See Library of Workout Plans")) {
		SeeLibraryButtonPressed();
	}
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
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


void ofApp::SearchForExerciseByName(string input) {
	vector<Exercise> results = library_.SearchForExercisesByName(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
	}

}

void ofApp::SearchForExerciseByMuscle(string input) {
	vector<Exercise> results = library_.SearchForExercisesByMuscle(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
	}
}

void ofApp::SearchForExerciseByEquipment(string input) {
	vector<Exercise> results = library_.SearchForExercisesByEquipment(input);
	scroll_search_exercises_->clear();

	for (int i = 0; i < results.size(); i++) {
		scroll_search_exercises_->add(results[i].GetName());
	}
}

void ofApp::SeeLibraryButtonPressed() {
	vector<WorkoutPlan> results = *library_.GetWorkoutPlans();
	std::cout << "Total number of workout plans in library: " << results.size() << std::endl;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i] << std::endl;
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
