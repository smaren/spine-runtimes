/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated January 1, 2020. Replaces all prior versions.
 *
 * Copyright (c) 2013-2020, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "SpineBone.h"
#include "SpineSprite.h"
#include "SpineSkeleton.h"
#include "SpineCommon.h"

void SpineBone::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update_world_transform"), &SpineBone::update_world_transform);
	ClassDB::bind_method(D_METHOD("set_to_setup_pose"), &SpineBone::set_to_setup_pose);
	ClassDB::bind_method(D_METHOD("world_to_local", "world_position"), &SpineBone::world_to_local);
	ClassDB::bind_method(D_METHOD("local_to_world", "local_position"), &SpineBone::local_to_world);
	ClassDB::bind_method(D_METHOD("world_to_local_rotation", "world_rotation"), &SpineBone::world_to_local_rotation);
	ClassDB::bind_method(D_METHOD("local_to_world_rotation", "local_rotation"), &SpineBone::local_to_world_rotation);
	ClassDB::bind_method(D_METHOD("rotate_world"), &SpineBone::rotate_world);
	ClassDB::bind_method(D_METHOD("get_world_to_local_rotation_x"), &SpineBone::get_world_to_local_rotation_x);
	ClassDB::bind_method(D_METHOD("get_world_to_local_rotation_y"), &SpineBone::get_world_to_local_rotation_y);
	ClassDB::bind_method(D_METHOD("get_data"), &SpineBone::get_data);
	ClassDB::bind_method(D_METHOD("get_skeleton"), &SpineBone::get_skeleton);
	ClassDB::bind_method(D_METHOD("get_parent"), &SpineBone::get_parent);
	ClassDB::bind_method(D_METHOD("get_children"), &SpineBone::get_children);
	ClassDB::bind_method(D_METHOD("get_x"), &SpineBone::get_x);
	ClassDB::bind_method(D_METHOD("set_x", "v"), &SpineBone::set_x);
	ClassDB::bind_method(D_METHOD("get_y"), &SpineBone::get_y);
	ClassDB::bind_method(D_METHOD("set_y", "v"), &SpineBone::set_y);
	ClassDB::bind_method(D_METHOD("get_rotation"), &SpineBone::get_rotation);
	ClassDB::bind_method(D_METHOD("set_rotation", "v"), &SpineBone::set_rotation);
	ClassDB::bind_method(D_METHOD("get_scale_x"), &SpineBone::get_scale_x);
	ClassDB::bind_method(D_METHOD("set_scale_x", "v"), &SpineBone::set_scale_x);
	ClassDB::bind_method(D_METHOD("get_scale_y"), &SpineBone::get_scale_y);
	ClassDB::bind_method(D_METHOD("set_scale_y", "v"), &SpineBone::set_scale_y);
	ClassDB::bind_method(D_METHOD("get_shear_x"), &SpineBone::get_shear_x);
	ClassDB::bind_method(D_METHOD("set_shear_x", "v"), &SpineBone::set_shear_x);
	ClassDB::bind_method(D_METHOD("get_shear_y"), &SpineBone::get_shear_y);
	ClassDB::bind_method(D_METHOD("set_shear_y", "v"), &SpineBone::set_shear_y);
	ClassDB::bind_method(D_METHOD("get_applied_rotation"), &SpineBone::get_applied_rotation);
	ClassDB::bind_method(D_METHOD("set_applied_rotation", "v"), &SpineBone::set_applied_rotation);
	ClassDB::bind_method(D_METHOD("get_a_x"), &SpineBone::get_a_x);
	ClassDB::bind_method(D_METHOD("set_a_x", "v"), &SpineBone::set_a_x);
	ClassDB::bind_method(D_METHOD("get_a_y"), &SpineBone::get_a_y);
	ClassDB::bind_method(D_METHOD("set_a_y", "v"), &SpineBone::set_a_y);
	ClassDB::bind_method(D_METHOD("get_a_scale_x"), &SpineBone::get_a_scale_x);
	ClassDB::bind_method(D_METHOD("set_a_scale_x", "v"), &SpineBone::set_a_scale_x);
	ClassDB::bind_method(D_METHOD("get_a_scale_y"), &SpineBone::get_a_scale_y);
	ClassDB::bind_method(D_METHOD("set_a_scale_y", "v"), &SpineBone::set_a_scale_y);
	ClassDB::bind_method(D_METHOD("get_a_shear_x"), &SpineBone::get_a_shear_x);
	ClassDB::bind_method(D_METHOD("set_a_shear_x", "v"), &SpineBone::set_a_shear_x);
	ClassDB::bind_method(D_METHOD("get_a_shear_y"), &SpineBone::get_a_shear_y);
	ClassDB::bind_method(D_METHOD("set_a_shear_y", "v"), &SpineBone::set_a_shear_y);
	ClassDB::bind_method(D_METHOD("get_a"), &SpineBone::get_a);
	ClassDB::bind_method(D_METHOD("set_a", "v"), &SpineBone::set_a);
	ClassDB::bind_method(D_METHOD("get_b"), &SpineBone::get_b);
	ClassDB::bind_method(D_METHOD("set_b", "v"), &SpineBone::set_b);
	ClassDB::bind_method(D_METHOD("get_c"), &SpineBone::get_c);
	ClassDB::bind_method(D_METHOD("set_c", "v"), &SpineBone::set_c);
	ClassDB::bind_method(D_METHOD("get_d"), &SpineBone::get_d);
	ClassDB::bind_method(D_METHOD("set_d", "v"), &SpineBone::set_d);
	ClassDB::bind_method(D_METHOD("get_world_x"), &SpineBone::get_world_x);
	ClassDB::bind_method(D_METHOD("set_world_x", "v"), &SpineBone::set_world_x);
	ClassDB::bind_method(D_METHOD("get_world_y"), &SpineBone::get_world_y);
	ClassDB::bind_method(D_METHOD("set_world_y", "v"), &SpineBone::set_world_y);
	ClassDB::bind_method(D_METHOD("get_world_rotation_x"), &SpineBone::get_world_rotation_x);
	ClassDB::bind_method(D_METHOD("get_world_rotation_y"), &SpineBone::get_world_rotation_y);
	ClassDB::bind_method(D_METHOD("get_world_scale_x"), &SpineBone::get_world_scale_x);
	ClassDB::bind_method(D_METHOD("get_world_scale_y"), &SpineBone::get_world_scale_y);
	ClassDB::bind_method(D_METHOD("is_active"), &SpineBone::is_active);
	ClassDB::bind_method(D_METHOD("set_active", "v"), &SpineBone::set_active);
	ClassDB::bind_method(D_METHOD("apply_world_transform_2d", "node2d"), &SpineBone::apply_world_transform_2d);
	ClassDB::bind_method(D_METHOD("get_transform"), &SpineBone::get_transform);
	ClassDB::bind_method(D_METHOD("set_transform", "local_transform"), &SpineBone::set_transform);
	ClassDB::bind_method(D_METHOD("get_global_transform"), &SpineBone::get_global_transform);
	ClassDB::bind_method(D_METHOD("set_global_transform", "global_transform"), &SpineBone::set_global_transform);
}

