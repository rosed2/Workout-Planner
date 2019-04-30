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
//Setup methods
void ofApp::setup(){
	
	//Setup data
	Parser parser = Parser();
	exercises_ = parser.ReadExercises();
	library_ = Library(&workout_plans_, &exercises_);

	//Set window size and position	
	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	ofSetWindowPosition(0, 0);

	SetupTitle();
	
	SetupGui();

	SetupCreateWorkout();

	SetupSeeLibrary();

	SetupSearchForExercise();

	SetupDays();

	SetupClearScrollsButton();
}

void ofApp::SetupTitle() {
	title_ = new ofxDatGuiLabel("Workout Planner");
	title_->setPosition(ofGetScreenWidth() / 2 - title_->getWidth() / 2, 0);
	title_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	title_->setBackgroundColor(ofColor::dodgerBlue);
	title_->setLabelColor(ofColor::floralWhite);
	title_->setStripeVisible(false);
}

void ofApp::SetupGui() {

	first_column_x_ = kFirstWidth;

	//Create 4 gui's, one column for each function
	guiCreateWorkout = new ofxDatGui();
	guiCreateWorkout->setTheme(theme_);
	guiCreateWorkout->setPosition(first_column_x_, kFirstHeight);
	//guiCreateWorkout->setWidth(300);

	second_column_x_ = first_column_x_ + guiCreateWorkout->getWidth() + kHorizontalBreak;

	guiSeeLibrary = new ofxDatGui();
	guiSeeLibrary->setPosition(second_column_x_, kFirstHeight);
	guiSeeLibrary->setTheme(theme_);

	third_column_x_ = second_column_x_ + guiSeeLibrary->getWidth() + kHorizontalBreak;

	guiSearchForExercise = new ofxDatGui();
	guiSearchForExercise->setTheme(theme_);
	guiSearchForExercise->setPosition(third_column_x_, kFirstHeight);

	fourth_column_x_ = third_column_x_ + guiSearchForExercise->getWidth() + kHorizontalBreak;

	guiDays = new ofxDatGui();
	guiDays->setTheme(theme_);
	guiDays->setPosition(fourth_column_x_, kFirstHeight);

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
	scroll_search_exercises_ = new ofxDatGuiScrollView("Exercises", kSearchExerciseScrollHeight);
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

void ofApp::SetupDays() {
	guiDays->addLabel("Weekly Planner");
	std::vector<std::string> days_names_{ "Sunday", "Monday", "Tuesday", "Wednesday",
										  "Thursday", "Friday", "Saturday" };

	for (int i = 0; i < days_names_.size(); i++) {
		days_.push_back(Day(days_names_[i]));
	}

	guiDays->addDropdown("Select Day", days_names_);
	guiDays->onDropdownEvent(this, &ofApp::onDropdownDay);

	ofxDatGuiButton* see_whole_library_ =guiDays->addButton("See All Workout Plans");
	guiDays->onButtonEvent(this, &ofApp::onButtonDaySeeLibrary);

	guiDays->addTextInput("Workout Name", "");
	guiDays->addTextInput("Exercise Name", "");
	guiDays->onTextInputEvent(this, &ofApp::onTextDaySelectWorkout);



	scroll_day_select_workout_ = new ofxDatGuiScrollView("Library of Workouts", kScrollLibrary);
	scroll_day_select_workout_->setPosition(fourth_column_x_, kFirstHeight
		+ guiDays->getHeight() + kVerticalBreak);
	scroll_day_select_workout_->onScrollViewEvent(this, &ofApp::onScrollDaySelectWorkout);
	scroll_day_select_workout_->setBackgroundColor(background_color_);

	scroll_day_add_workout_ = new ofxDatGuiScrollView("Workouts", kScrollViewElements);
	scroll_day_add_workout_->setPosition(fourth_column_x_, kFirstHeight
		+ guiDays->getHeight() + scroll_day_select_workout_->getHeight() + 2 * kVerticalBreak);
	scroll_day_add_workout_->onScrollViewEvent(this, &ofApp::onScrollDayAddWorkout);
	scroll_day_add_workout_->setBackgroundColor(background_color_);


	scroll_day_see_day_ = new ofxDatGuiScrollView("Day Workouts", kScrollViewElements);
	scroll_day_see_day_->setPosition(fourth_column_x_, kFirstHeight
		+ guiDays->getHeight() + scroll_day_select_workout_->getHeight() 
		+ scroll_day_add_workout_->getHeight() + 3 * kVerticalBreak);
	scroll_day_see_day_->onScrollViewEvent(this, &ofApp::onScrollDayRemoveWorkout);
	scroll_day_see_day_->setBackgroundColor(background_color_);

	
}

void ofApp::SetupClearScrollsButton() {
	button_clear_all_scrolls_ = new ofxDatGuiButton("Clear Scrolls");
	button_clear_all_scrolls_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button_clear_all_scrolls_->onButtonEvent(this, &ofApp::onButtonClearAllScrolls);
	button_clear_all_scrolls_->setTheme(theme_);
	button_clear_all_scrolls_->setPosition(ofGetScreenWidth() / 2 -
		button_clear_all_scrolls_->getWidth() / 2,
		ofGetScreenHeight() - 3 * button_clear_all_scrolls_->getHeight()
		- 3*kVerticalBreak);
}

//--------------------------------------------------------------
void ofApp::update(){
	scroll_search_exercises_->update();
	scroll_see_library_->update();
	scroll_see_workout_->update();
	scroll_select_exercises_->update();
	scroll_edit_plan_->update();
	scroll_day_see_day_->update();
	scroll_day_select_workout_->update();
	scroll_day_add_workout_->update();
	button_clear_all_scrolls_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(background_color_);

	title_->draw();
	scroll_search_exercises_->draw();
	scroll_see_library_->draw();
	scroll_see_workout_->draw();
	scroll_select_exercises_->draw();
	scroll_edit_plan_->draw();
	scroll_day_see_day_->draw();
	scroll_day_select_workout_->draw();
	scroll_day_add_workout_->draw();
	button_clear_all_scrolls_->draw();
}


//Convenience Methods for Populating Scroll View
void ofApp::PopulateScrollExercises(std::vector<Exercise> results, ofxDatGuiScrollView* scroll) {
	for (int i = 0; i < results.size(); i++) {
		scroll->add(results[i].GetName());
		scroll->add("		Muscle: " + results[i].GetMuscle());
		scroll->add("		Equipment: " + results[i].GetEquipment());
	}
}

void ofApp::PopulateScrollWorkouts(std::vector<WorkoutPlan> results, ofxDatGuiScrollView* scroll) {
	for (int i = 0; i < results.size(); i++) {
		scroll->add(results[i].GetName());
	}
}



//Method for Clear Scrolls Button
void ofApp::onButtonClearAllScrolls(ofxDatGuiButtonEvent e) {
	if (e.target->is("Clear Scrolls")) {
		scroll_search_exercises_->clear();

		scroll_see_library_->clear();
		scroll_see_workout_->clear();

		scroll_select_exercises_->clear();
		scroll_edit_plan_->clear();

		scroll_day_select_workout_->clear();
		scroll_day_add_workout_->clear();
		scroll_day_see_day_->clear();
	}
}




//Methods for Creating/Editing Workout
void ofApp::onScrollAddExerciseToWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	vector<Exercise> exercises = library_.SearchForExercisesByName(exercise_name);
	Exercise* exercise = &exercises[0];
	current_workout_.AddExercise(*exercise);
	UpdateScrollEditPlan();
}

