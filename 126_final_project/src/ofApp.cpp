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
	vector<Exercise> exercises = parser.ReadExercises();
	vector<WorkoutPlan> workouts{};
	library_ = Library(workouts, exercises);

	gui.setup();
	gui.add(create_workout_button_.setup("Create Workout"));
	gui.add(search_for_exercises_button_.setup("Search For Exercises"));
	gui.add(see_library_.setup("See Library of Workout Plans"));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	ofSetHexColor(0x00FF00);

	gui.draw();

	if (create_workout_button_) {
		std::cout << "clicked workout" << std::endl;
		std::string input;
		input = ofSystemTextBoxDialog("Search for Workout Name", input);
		std::cout << input << std::endl;
	} else if (search_for_exercises_button_) {
		std::cout << "clicked search" << std::endl;
		std::string input;
		input = ofSystemTextBoxDialog("Search for Exercises", input);
		vector<Exercise> results = library_.SearchForExercisesByName(input);
		std::stringstream ss;
		for (int i = 0; i < results.size(); i++) {
			ss << results[i].GetName() << std::endl;
		}
		ofDrawBitmapString(ss.str(), 10, 14);
	}

	

	

	

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
