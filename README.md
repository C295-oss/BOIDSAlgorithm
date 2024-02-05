
<h1 align="center">
BOID FLocking Algorithm  
</h1>

![alt text](https://github.com/C295-oss/BOIDSAlgorithm/blob/master/BOID.png)

<h1 align="center">
About Algorithm 
</h1>

<p align="center">
The boids algorithm is a behavior simulating algorithm of creatures such as birds that flock together. 
<br/>
</p>

<br/>

<p>
Each particle, or "boid," follows a specific set of rules that lead to flocking behavior:
</p>
<ul>
  <li><b>Seperation</b> : boids will move away from other boids when they are within its space. </li>
  <li><b>Alignment</b> : boids will have similar velocities of their neighboring boids. </li>
  <li><b>Cohesion</b> : boids will move towards the center of mass of the flock. </li>
</ul>

<h1 align="center">
Usage
</h1>
<p align="center">
Run main.cpp as a standard cpp file using gcc. A fullscreen window will pop up and the simulation will commence.
</p>



<h1 align="center">
Resources Used
</h1>
<p align="center">
This repository's algorithm is loosely based on <a href="https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html"> this link</a>.
<br/>
The enviornment was rendered using <a href="https://www.sfml-dev.org/">SFML</a>.
</p>
