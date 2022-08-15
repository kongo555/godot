#include "simple_area.h"

#include <core/engine.h>
#include <math.h>

#include "simple_world.h"

void SimpleArea::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_overlapping_areas"), &SimpleArea::get_overlapping_areas);
    ClassDB::bind_method(D_METHOD("get_overlapping_bodies"), &SimpleArea::get_overlapping_bodies);

    ClassDB::bind_method(D_METHOD("get_offset"), &SimpleArea::get_offset);
	ClassDB::bind_method(D_METHOD("set_offset", "offset"), &SimpleArea::set_offset);

    ClassDB::bind_method(D_METHOD("get_extents"), &SimpleArea::get_extents);
	ClassDB::bind_method(D_METHOD("set_extents", "extents"), &SimpleArea::set_extents);

	ClassDB::bind_method(D_METHOD("get_collision_layer"), &SimpleArea::get_collision_layer);
	ClassDB::bind_method(D_METHOD("set_collision_layer", "collision_layer"), &SimpleArea::set_collision_layer);
	ClassDB::bind_method(D_METHOD("get_collision_mask"), &SimpleArea::get_collision_mask);
	ClassDB::bind_method(D_METHOD("set_collision_mask", "collision_mask"), &SimpleArea::set_collision_mask);

	ClassDB::bind_method(D_METHOD("set_collision_layer_bit", "bit", "value"), &SimpleArea::set_collision_layer_bit);
	ClassDB::bind_method(D_METHOD("get_collision_layer_bit"), &SimpleArea::get_collision_layer_bit);
	ClassDB::bind_method(D_METHOD("set_collision_mask_bit", "bit", "value"), &SimpleArea::set_collision_mask_bit);
	ClassDB::bind_method(D_METHOD("get_collision_mask_bit"), &SimpleArea::get_collision_mask_bit);

    ClassDB::bind_method(D_METHOD("get_disabled"), &SimpleArea::get_disabled);
	ClassDB::bind_method(D_METHOD("set_disabled", "disabled"), &SimpleArea::set_disabled);

	// ADD_GROUP("Collision", "collision_");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "extents"), "set_extents", "get_extents");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "offset"), "set_offset", "get_offset");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "collision_layer", PROPERTY_HINT_LAYERS_3D_PHYSICS), "set_collision_layer", "get_collision_layer");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "collision_mask", PROPERTY_HINT_LAYERS_3D_PHYSICS), "set_collision_mask", "get_collision_mask");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "disabled"), "set_disabled", "get_disabled");
}

void SimpleArea::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE:
			add_to_world(SimpleWorld::get_singleton());
			break;
		
		case NOTIFICATION_READY:
			break;

		case NOTIFICATION_EXIT_TREE:
			remove_from_world(SimpleWorld::get_singleton());
			break;
	}
}

void SimpleArea::add_to_world(SimpleWorld *p_world) const {
	p_world->add_area((SimpleArea *)this);
}

void SimpleArea::remove_from_world(SimpleWorld *p_world) const {
	p_world->remove_area((SimpleArea *)this);
}

Array SimpleArea::get_overlapping_areas() const {
	return SimpleWorld::get_singleton()->get_overlapping_areas(this);
}

Array SimpleArea::get_overlapping_bodies() const {
	return SimpleWorld::get_singleton()->get_overlapping_bodies(this);
}

Vector3 SimpleArea::get_extents() const {
	return extents;
}

void SimpleArea::set_extents(Vector3 p_extents) {
	extents = p_extents;
}

Vector3 SimpleArea::get_offset() const {
	return offset;
}

void SimpleArea::set_offset(Vector3 p_offset) {
	offset = p_offset;
}

bool SimpleArea::get_disabled() const {
	return disabled;
}

void SimpleArea::set_disabled(bool p_disabled) {
	disabled = p_disabled;
}

uint32_t SimpleArea::get_collision_layer() const {
	return collision_layer;
}

void SimpleArea::set_collision_layer(uint32_t p_collision_layer) {
	collision_layer = p_collision_layer;
	// _change_notify("collision_layer");
}

uint32_t SimpleArea::get_collision_mask() const {
	return collision_mask;
}
void SimpleArea::set_collision_mask(uint32_t p_collision_mask) {
	collision_mask = p_collision_mask;
	// _change_notify("collision_mask");
}

void SimpleArea::set_collision_layer_bit(int p_bit, bool p_value) {
	uint32_t l = collision_layer;
	if (p_value) {
		l |= (1 << p_bit);
	}
	else {
		l &= ~(1 << p_bit);
	}
	set_collision_layer(l);
}

bool SimpleArea::get_collision_layer_bit(int p_bit) const {
	return get_collision_layer() & (1 << p_bit);
}

void SimpleArea::set_collision_mask_bit(int p_bit, bool p_value) {
	uint32_t m = collision_mask;
	if (p_value) {
		m |= (1 << p_bit);
	}
	else {
		m &= ~(1 << p_bit);
	}
	set_collision_mask(m);
}

bool SimpleArea::get_collision_mask_bit(int p_bit) const {
	return get_collision_mask() & (1 << p_bit);
}

SimpleArea::SimpleArea() {
	collision_layer = 1;
	collision_mask = 1;

    offset = Vector3();
    extents = Vector3();

    disabled = false;
}

SimpleArea::~SimpleArea() {
}
