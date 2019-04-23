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
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void SeeLibraryButtonPressed();

		void SearchForExerciseByName(std::string);
		void SearchForExerciseByMuscle(std::string);
		void SearchForExerciseByEquipment(std::string);

		void CreateWorkout(std::string);
		
		Library library_;
		std::vector<Exercise> exercises_;
		std::vector<WorkoutPlan> workout_plans_;


		ofxDatGui* gui;
		void onButtonEvent(ofxDatGuiButtonEvent e);
		void onTextInputEvent(ofxDatGuiTextInputEvent e);
};
