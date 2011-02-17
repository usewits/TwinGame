#pragma once
#include "Object.h"

class mat;

//Note: the camera position in this class is the look-at position and not the actual position of the camera.
//GetRealCameraPosition() will return the actual position, with zoom value taken into account.

//The position and pitch and yaw are used from the object base. The movement vector from Object is not used
class Camera : public Object
{
public:
	Camera(ObjectManager* objectmgr);
	~Camera();

	//Only for initialization. This is the look-at position of the camera.
	void SetPosition( const Vector3& CamPos ){ position = CamPos; }

	//This will make the camera follow the specified object.
	//Note: the camera will 'flow' after the object. When switching
	//objects it will also smoothly fly from one object to the next.
	void FollowObject( const Object* object, bool FreeRotation = false );
	void ViewLocation( const Vector3& location, bool FreeRotation = false );

	//ObjectPosition is the postion of the object that the camera should follow.
	//This is usually the position of the local player but the camera could also
	//be hanging still somewhere else. ObjectMovement is the movement vector of the
	//object. This is neccesary because when the player walks towards the camera
	//then the camera will not fly to the player as fast as when the player would
	//be walking away from it.
	void Update(float ElapsedTime);

	//These should be called by the mouse handler
	//This will give the camera a swing
	void RotateCameraSwing(float yawspeed, float pitchspeed);
	//This will also rotate the camera but will instantly apply the angle and not swing
	void RotateCamera(float Yaw, float Pitch); //Add yaw/pitch to current angle
	void SetCameraAngle(float Yaw, float Pitch);

	//Vector3 GetRealCameraPosition();
	void GenerateViewMatrix();
	mat* viewMatrix; //Pointer to Renderer's viewmatrix

	float mCamZoomSpeed; //Zoomspeed. positive means zooming out
	float mCamYawSpeed; //Yaw speed in radians per second
	float mCamPitchSpeed; //Pitch speed in radians per second

private:
	float mCamDist; //Zoom. Higher means further away
	float MinCamDist;
	float MaxCamDist;

	bool mFollowingObject; //Wether we are using mObject or mFollowPosition
	bool mFreeRotation; //Camera behind object or free rotation
	const Object* mObject; //The object that is being followed
	Vector3 mFollowPosition;

	void DeAccelerate(float& Speed, float Acceleration);
};
