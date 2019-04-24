# Work Log

## Week 1
1. *4-7-19* Came up with project proposal.
1. *4-7-19* Found an api that contains information about different exercises but still trying to make
it work as it runs on localhost. I plan on getting data from a JSON file and then implementing 
this functionality after I get it working if I have time.
1. *4-8-19* Started playing around with ofxGui. I can successfully create a panel, buttons, 
and sliders that interact with another class. 
1. *4-9-19* Started experimenting with ofxJSON. I can successfully read from a JSON file 
and print out the data it contains. 
1. *4-10-19* Successfully learned how to get an array from a JSON file.

## Week 2
1. *4-15-19* Finished creating JSON file of exercises.
1. *4-15-19* Create classes for Exercise, WorkoutPlan, and Library
1. *4-15-19* Add functions to Exercise, WorkoutPlan, and Library
1. *4-15-19* Add tests for Exercise, WorkoutPlan, and Library
1. *4-16-19* Add search functions to Library and add muscle_ member to Exercise
1. *4-17-19* Update tests to reflect change in Exercise
1. *4-17-19* Create Parser class, can successfully parse an array of exercises from a JSON file

## Week 3
1. *4-22-19* Change vector variable members in WorkoutPlan and Library to pointers to vectors
1. *4-22-19* Trying to figure out how to call a function once a button is pressed
1. *4-22-19* Learned about adding a listener per button
1. *4-22-19* Getting error when I call SearchForExerciseByName on the library object, inside method
call it has the wrong size vector of exercises
	1. *4-22-19* Figured out that I was setting a pointer to the address of a temp variable
1. *4-22-19* Running into problem where I create a temporary vector and set a WorkoutPlan's 
pointer variable to the address of the temp vector
	1. *4-22-19* Decided to make WorkoutPlan's member variable a vector, not a pointer to a variable
1. *4-22-19* Found another addon called ofxDatGui to use drop down menus
	1. *4-22-19* Starting to get ofxDatGui to work, I'll use this addon instead of ofxGui
1. *4-22-19* Figured out how to create text input field using ofxDatGui
1. *4-22-19* Created multiple text boxes to search for exercises by different criteria
1. *4-22-19* Decided to get rid of buttons for a couple activities and use folders instead
1. *4-22-19* Figured out how to increase font size and increase width of buttons
1. *4-23-19* Decided to use ofxDatGuiScrollView to display the exercises after searching
	1. *4-23-19* Created scroll view that shows results of searching exercises