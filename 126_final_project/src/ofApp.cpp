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
	
	Parser parser = Parser();
	exercises_ = parser.ReadExercises();
	library_ = Library(&workout_plans_, &exercises_);

	ofSetWindowPosition(0, 0);

	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	gui->setTheme(new ofxDatGuiThemeMidnight);
	/*gui->addButton("Create Workout Plan");
	gui->addButton("Search For Exercises");*/

	gui->addHeader(":: drag me to reposition ::");

	ofxDatGuiButton* see_library_ = gui->addButton("See Library of Workout Plans");
	see_library_->setPosition(1700, 1700);
	gui->onButtonEvent(this, &ofApp::onButtonEvent);

	gui->addBreak()->setHeight(900.0f);

	ofxDatGuiFolder* folder_search_ = gui->addFolder("Search for Exercises", ofColor::white);
	folder_search_->setWidth(1700, 1350);
	ofxDatGuiTextInput* exercise_name_ = folder_search_->addTextInput("Exercise Name", "");
	exercise_name_->setWidth(1700, 1350);
	ofxDatGuiTextInput* muscle_name_ = folder_search_->addTextInput("Muscle Name", "");
	ofxDatGuiTextInput* equipment_name_ = folder_search_->addTextInput("Equipment Name", "");
	exercise_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);
	muscle_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);
	equipment_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);

	gui->addBreak()->setHeight(900.0f);

	ofxDatGuiFolder* folder_create_workout_ = gui->addFolder("Create Workout Plan", ofColor::red);
	ofxDatGuiTextInput* workout_name_ = folder_create_workout_->addTextInput("Workout Plan Name", "");
	workout_name_->onTextInputEvent(this, &ofApp::onTextInputEvent);

	
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::lightGray);

	ofSetHexColor(0x00FF00);

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
	std::stringstream ss;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i].GetName() << std::endl;
	}
}

void ofApp::SearchForExerciseByMuscle(string input) {
	vector<Exercise> results = library_.SearchForExercisesByMuscle(input);
	std::stringstream ss;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i].GetName() << std::endl;
	}
}

void ofApp::SearchForExerciseByEquipment(string input) {
	vector<Exercise> results = library_.SearchForExercisesByEquipment(input);
	std::stringstream ss;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i].GetName() << std::endl;
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














//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
