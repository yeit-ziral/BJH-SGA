#include "Framework.h"
#include "Transform.h"

Transform::Transform()
{
	world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	world = XMMatrixTransformation
	(
		pivot, XMQuaternionIdentity(), scale,
		pivot, XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z), // RollPitchYaw가 들어가서 Quaternion이 아니라 오일러 회전을 하고 있고 값만 Quaternion처럼 보여줌
		translation
	);

	if (parent != nullptr)
		world *= parent->world; // parent의 world가 문제 없는 이유는 parent도 Transform이고 this도 Transform인 동일 클래스여서 가능하다.
}
