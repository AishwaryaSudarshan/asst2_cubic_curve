#include "Curve.h"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
}

void Curve::calculate_curve()
{
	//////////
	// Asst2
	// You are supposed to add certain number of points
	// to this->curve_points_pos.
	// Ecach point is calculated through Catmull-Rom formulation.
	// Note that all control points are given in this->control_points_pos.

	this->curve_points_pos.clear();
	int n = static_cast<int>(this->control_points_pos.size());
	if (n < 4) return; // Need at least 4 points for Catmull-Rom

	// Catmull-Rom basis matrix (with tau)
	float t = this->tau;
	glm::mat4 basis = glm::mat4(
		-t, 2.0f - t, t - 2.0f, t,
		 2.0f * t, t - 3.0f, 3.0f - 2.0f * t, -t,
		-t, 0.0f, t, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f
	);

	// Closed curve: wrap control points
	for (int i = 0; i < n; ++i) {
		glm::vec3 P0 = control_points_pos[(i - 1 + n) % n];
		glm::vec3 P1 = control_points_pos[i % n];
		glm::vec3 P2 = control_points_pos[(i + 1) % n];
		glm::vec3 P3 = control_points_pos[(i + 2) % n];

		glm::mat4x3 G(
			P0.x, P0.y, P0.z,
			P1.x, P1.y, P1.z,
			P2.x, P2.y, P2.z,
			P3.x, P3.y, P3.z
		);

		for (int j = 0; j < num_points_per_segment; ++j) {
			float u = float(j) / float(num_points_per_segment - 1);
			glm::vec4 U(u * u * u, u * u, u, 1.0f);
			glm::vec3 point = G * (basis * U);
			this->curve_points_pos.push_back(point);
		}
	}

}
