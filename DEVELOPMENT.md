Development.md

11/12/2020
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
 
 11/13/2020
 * Implement MoveTowardLocation() method in Person class and manually tested in app class.
 * Implement Simulator constructor to evenly space out a specified number of people around the Arena.