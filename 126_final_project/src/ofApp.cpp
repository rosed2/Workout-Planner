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

	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	gui->addButton("Create Workout Plan");
	gui->addButton("Search For Exercises");
	gui->addButton("See Library of Workout Plans");
	gui->onButtonEvent(this, &ofApp::onButtonEvent);

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	ofSetHexColor(0x00FF00);

	//gui.draw();

}


void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->is("Create Workout Plan")) {
		CreateWorkout();
	} else if (e.target->is("Search for Exercises")) {
		SearchForExerciseByName();
	} else if (e.target->is("See Library of Workout Plans")) {
		SeeLibrary();
	}
}




void ofApp::SearchForExerciseByName() {
	std::string input;

	input = ofSystemTextBoxDialog("Search for Exercises", input);

	vector<Exercise> results = library_.SearchForExercisesByName(input);
	std::stringstream ss;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i].GetName() << std::endl;
	}

	ofDrawBitmapString(ss.str(), 10, 14);
}

void ofApp::SeeLibrary() {
	vector<WorkoutPlan> results = *library_.GetWorkoutPlans();
	std::cout << "Total number of workout plans in library: " << results.size() << std::endl;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i] << std::endl;
	}
}

void ofApp::CreateWorkout() {
	std::string name;
	name = ofSystemTextBoxDialog("Type Workout Plan Name", name);

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
