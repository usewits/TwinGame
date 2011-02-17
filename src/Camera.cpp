#include "Camera.h"
#include "matrix.h"

Camera::Camera(ObjectManager* objectmgr) : Object(objectmgr),
	mCamDist(40), MinCamDist(10), MaxCamDist(80),
	mCamZoomSpeed(0), mCamYawSpeed(0), mCamPitchSpeed(0),
	mFollowingObject(false), mFreeRotation(false), mObject(0), mFollowPosition(0.0f)
{}

Camera::~Camera(){}

const float PI = 3.14159265358979323846264338327950288f;

//This will make the camera follow the specified object.
//Note: the camera will 'flow' after the object. When switching
//objects it will also smoothly fly from one object to the next.
void Camera::FollowObject( const Object* object, bool FreeRotation ){
	mObject = object;
	mFollowingObject = true;
	mFreeRotation = FreeRotation;
}

void Camera::ViewLocation( const Vector3& location, bool FreeRotation ){
	mFollowPosition = location;
	mFollowingObject = false;
	mFreeRotation = FreeRotation;
}

void Camera::Update(float ElapsedTime){

	//---------------------------------------------
	//TODO: Camera shouldn't move beneath the floor
	//		so we need to check with a heightmap or
	//		for now probably just the y = -20 plane.
	//---------------------------------------------

	bool MatrixChanged = false;

	Vector3 TargetPos = (mFollowingObject ? mObject->position : mFollowPosition);
	Vector3 ToMove = TargetPos - position;
	float dist = ToMove.length();
    
	//1. Camera position
	//We only need to move if the camera is not at the player
	if( dist > 0 ){
		//If the camera is really far away OR really close to the object and the object is not moving
		//then just teleport the camera to the exact object position
		if( dist > 100.0f || (mFollowingObject && !mObject->movement.isZeroLength() && dist < 0.1f) ){
			position = TargetPos;
		}else{ //We are at a normal distance from the object. Let camera fly with normal speed
			//ToMove already has a length, so if the camera is further away from the player,
			//then the camera will go faster.
			//When the object is moving in a single direction then the camera will be (PlayerSpeed/2.0f) units behind the object
			position += ToMove * 2.0f * ElapsedTime;
		}
		MatrixChanged = true;
	}

	//2. Camera rotation
	if( mFreeRotation ){
		if( mCamYawSpeed ){
			if( mCamYawSpeed > 1.5f*PI ) mCamYawSpeed = 1.5f*PI;
			if( mCamYawSpeed < -1.5f*PI ) mCamYawSpeed = -1.5f*PI;
			yaw += mCamYawSpeed * ElapsedTime;
			MatrixChanged = true;
			DeAccelerate(mCamYawSpeed, 3.5f * ElapsedTime); //Deacceleration of 3.5 radians per second per second
		}
		if( mCamPitchSpeed ){
			if( mCamPitchSpeed > PI ) mCamPitchSpeed = PI;
			else if( mCamPitchSpeed < -PI ) mCamPitchSpeed = -PI;
			pitch += mCamPitchSpeed * ElapsedTime;
			MatrixChanged = true;
			//Decrease the speed (which causes a natural 'slow down')
			DeAccelerate(mCamPitchSpeed, 3.5f * ElapsedTime); //Deacceleration of 3.5 radians per second per second
		}
	}else{
		mCamYawSpeed = 0;
		mCamPitchSpeed = 0;
		if( mFollowingObject ){
			if( yaw != mObject->yaw || pitch != mObject->pitch ) MatrixChanged = true;
			yaw = mObject->yaw;
			pitch = mObject->pitch;
		}
	}

	//3. Camera zoom
	if( mCamZoomSpeed ){
		if( mCamZoomSpeed > 60 ) mCamZoomSpeed = 60;
		else if( mCamZoomSpeed < -60 ) mCamZoomSpeed = -60;
		//Adjust the zoom with the speed
		mCamDist += mCamZoomSpeed * ElapsedTime;
		MatrixChanged = true;
		//Make sure it does not zoom in or out too far
		if( mCamDist < MinCamDist ){ mCamDist = MinCamDist; mCamZoomSpeed = 0; }
		else if( mCamDist > MaxCamDist ){ mCamDist = MaxCamDist; mCamZoomSpeed = 0; }
		//Decrease the speed (which causes a natural 'slow down')
		DeAccelerate(mCamZoomSpeed, 700 * ElapsedTime); //Deacceleration of 700 units per second per second
	}

	if( MatrixChanged ) GenerateViewMatrix();
}

void Camera::DeAccelerate(float& Speed, float Acceleration){
	if( Speed > 0 ){
		if( Speed < Acceleration ) Speed = 0;
		else Speed -= Acceleration;
	}else{
		if( Speed > Acceleration ) Speed = 0;
		else Speed += Acceleration;
	}
}

void Camera::RotateCameraSwing(float yawspeed, float pitchspeed){
	mCamYawSpeed += yawspeed;
	mCamPitchSpeed += pitchspeed;
}

void Camera::RotateCamera(float Yaw, float Pitch){
	yaw += Yaw, 
    pitch += Pitch;
}

void Camera::SetCameraAngle(float Yaw, float Pitch){
	yaw = Yaw;
	pitch = Pitch;
}

void Camera::GenerateViewMatrix(){
	if( viewMatrix ){
		mat zoomMat, rotateMat, translateMat;
		zoomMat.setTranslation(0, 0, -mCamDist);
		rotateMat.setRotationXYZ( -pitch, -yaw, 0 );
		translateMat.setTranslation(-position);
		*viewMatrix = zoomMat * rotateMat * translateMat;
	}
}