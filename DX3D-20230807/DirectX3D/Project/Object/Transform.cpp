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
		pivot, XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z), // RollPitchYaw�� ���� Quaternion�� �ƴ϶� ���Ϸ� ȸ���� �ϰ� �ְ� ���� Quaternionó�� ������
		translation
	);

	if (parent != nullptr)
		world *= parent->world; // parent�� world�� ���� ���� ������ parent�� Transform�̰� this�� Transform�� ���� Ŭ�������� �����ϴ�.
}
