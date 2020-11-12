I want to make a pandemic simulator for my final project.
Specifically, I want to make a model that graphs the spread of a
 virus over time based on parameters such as how infectious it is, 
 the total number of people, the incubation period, etc.
 
 I imagine a visual simulation where:
  * A particle represents a person, and the color of the particle tells
 us if the person is at risk, infected, or immune
 * The particles will be lined up on the perimeter of a 
 large circle on the screen, whereby they can each infect the particles to their right and left if they
 are contagious
 * After each day, they will each move (on screen) to a new location on the circle, where again they can each infect their
 neighbors.
 * There will be a stacked bar chart where the height of each column is the same, but the bar will be
  divided into regions of infected, vulnerable, and immune, allowing us to see how the spread progresses over time.
  
I do not currently have a lot of experience with this concept besides basic
logarithmic models of predicting how quickly an outbreak grows. 
I want to do this project because it's extremely relevant given the 
current pandemic, especially with concerns regarding how long
one remains immune and how that affects the spread.

By the end of the first week, I will have the movement mechanics created, along seeing the movement in Cinder. This means:
 * Generate particles around the boundary of a circle
 * Show increments of "days" where each particle moves to a new random slot on the circle
 
 By the end of the second week, I will implement the virus logic into the simulation.
 * The simulation will have parameters for: 
    * Total number of people
    * Virus incubation period (how many days from infection until contagious)
    * Contagious period
    * Probability of infecting someone when exposed
    * Duration of immunity
 * The particle colors will update accordingly
    
 By the end of the third week, I will:
 * Create a graph that maps the virus spread over time and updates in real time
 * Create buttons/sliders for the parameters in the simulation
 * Allow user to click a "next day" button day-by-day or to click a "play" button that iterates through days for them


If I finish early, I will add:
* A vaccination feature that a user can add at any point during the simulation:
    * User defines the distribution rate of the vaccine at clicks "distribute" at any moment
* A "lockdown" feature where at any point in the simulation, particles are constrained to 
"pods" until the user ends the lockdown.