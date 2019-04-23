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
	
	Parser parser = Parser();
	exercises_ = parser.ReadExercises();
	library_ = Library(&workout_plans_, &exercises_);

	search_for_exercises_button_.addListener(this, &ofApp::SearchForExerciseByName);
	create_workout_button_.addListener(this, &ofApp::CreateWorkout);
	see_library_button_.addListener(this, &ofApp::SeeLibrary);

	gui.setup();
	gui.add(create_workout_button_.setup("Create Workout"));
	gui.add(search_for_exercises_button_.setup("Search For Exercises"));
	gui.add(see_library_button_.setup("See Library of Workout Plans"));
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	ofSetHexColor(0x00FF00);

	gui.draw();

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
	std::cout << results.size() << std::endl;

	for (int i = 0; i < results.size(); i++) {
		std::cout << results[i] << std::endl;
	}
}

void ofApp::CreateWorkout() {
	Exercise ex1 = (*library_.GetAllExercises())[0];
	Exercise ex2 = (*library_.GetAllExercises())[1];
	vector<Exercise> vec{ ex1, ex2 };
	WorkoutPlan w1 = WorkoutPlan("name", vec);
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
