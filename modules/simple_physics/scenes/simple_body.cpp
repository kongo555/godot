#include "simple_body.h"

#include <core/engine.h>
#include <math.h>

#include "simple_world.h"

void SimpleBody::_bind_methods() {
    // SimpleArea::_bind_methods();
	ClassDB::bind_method(D_METHOD("move_and_slide"), &SimpleBody::move_and_slide);
    
    ClassDB::bind_method(D_METHOD("get_remainder"), &SimpleBody::get_remainder);
    ClassDB::bind_method(D_METHOD("set_remainder", "remainder"), &SimpleBody::set_remainder);

    ClassDB::bind_method(D_METHOD("get_collision_normal"), &SimpleBody::get_collision_normal);
    ClassDB::bind_method(D_METHOD("set_collision_normal", "collision_normal"), &SimpleBody::set_collision_normal);

    ClassDB::bind_method(D_METHOD("get_on_wall"), &SimpleBody::get_on_wall);
	ClassDB::bind_method(D_METHOD("set_on_wall", "on_wall"), &SimpleBody::set_on_wall);
    ClassDB::bind_method(D_METHOD("get_on_floor"), &SimpleBody::get_on_floor);
	ClassDB::bind_method(D_METHOD("set_on_floor", "on_floor"), &SimpleBody::set_on_floor);
    ClassDB::bind_method(D_METHOD("get_on_ceiling"), &SimpleBody::get_on_ceiling);
	ClassDB::bind_method(D_METHOD("set_on_ceiling", "on_ceiling"), &SimpleBody::set_on_ceiling);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "remainder"), "set_remainder", "get_remainder");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "collision_normal"), "set_collision_normal", "get_collision_normal");

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "on_wall"), "set_on_wall", "get_on_wall");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "on_floor"), "set_on_floor", "get_on_floor");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "on_ceiling"), "set_on_ceiling", "get_on_ceiling");
}

void SimpleBody::add_to_world(SimpleWorld *p_world) const {
	p_world->add_body((SimpleBody *)this);
}

void SimpleBody::remove_from_world(SimpleWorld *p_world) const {
	p_world->remove_body((SimpleBody *)this);
}

int sign(int val) {
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

void SimpleBody::move_and_slide(real_t p_delta, Vector3 p_linear_velocity) {
    on_wall = false;
    on_floor = false;
    on_ceiling = false;
    collision_normal = Vector3();

    // bool has_collision = false;
    Transform transform = get_global_transform();
    
    // x
    {
        remainder.x += p_linear_velocity.x * p_delta;
        int move = (int) floorf(remainder.x);
        remainder.x -= move;
        int dir = sign(move);

        while (move != 0) {
            transform.origin.x += dir;
            set_global_transform(transform);
            move -= dir;

            if (SimpleWorld::get_singleton()->has_collision(this)) {
                transform.origin.x -= dir;
                set_global_transform(transform);
                // has_collision = true;
                on_wall = true;

                if (p_linear_velocity.x > 0) {
                    collision_normal.x = 1;
                } else {
                    collision_normal.x = -1;
                }

                break;
            }
        }
    }

    // z
    {
        remainder.z += p_linear_velocity.z * p_delta;
        int move = (int) floorf(remainder.z);
        remainder.z -= move;
        int dir = sign(move);

        while (move != 0) {
            transform.origin.z += dir;
            set_global_transform(transform);
            move -= dir;

            if (SimpleWorld::get_singleton()->has_collision(this)) {
                transform.origin.z -= dir;
                set_global_transform(transform);
                // has_collision = true;
                on_wall = true;

                if (p_linear_velocity.z > 0) {
                    collision_normal.z = 1;
                } else {
                    collision_normal.z = -1;
                }
                
                break;
            }

        }
    }
    // y
    {
        remainder.y += p_linear_velocity.y * p_delta;
        int move = (int) floorf(remainder.y);
        remainder.y -= move;
        int dir = sign(move);

        while (move != 0) {
            transform.origin.y += dir;
            set_global_transform(transform);
            move -= dir;

            if (SimpleWorld::get_singleton()->has_collision(this)) {
                transform.origin.y -= dir;
                set_global_transform(transform);

                if (p_linear_velocity.y > 0) {
                    on_ceiling = true;
                } else {
                    on_floor = true;
                }

                // has_collision = true;
                break;
            }
        }
    }
    
    // set_global_transform(transform);
}

Vector3 SimpleBody::get_remainder() const {
	return remainder;
}

void SimpleBody::set_remainder(Vector3 p_remainder) {
	remainder = p_remainder;
}

Vector3 SimpleBody::get_collision_normal() const {
	return collision_normal;
}

void SimpleBody::set_collision_normal(Vector3 p_collision_normal) {
	collision_normal = p_collision_normal;
}

bool SimpleBody::get_on_wall() const {
	return on_wall;
}

void SimpleBody::set_on_wall(bool p_on_wall) {
	on_wall = p_on_wall;
}

bool SimpleBody::get_on_floor() const {
	return on_floor;
}

void SimpleBody::set_on_floor(bool p_on_floor) {
	on_floor = p_on_floor;
}

bool SimpleBody::get_on_ceiling() const {
	return on_ceiling;
}

void SimpleBody::set_on_ceiling(bool p_on_ceiling) {
	on_ceiling = p_on_ceiling;
}

SimpleBody::SimpleBody() {
    remainder = Vector3();
    collision_normal = Vector3();
    on_wall = false;
	on_floor = false;
    on_ceiling = false;
}

SimpleBody::~SimpleBody() {
}
