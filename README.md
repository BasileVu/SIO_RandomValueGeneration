# SIO_RandomValueGeneration

A small project done in the Simulation and Optimization course at HEIG-VD. 
The idea is to generate random values according to a piece-wise linear function using three different algorithms:
* Hit or miss
* Mixture + geometric approach
* Mixture + inverse functions

The various generated values are then processed in order to compute mean, standard variation and a confidence interval at 95%. 
After that, additionnal values are generated in order to sample the time elapsed for each simulation, which then 
is used to compare the three algoritms by computing the mean, standard deviation and confidence interval for the time.
