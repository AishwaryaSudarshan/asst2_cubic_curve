#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Curve
{
public:
	Curve();
	~Curve();
	
	void init();
	//////////
	// Asst2: add calculated points to curve.
	void calculate_curve();

public:
	std::vector<glm::vec3> control_points_pos;
	std::vector<glm::vec3> curve_points_pos;

private:
	float tau = 0.5; // Coefficient for Catmull-Rom splines
	int num_points_per_segment = 200;
};