void ofApp::onScrollRemoveExerciseFromWorkout(ofxDatGuiScrollViewEvent e) {
	std::string exercise_name = e.target->getLabel();
	current_workout_.RemoveExercise(exercise_name);
}

void ofApp::onTextCreateWorkout(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Plan Name")) {
		//Searching to see if there are any workout plans with this name already
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		if (results.size() == 0) {
			vector<Exercise> empty_exercises{};
			current_workout_ = WorkoutPlan(e.text, empty_exercises);
		} else {
			current_workout_ = results[0];
			scroll_edit_plan_->clear();
			UpdateScrollEditPlan();
		}

	} else if (e.target->is("Exercise Name")) {
		scroll_select_exercises_->add("Click Exercise to Add");
		SearchForExerciseByName(e.text, scroll_select_exercises_);
	} else if (e.target->is("Muscle Name")) {
		scroll_select_exercises_->add("Click Exercise to Add");
		SearchForExerciseByMuscle(e.text, scroll_select_exercises_);
	} else if (e.target->is("Equipment Name")) {
		scroll_select_exercises_->add("Click Exercise to Add");
		SearchForExerciseByEquipment(e.text, scroll_select_exercises_);
	}
}

void ofApp::UpdateScrollEditPlan() {
	scroll_edit_plan_->clear();
	scroll_edit_plan_->add("Exercises in this Workout");
	scroll_edit_plan_->add("Click Exercise to Remove");
	PopulateScrollExercises(current_workout_.GetExercises(), scroll_edit_plan_);
}

