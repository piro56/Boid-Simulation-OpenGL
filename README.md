# Various Assortment of Small OpenGL-Projects

### Boid Simulation
A medium sized project, where I simulate BOIDs. <br/>
*Boid (plural boids)*: A computer simulation of an animal that flies in flocks or swarms.

#### Optimization
- Utilized multithreading to allow for numerous thousands of boids.<br/>
- Only consider approximately 1/k of the surrounding boids (where k = num threads). <br/>
  - Calculating flocking behavior by looking at only a fraction of the number of objects still results in similar behavior, and was practically indistinguishable with a large enough flock.<br/>
#### Learning Outcome
This project was great for getting more familiarity with the graphics pipeline, and bettering the organization of my code utilizing classes and inheritance.
![boids](https://user-images.githubusercontent.com/69094266/140634526-c7f49dc5-b07c-4020-9910-73862976147a.gif)

References:
https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf
http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/

### 3D Cube
Using matrix transformations and through many really weird looking squares, I eventually was able to create a cube.
- 3D World Space == with a moving camera and transformation matrices, I was able to simulate a 3D worldspace.
- Rotating Objects and Transformation Matrices - Using a transformation matrix allowed for easy manipulation of object vertices. <a/>
`![3dcubes](https://user-images.githubusercontent.com/69094266/172071925-e40f48b6-0d4f-42bd-9e1f-021ec373d2cf.gif)`
<p align="center">
<img src="https://user-images.githubusercontent.com/69094266/172071925-e40f48b6-0d4f-42bd-9e1f-021ec373d2cf.gif" width="500" height="400">
</p>