SpineBone::SpineBone() : bone(nullptr), sprite(nullptr) {}

void SpineBone::update_world_transform() {
	SPINE_CHECK(bone,)
	bone->updateWorldTransform();
}

void SpineBone::set_to_setup_pose() {
	SPINE_CHECK(bone,)
	bone->setToSetupPose();
}

Vector2 SpineBone::world_to_local(Vector2 world_position) {
	SPINE_CHECK(bone, Vector2())
	float x, y;
	bone->worldToLocal(world_position.x, world_position.y, x, y);
	return Vector2(x, y);
}

Vector2 SpineBone::local_to_world(Vector2 local_position) {
	SPINE_CHECK(bone, Vector2())
	float x, y;
	bone->localToWorld(local_position.x, local_position.y, x, y);
	return Vector2(x, y);
}

float SpineBone::world_to_local_rotation(float world_rotation) {
	SPINE_CHECK(bone, 0)
	return bone->worldToLocalRotation(world_rotation);
}

float SpineBone::local_to_world_rotation(float local_rotation) {
	SPINE_CHECK(bone, 0)
	return bone->localToWorldRotation(local_rotation);
}

void SpineBone::rotate_world(float degrees) {
	SPINE_CHECK(bone,)
	bone->rotateWorld(degrees);
}

float SpineBone::get_world_to_local_rotation_x() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldToLocalRotationX();
}

float SpineBone::get_world_to_local_rotation_y() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldToLocalRotationY();
}

Ref<SpineBoneData> SpineBone::get_data() {
	SPINE_CHECK(bone, nullptr)
	auto &bone_data = bone->getData();
	Ref<SpineBoneData> bone_data_ref(memnew(SpineBoneData));
	bone_data_ref->set_spine_object(&bone_data);
	return bone_data_ref;
}