void ofApp::onButtonCreateWorkout(ofxDatGuiButtonEvent e) {
	if (e.target->is("Done Creating/Editing Workout")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(current_workout_.GetName());
		if (results.size() == 0) {
			library_.AddWorkoutPlan(current_workout_);
		} else {
			library_.RemoveWorkoutPlan(current_workout_.GetName());
			library_.AddWorkoutPlan(current_workout_);
		}
	} else if (e.target->is("Delete Workout")) {
		library_.RemoveWorkoutPlan(current_workout_.GetName());
	}
	scroll_select_exercises_->clear();
	scroll_edit_plan_->clear();
}





//Methods for searching for exercises
void ofApp::SearchForExerciseByName(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByName(input);
	scroll->clear();
	PopulateScrollExercises(results, scroll);
}

void ofApp::SearchForExerciseByMuscle(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByMuscle(input);
	scroll->clear();
	PopulateScrollExercises(results, scroll);
}

void ofApp::SearchForExerciseByEquipment(string input, ofxDatGuiScrollView* scroll) {
	vector<Exercise> results = library_.SearchForExercisesByEquipment(input);
	scroll->clear();
	PopulateScrollExercises(results, scroll);
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

		PopulateScrollWorkouts(results, scroll_see_library_);
	}
}

void ofApp::onTextSeeLibrary(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		scroll_see_workout_->clear();
		scroll_see_library_->clear();
		PopulateScrollWorkouts(results, scroll_see_library_);
	} else if (e.target->is("Exercise Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByExercise(e.text);
		scroll_see_workout_->clear();
		scroll_see_library_->clear();
		PopulateScrollWorkouts(results, scroll_see_library_);
	}
}

void ofApp::onScrollSeeLibrary(ofxDatGuiScrollViewEvent e) {
	scroll_see_workout_->clear();
	scroll_see_workout_->add("Exercises");
	std::string workout_name = e.target->getLabel();
	vector<WorkoutPlan> workout = library_.SearchForPlanByName(workout_name);
	vector<Exercise> results = workout[0].GetExercises();

	PopulateScrollExercises(results, scroll_see_workout_);
}




//Methods for Weekly Planner
void ofApp::onDropdownDay(ofxDatGuiDropdownEvent e) {
	scroll_day_add_workout_->clear();
	scroll_day_see_day_->clear();
	scroll_day_select_workout_->clear();
	string name = e.target->getLabel();
	for (int i = 0; i < days_.size(); i++) {
		if (days_[i].GetName() == name) {
			current_day_ = &days_[i];
			UpdateScrollDaySeeDay();
			break;
		}
	}
}

void ofApp::onButtonDaySeeLibrary(ofxDatGuiButtonEvent e) {
	if (e.target->is("See All Workout Plans")) {
		vector<WorkoutPlan> results = *library_.GetWorkoutPlans();
		scroll_day_select_workout_->clear();
		PopulateScrollWorkouts(results, scroll_day_select_workout_);
	}
}

void ofApp::onTextDaySelectWorkout(ofxDatGuiTextInputEvent e) {
	if (e.target->is("Workout Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByName(e.text);
		scroll_day_select_workout_->clear();
		PopulateScrollWorkouts(results, scroll_day_select_workout_);
	} else if (e.target->is("Exercise Name")) {
		vector<WorkoutPlan> results = library_.SearchForPlanByExercise(e.text);
		scroll_day_select_workout_->clear();
		PopulateScrollWorkouts(results, scroll_day_select_workout_);
	}
}

void ofApp::onScrollDaySelectWorkout(ofxDatGuiScrollViewEvent e) {
	scroll_day_add_workout_->clear();

	scroll_day_add_workout_->add("Click this to Add");
	scroll_day_add_workout_->add("Exercises in this Workout");

	vector<WorkoutPlan> workout = library_.SearchForPlanByName(e.target->getLabel());
	WorkoutPlan current_workout = workout[0];
	selected_workout_ = workout[0];

	PopulateScrollExercises(current_workout.GetExercises(), scroll_day_add_workout_);
}

void ofApp::onScrollDayAddWorkout(ofxDatGuiScrollViewEvent e) {
	std::string workout_name = e.target->getLabel();
	if (workout_name == "Click this to Add") {
		current_day_->AddWorkoutPlan(selected_workout_);
		UpdateScrollDaySeeDay();
	}
}

void ofApp::onScrollDayRemoveWorkout(ofxDatGuiScrollViewEvent e) {
	std::string workout_name = e.target->getLabel();
	current_day_->RemoveWorkoutPlan(workout_name);
}

void ofApp::UpdateScrollDaySeeDay() {
	scroll_day_see_day_->clear();
	scroll_day_see_day_->add("Workout Plans for this Day");
	scroll_day_see_day_->add("Click Workout Plan to Remove");
	PopulateScrollWorkouts(*current_day_->GetWorkoutPlans(), scroll_day_see_day_);
}

