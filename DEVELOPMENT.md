##Development

**11/12/2020**
* Created empty classes for Person and Simulator
* Created CMAKE file, epidemic_app class
* Create header constructor and instance variable skeleton code in person.h and simulator.h.
    * The current plan is to maintain a vector in Simulator of locations on the circle, and maintain
    another vector of People objects where each Person Object corresponds to the location in the location
    vector at the same index. Although this is a parallel array, I am doing this because I can easily shuffle
    locations in the locations vector as my way of reassigning each Person to a new location on the circle
* I think I will implement move mechanics as follows:
    * A method in my Person class called MoveTowardLocation() that will move a Person toward their
new slot in the circle for 1 frame's distance. I will have it return a boolean that returns true once the Person
 has reached their target location.
    * A method in my Simulator class that called ApproachNewLocations() that will move each Person toward their
    target slot along the circle. This method will return true if every call for each Peron.MoveTowardLocation()
    returned true. This will tell the Simulator that each Person has reached their desired locations,
    and the simulation can proceed with the next day.
 
 **11/13/2020**
 * Implement MoveTowardLocation() method in Person class and manually tested in app class.
    * Verified functionality with unit tests
 * Implement Simulator constructor to evenly space out a specified number of people around the Arena.
 
 **11/14/2020**
 * Write unit tests for Simulator constructor's spacing of locations
 * Implement ApproachNewLocations() in Simulator
 class to randomly assign each Person to a new location and then move each person toward that location
    * Have not yet implemented a way to tell once all particles have reached their final location
        * Will use bool values returned from MoveTowardLocation() to return a bool indicating if all particles have
        reached their targets so that simulator will know if it can move on to the next day
        
 **11/15/2020**
 * Finish implementing ApproachNewLocations() to return a bool as described yesterday
 * Refactor Simulator constructor to take a parameter for speed rather than hard-coding it
 * Found bug in ApproachNewLocations() where I double-increment the index in slots
 * Created a Simulator Method that moves one Person at a time to their new location
    * After manually testing this method, I decided that it's too time consuming to watch
    each person move individually for larger datasets, and increasing the speed makes the feature irrelevant
    * Ultimately deleted this method
 * Wrote tests for ApproachNewLocations()
 * Implemented InfectNeighbors()
    * Spent a good deal of time to find bug where slots are being shuffled and not people, so the 
    "neighbors" in people_ are not actual neighbors on the arena.
        * Fixed bug by refactoring ShuffleSlots() to be ShufflePeople(), so
        now the people in people_ are in the order they're in on the arena too
    * Refactored tests to accommodate refactoring ShufflePeople()