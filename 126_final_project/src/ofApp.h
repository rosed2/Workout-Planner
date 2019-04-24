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

		/*void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);*/

		void SearchForExerciseByName(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByMuscle(std::string, ofxDatGuiScrollView*);
		void SearchForExerciseByEquipment(std::string, ofxDatGuiScrollView*);

		void CreateWorkout(std::string);
		
		Library library_;
		std::vector<Exercise> exercises_;
		std::vector<WorkoutPlan> workout_plans_;

		ofxDatGuiLabel* title_;
		ofxDatGui* guiSeeLibrary;
		ofxDatGui* guiSearchForExercise;
		ofxDatGui* guiCreateWorkout;
		void onButtonSeeLibrary(ofxDatGuiButtonEvent e);
		void onTextSearchExercise(ofxDatGuiTextInputEvent e);

		void onTextCreateWorkout(ofxDatGuiTextInputEvent e);
		void onTextSeeLibrary(ofxDatGuiTextInputEvent e);

		ofxDatGuiScrollView* scroll_search_exercises_;

		ofxDatGuiScrollView* scroll_see_library_;
		void onScrollSeeLibrary(ofxDatGuiScrollViewEvent e);
		ofxDatGuiScrollView* scroll_see_workout_;

		//Things for creating workout
		void onButtonDoneCreateWorkout(ofxDatGuiButtonEvent e);
		ofxDatGuiScrollView* scroll_select_exercises_;
		void onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e);
		vector<Exercise> new_workout_exercises;
		std::string new_workout_name;

		//void onScrollSeeWorkout(ofxDatGuiScrollViewEvent e);
};