Ref<SpineSkeleton> SpineBone::get_skeleton() {
	SPINE_CHECK(bone, nullptr)
	auto &skeleton = bone->getSkeleton();
	Ref<SpineSkeleton> skeleton_ref(memnew(SpineSkeleton));
	skeleton_ref->set_spine_object(sprite, &skeleton);
	return skeleton_ref;
}

Ref<SpineBone> SpineBone::get_parent() {
	SPINE_CHECK(bone, nullptr)
	auto parent = bone->getParent();
	if (!parent) return nullptr;
	Ref<SpineBone> parent_ref(memnew(SpineBone));
	parent_ref->set_spine_object(sprite, parent);
	return parent_ref;
}

Array SpineBone::get_children() {
	Array result;
	SPINE_CHECK(bone, result)
	auto children = bone->getChildren();
	result.resize((int)children.size());
	for (int i = 0; i < children.size(); ++i) {
		auto child = children[i];
		Ref<SpineBone> bone_ref(memnew(SpineBone));
		bone_ref->set_spine_object(sprite, child);
		result[i] = bone_ref;
	}
	return result;
}

float SpineBone::get_x() {
	SPINE_CHECK(bone, 0)
	return bone->getX();
}

void SpineBone::set_x(float v) {
	SPINE_CHECK(bone,)
	bone->setX(v);
}

float SpineBone::get_y() {
	SPINE_CHECK(bone, 0)
	return bone->getY();
}

void SpineBone::set_y(float v) {
	SPINE_CHECK(bone,)
	bone->setY(v);
}

float SpineBone::get_rotation() {
	SPINE_CHECK(bone, 0)
	return bone->getRotation();
}

void SpineBone::set_rotation(float v) {
	SPINE_CHECK(bone,)
	bone->setRotation(v);
}

float SpineBone::get_scale_x() {
	SPINE_CHECK(bone, 0)
	return bone->getScaleX();
}

void SpineBone::set_scale_x(float v) {
	SPINE_CHECK(bone,)
	bone->setScaleX(v);
}

float SpineBone::get_scale_y() {
	SPINE_CHECK(bone, 0)
	return bone->getScaleY();
}

void SpineBone::set_scale_y(float v) {
	SPINE_CHECK(bone,)
	bone->setScaleY(v);
}

float SpineBone::get_shear_x() {
	SPINE_CHECK(bone, 0)
	return bone->getShearX();
}

void SpineBone::set_shear_x(float v) {
	SPINE_CHECK(bone,)
	bone->setShearX(v);
}

float SpineBone::get_shear_y() {
	SPINE_CHECK(bone, 0)
	return bone->getShearY();
}

void SpineBone::set_shear_y(float v) {
	SPINE_CHECK(bone,)
	bone->setShearY(v);
}

float SpineBone::get_applied_rotation() {
	SPINE_CHECK(bone, 0)
	return bone->getAppliedRotation();
}

void SpineBone::set_applied_rotation(float v) {
	SPINE_CHECK(bone,)
	bone->setAppliedRotation(v);
}

float SpineBone::get_a_x() {
	SPINE_CHECK(bone, 0)
	return bone->getAX();
}

void SpineBone::set_a_x(float v) {
	SPINE_CHECK(bone,)
	bone->setAX(v);
}

float SpineBone::get_a_y() {
	SPINE_CHECK(bone, 0)
	return bone->getAY();
}

void SpineBone::set_a_y(float v) {
	SPINE_CHECK(bone,)
	bone->setAY(v);
}

float SpineBone::get_a_scale_x() {
	SPINE_CHECK(bone, 0)
	return bone->getAScaleX();
}

void SpineBone::set_a_scale_x(float v) {
	SPINE_CHECK(bone,)
	bone->setAScaleX(v);
}

float SpineBone::get_a_scale_y() {
	SPINE_CHECK(bone, 0)
	return bone->getAScaleY();
}

void SpineBone::set_a_scale_y(float v) {
	SPINE_CHECK(bone,)
	bone->setAScaleY(v);
}

float SpineBone::get_a_shear_x() {
	SPINE_CHECK(bone, 0)
	return bone->getAShearX();
}

void SpineBone::set_a_shear_x(float v) {
	SPINE_CHECK(bone,)
	bone->setAShearX(v);
}

float SpineBone::get_a_shear_y() {
	SPINE_CHECK(bone, 0)
	return bone->getAShearY();
}

