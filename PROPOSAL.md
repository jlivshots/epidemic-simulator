I want to make a pandemic simulator for my final project. Specifically, I want to make a model that graphs the spread of a virus over time based on parameters such as how infectious it is, the size of gatherings, the total number of people, the presence of a vaccine, and how long people are immune from the virus.

I do not currently have a lot of experience with this concept besides basic logarithmic models of predicting how quickly an outbreak grows. I want to do this project because it's exremely relevant given the current pandemic, expecially with concerns regarding how long one remains immune and how that effects the spread.

By the end of the first week, I would like to have a basic model where people are represented by particles. I want to have a working simulation where based on parameters like gathering size and total number of people, these particles are assigned to gathering "rooms" where each of them becomes infected a specified percentage of the time for a certain period of time if they are exposed to someone that is infected.

By the end of the second week, I want to begin implementing visual components using cinder to actually see how these "particles" spread the virus. I will also add more logic to have the spread depend on factors like vaccine distrubution, at what point it's released and at what rate, what the maximum vaccination percentage is, etc. I will assign a certain color to infected, a certain one to vaccinated, another one to immune, and a final one to uninfected.

By the end of the third week, I will add graphs that track the spread of the virus. This includes data for infection, vaccination, immunity, (death?), etc. This will likely be in the form of bar charts. To add complexity, I will have the charts draw live as the simulation progresses.

If I finish early, I will add sliders/buttons/text boxes to be able to configure the constants within the Cinder window, rather than through constants in a header file. I could also potentially have presets for actual infection rates of known diseases.
