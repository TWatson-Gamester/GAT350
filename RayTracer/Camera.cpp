#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov, const glm::ivec2& screenSize, float aperture, float focalLength){
	//The constructor will setup the viewport
	this->screenSize = screenSize;
	this->aspectRatio = (screenSize.x / (float)screenSize.y);

	//Calculate the height from the vertical field of view (fov)
	float theta = glm::radians(fov);
	float h = tan(theta * 0.5f);

	//Calculate the viewport widthand height
	viewportHeight = h * 2.0f;
	viewportWidth = viewportHeight * aspectRatio;

	//set the aperture, focalLengthand lensRadius
	this->aperture = aperture;
	this->focalLength = focalLength;
	lensRadius = this->aperture / 2;

	//Call the Set function
	Set(eye, lookAt, up, fov);
}

void Camera::Set(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov){
	//The create the forward, rightand up vectors for the camera
	this->eye = eye;
	forward = glm::normalize(lookAt - this->eye);
	right = glm::normalize(glm::cross(forward, up));
	this->up = glm::cross(right, forward);

	//Calculate the horizontaland vertical dimensions of the viewport
	horizontal = focalLength * viewportWidth * right;
	vertical = focalLength * viewportHeight * this->up;

	//Calculate the bottom left position of the viewport
	lowerLeft = this->eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward * focalLength;
}

glm::vec2 Camera::ScreenToViewport(const glm::vec2& screen){
	//Convert screen coordinates to viewport
	glm::vec2 viewport{ 0, 0 };

	viewport.x = (float)screen.x / screenSize.x;
	viewport.y = (float)screen.y / screenSize.y;


	return viewport;
}

ray_t Camera::ViewportToRay(const glm::vec2& viewport){

	glm::vec3 random = lensRadius * randomInUnitDisk();
	glm::vec3 offset = right * random.x + up * random.y;

	//Create ray to cast into the viewport
	//The origin of the ray is the current eye
	ray_t ray;
	ray.origin = eye + offset;

	// The direction... uses the lowerLeft as the origin and…
	// scales the horizontal vector by the viewport x and… scales the vertical vector by the viewport.y minus the eye location
	ray.direction = lowerLeft + (viewport.x * horizontal) + (viewport.y * vertical) - eye - offset;
	return ray;
}