void SpineBone::set_a_shear_y(float v) {
	SPINE_CHECK(bone,)
	bone->setAShearY(v);
}

float SpineBone::get_a() {
	SPINE_CHECK(bone, 0)
	return bone->getA();
}

void SpineBone::set_a(float v) {
	SPINE_CHECK(bone,)
	bone->setA(v);
}

float SpineBone::get_b() {
	SPINE_CHECK(bone, 0)
	return bone->getB();
}

void SpineBone::set_b(float v) {
	SPINE_CHECK(bone,)
	bone->setB(v);
}

float SpineBone::get_c() {
	SPINE_CHECK(bone, 0)
	return bone->getC();
}

void SpineBone::set_c(float v) {
	SPINE_CHECK(bone,)
	bone->setC(v);
}

float SpineBone::get_d() {
	SPINE_CHECK(bone, 0)
	return bone->getD();
}

void SpineBone::set_d(float v) {
	SPINE_CHECK(bone,)
	bone->setD(v);
}

float SpineBone::get_world_x() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldX();
}

void SpineBone::set_world_x(float v) {
	SPINE_CHECK(bone,)
	bone->setWorldX(v);
}

float SpineBone::get_world_y() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldY();
}

void SpineBone::set_world_y(float v) {
	SPINE_CHECK(bone,)
	bone->setWorldY(v);
}

float SpineBone::get_world_rotation_x() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldRotationX();
}

float SpineBone::get_world_rotation_y() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldRotationY();
}


float SpineBone::get_world_scale_x() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldScaleX();
}

float SpineBone::get_world_scale_y() {
	SPINE_CHECK(bone, 0)
	return bone->getWorldScaleY();
}

bool SpineBone::is_active() {
	SPINE_CHECK(bone, false)
	return bone->isActive();
}
void SpineBone::set_active(bool v) {
	SPINE_CHECK(bone,)
	bone->setActive(v);
}

// External feature functions
void SpineBone::apply_world_transform_2d(const Variant &o) {
	SPINE_CHECK(bone,)
	if (o.get_type() == Variant::OBJECT) {
		auto node2d = Object::cast_to<Node2D>(o.operator Object*());
		if (node2d) {			
			// In godot the y-axis is nag to spine
			node2d->set_transform(Transform2D(
					get_a(), get_c(),
					get_b(), get_d(),
					get_world_x(), -get_world_y()));
			// Fix the rotation
			auto pos = node2d->get_position();
			node2d->translate(-pos);
			node2d->set_rotation(-node2d->get_rotation());
			node2d->translate(pos);
		}
	}
}

Transform2D SpineBone::get_transform() {
	SPINE_CHECK(bone, Transform2D())
	Transform2D transform;
	transform.rotate(Math::deg2rad(-get_rotation()));
	transform.scale(Size2(get_scale_x(), get_scale_y()));
	transform.set_origin(Vector2(get_x(), -get_y()));
	return transform;
}

void SpineBone::set_transform(Transform2D transform) {
	SPINE_CHECK(bone,)
	Vector2 position = transform.get_origin();
	position.y *= -1;
	float rotation = Math::rad2deg(-transform.get_rotation());
	Vector2 scale = transform.get_scale();

	set_x(position.x);
	set_y(position.y);
	set_rotation(rotation);
	set_scale_x(scale.x);
	set_scale_y(scale.y);
}

Transform2D SpineBone::get_global_transform() {
	SPINE_CHECK(bone, Transform2D())
	if (!sprite) return get_transform();
	if (!sprite->is_visible_in_tree()) return get_transform();
	Transform2D local;
	local.rotate(Math::deg2rad(-get_world_rotation_x()));
	local.scale(Vector2(get_world_scale_x(), get_world_scale_y()));
	local.set_origin(Vector2(get_world_x(), -get_world_y()));
	return sprite->get_global_transform() * local;
}

void SpineBone::set_global_transform(Transform2D transform) {
	SPINE_CHECK(bone,)
	if (!sprite) set_transform(transform);
	if (!sprite->is_visible_in_tree()) return;
	transform = sprite->get_global_transform().affine_inverse() * transform;
	Vector2 position = transform.get_origin();
	position.y *= -1;
	float rotation = world_to_local_rotation(Math::rad2deg(-transform.get_rotation()));
	Vector2 scale = transform.get_scale();

	set_x(position.x);
	set_y(position.y);
	set_rotation(rotation);
	set_scale_x(scale.x);
	set_scale_y(scale.y);
}