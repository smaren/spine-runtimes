/******************************************************************************
* Spine Runtimes Software License v2.5
*
* Copyright (c) 2013-2016, Esoteric Software
* All rights reserved.
*
* You are granted a perpetual, non-exclusive, non-sublicensable, and
* non-transferable license to use, install, execute, and perform the Spine
* Runtimes software and derivative works solely for personal or internal
* use. Without the written permission of Esoteric Software (see Section 2 of
* the Spine Software License Agreement), you may not (a) modify, translate,
* adapt, or develop new applications using the Spine Runtimes or otherwise
* create derivative works or improvements of the Spine Runtimes or (b) remove,
* delete, alter, or obscure any trademarks or any copyright, trademark, patent,
* or other intellectual property or proprietary rights notices on or in the
* Software, including any copy thereof. Redistributions in binary or source
* form must include this license and terms.
*
* THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
* USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#include <spine/TransformConstraint.h>

#include <spine/TransformConstraintData.h>
#include <spine/Skeleton.h>
#include <spine/Bone.h>

#include <spine/BoneData.h>

using namespace Spine;

RTTI_IMPL(TransformConstraint, Constraint);

TransformConstraint::TransformConstraint(TransformConstraintData &data, Skeleton &skeleton) : Constraint(),
																							  _data(data),
																							  _target(skeleton.findBone(
																									  data.getTarget()->getName())),
																							  _rotateMix(
																									  data.getRotateMix()),
																							  _translateMix(
																									  data.getTranslateMix()),
																							  _scaleMix(
																									  data.getScaleMix()),
																							  _shearMix(
																									  data.getShearMix()) {
	_bones.ensureCapacity(_data.getBones().size());
	for (size_t i = 0; i < _data.getBones().size(); ++i) {
		BoneData *boneData = _data.getBones()[i];

		_bones.add(skeleton.findBone(boneData->getName()));
	}
}

void TransformConstraint::apply() {
	update();
}

void TransformConstraint::update() {
	if (_data.isLocal()) {
		if (_data.isRelative()) {
			applyRelativeLocal();
		} else {
			applyAbsoluteLocal();
		}
	} else {
		if (_data.isRelative()) {
			applyRelativeWorld();
		} else {
			applyAbsoluteWorld();
		}
	}
}

int TransformConstraint::getOrder() {
	return _data.getOrder();
}

TransformConstraintData &TransformConstraint::getData() {
	return _data;
}

Vector<Bone *> &TransformConstraint::getBones() {
	return _bones;
}

Bone *TransformConstraint::getTarget() {
	return _target;
}

void TransformConstraint::setTarget(Bone *inValue) {
	_target = inValue;
}

float TransformConstraint::getRotateMix() {
	return _rotateMix;
}

void TransformConstraint::setRotateMix(float inValue) {
	_rotateMix = inValue;
}

float TransformConstraint::getTranslateMix() {
	return _translateMix;
}

void TransformConstraint::setTranslateMix(float inValue) {
	_translateMix = inValue;
}

float TransformConstraint::getScaleMix() {
	return _scaleMix;
}

void TransformConstraint::setScaleMix(float inValue) {
	_scaleMix = inValue;
}

float TransformConstraint::getShearMix() {
	return _shearMix;
}

void TransformConstraint::setShearMix(float inValue) {
	_shearMix = inValue;
}

void TransformConstraint::applyAbsoluteWorld() {
	float rotateMix = _rotateMix, translateMix = _translateMix, scaleMix = _scaleMix, shearMix = _shearMix;
	Bone &target = *_target;
	float ta = target._a, tb = target._b, tc = target._c, td = target._d;
	float degRadReflect = ta * td - tb * tc > 0 ? DEG_RAD : -DEG_RAD;
	float offsetRotation = _data._offsetRotation * degRadReflect, offsetShearY = _data._offsetShearY * degRadReflect;

	for (size_t i = 0; i < _bones.size(); ++i) {
		Bone *item = _bones[i];
		Bone &bone = *item;

		bool modified = false;

		if (rotateMix != 0) {
			float a = bone._a, b = bone._b, c = bone._c, d = bone._d;
			float r = MathUtil::atan2(tc, ta) - MathUtil::atan2(c, a) + offsetRotation;
			if (r > PI) {
				r -= PI_2;
			} else if (r < -PI) {
				r += PI_2;
			}

			r *= rotateMix;
			float cos = MathUtil::cos(r), sin = MathUtil::sin(r);
			bone._a = cos * a - sin * c;
			bone._b = cos * b - sin * d;
			bone._c = sin * a + cos * c;
			bone._d = sin * b + cos * d;
			modified = true;
		}

		if (translateMix != 0) {
			float tx, ty;
			target.localToWorld(_data._offsetX, _data._offsetY, tx, ty);
			bone._worldX += (tx - bone._worldX) * translateMix;
			bone._worldY += (ty - bone._worldY) * translateMix;
			modified = true;
		}

		if (scaleMix > 0) {
			float s = MathUtil::sqrt(bone._a * bone._a + bone._c * bone._c);

			if (s > 0.00001f) {
				s = (s + (MathUtil::sqrt(ta * ta + tc * tc) - s + _data._offsetScaleX) * scaleMix) / s;
			}
			bone._a *= s;
			bone._c *= s;
			s = MathUtil::sqrt(bone._b * bone._b + bone._d * bone._d);

			if (s > 0.00001f) {
				s = (s + (MathUtil::sqrt(tb * tb + td * td) - s + _data._offsetScaleY) * scaleMix) / s;
			}
			bone._b *= s;
			bone._d *= s;
			modified = true;
		}

		if (shearMix > 0) {
			float b = bone._b, d = bone._d;
			float by = MathUtil::atan2(d, b);
			float r = MathUtil::atan2(td, tb) - MathUtil::atan2(tc, ta) - (by - MathUtil::atan2(bone._c, bone._a));
			if (r > PI) {
				r -= PI_2;
			} else if (r < -PI) {
				r += PI_2;
			}

			r = by + (r + offsetShearY) * shearMix;
			float s = MathUtil::sqrt(b * b + d * d);
			bone._b = MathUtil::cos(r) * s;
			bone._d = MathUtil::sin(r) * s;
			modified = true;
		}

		if (modified) {
			bone._appliedValid = false;
		}
	}
}

void TransformConstraint::applyRelativeWorld() {
	float rotateMix = _rotateMix, translateMix = _translateMix, scaleMix = _scaleMix, shearMix = _shearMix;
	Bone &target = *_target;
	float ta = target._a, tb = target._b, tc = target._c, td = target._d;
	float degRadReflect = ta * td - tb * tc > 0 ? DEG_RAD : -DEG_RAD;
	float offsetRotation = _data._offsetRotation * degRadReflect, offsetShearY = _data._offsetShearY * degRadReflect;
	for (size_t i = 0; i < _bones.size(); ++i) {
		Bone *item = _bones[i];
		Bone &bone = *item;

		bool modified = false;

		if (rotateMix != 0) {
			float a = bone._a, b = bone._b, c = bone._c, d = bone._d;
			float r = MathUtil::atan2(tc, ta) + offsetRotation;
			if (r > PI) {
				r -= PI_2;
			} else if (r < -PI) {
				r += PI_2;
			}

			r *= rotateMix;
			float cos = MathUtil::cos(r), sin = MathUtil::sin(r);
			bone._a = cos * a - sin * c;
			bone._b = cos * b - sin * d;
			bone._c = sin * a + cos * c;
			bone._d = sin * b + cos * d;
			modified = true;
		}

		if (translateMix != 0) {
			float tx, ty;
			target.localToWorld(_data._offsetX, _data._offsetY, tx, ty);
			bone._worldX += tx * translateMix;
			bone._worldY += ty * translateMix;
			modified = true;
		}

		if (scaleMix > 0) {
			float s = (MathUtil::sqrt(ta * ta + tc * tc) - 1 + _data._offsetScaleX) * scaleMix + 1;
			bone._a *= s;
			bone._c *= s;
			s = (MathUtil::sqrt(tb * tb + td * td) - 1 + _data._offsetScaleY) * scaleMix + 1;
			bone._b *= s;
			bone._d *= s;
			modified = true;
		}

		if (shearMix > 0) {
			float r = MathUtil::atan2(td, tb) - MathUtil::atan2(tc, ta);
			if (r > PI) {
				r -= PI_2;
			} else if (r < -PI) {
				r += PI_2;
			}

			float b = bone._b, d = bone._d;
			r = MathUtil::atan2(d, b) + (r - PI / 2 + offsetShearY) * shearMix;
			float s = MathUtil::sqrt(b * b + d * d);
			bone._b = MathUtil::cos(r) * s;
			bone._d = MathUtil::sin(r) * s;
			modified = true;
		}

		if (modified) {
			bone._appliedValid = false;
		}
	}
}

void TransformConstraint::applyAbsoluteLocal() {
	float rotateMix = _rotateMix, translateMix = _translateMix, scaleMix = _scaleMix, shearMix = _shearMix;
	Bone &target = *_target;
	if (!target._appliedValid) {
		target.updateAppliedTransform();
	}

	for (size_t i = 0; i < _bones.size(); ++i) {
		Bone *item = _bones[i];
		Bone &bone = *item;

		if (!bone._appliedValid) {
			bone.updateAppliedTransform();
		}

		float rotation = bone._arotation;
		if (rotateMix != 0) {
			float r = target._arotation - rotation + _data._offsetRotation;
			r -= (16384 - (int) (16384.499999999996 - r / 360)) * 360;
			rotation += r * rotateMix;
		}

		float x = bone._ax, y = bone._ay;
		if (translateMix != 0) {
			x += (target._ax - x + _data._offsetX) * translateMix;
			y += (target._ay - y + _data._offsetY) * translateMix;
		}

		float scaleX = bone._ascaleX, scaleY = bone._ascaleY;
		if (scaleMix > 0) {
			if (scaleX > 0.00001f) {
				scaleX = (scaleX + (target._ascaleX - scaleX + _data._offsetScaleX) * scaleMix) / scaleX;
			}

			if (scaleY > 0.00001f) {
				scaleY = (scaleY + (target._ascaleY - scaleY + _data._offsetScaleY) * scaleMix) / scaleY;
			}
		}

		float shearY = bone._ashearY;
		if (shearMix > 0) {
			float r = target._ashearY - shearY + _data._offsetShearY;
			r -= (16384 - (int) (16384.499999999996 - r / 360)) * 360;
			bone._shearY += r * shearMix;
		}

		bone.updateWorldTransform(x, y, rotation, scaleX, scaleY, bone._ashearX, shearY);
	}
}

void TransformConstraint::applyRelativeLocal() {
	float rotateMix = _rotateMix, translateMix = _translateMix, scaleMix = _scaleMix, shearMix = _shearMix;
	Bone &target = *_target;
	if (!target._appliedValid) {
		target.updateAppliedTransform();
	}

	for (size_t i = 0; i < _bones.size(); ++i) {
		Bone *item = _bones[i];
		Bone &bone = *item;

		if (!bone._appliedValid) {
			bone.updateAppliedTransform();
		}

		float rotation = bone._arotation;
		if (rotateMix != 0) {
			rotation += (target._arotation + _data._offsetRotation) * rotateMix;
		}

		float x = bone._ax, y = bone._ay;
		if (translateMix != 0) {
			x += (target._ax + _data._offsetX) * translateMix;
			y += (target._ay + _data._offsetY) * translateMix;
		}

		float scaleX = bone._ascaleX, scaleY = bone._ascaleY;
		if (scaleMix > 0) {
			if (scaleX > 0.00001f) {
				scaleX *= ((target._ascaleX - 1 + _data._offsetScaleX) * scaleMix) + 1;
			}

			if (scaleY > 0.00001f) {
				scaleY *= ((target._ascaleY - 1 + _data._offsetScaleY) * scaleMix) + 1;
			}
		}

		float shearY = bone._ashearY;
		if (shearMix > 0) {
			shearY += (target._ashearY + _data._offsetShearY) * shearMix;
		}

		bone.updateWorldTransform(x, y, rotation, scaleX, scaleY, bone._ashearX, shearY);
	}
}