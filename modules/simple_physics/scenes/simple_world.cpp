#include "simple_world.h"
#include "simple_area.h"
#include "simple_body.h"

SimpleWorld *SimpleWorld::singleton = NULL;

SimpleWorld *SimpleWorld::get_singleton() {
	return singleton;
}

void SimpleWorld::add_area(SimpleArea *p_area) {
	areas.push_back(p_area);
}

void SimpleWorld::remove_area(SimpleArea *p_area) {
	areas.erase(p_area);
}

void SimpleWorld::add_body(SimpleBody *p_body) {
	bodies.push_back(p_body);
}

void SimpleWorld::remove_body(SimpleBody *p_body) {
	bodies.erase(p_body);
}

bool test_collision_layers(const SimpleArea *object_a, const SimpleArea *object_b) {
    return (object_a->collision_layer & object_b->collision_mask) || (object_b->collision_layer & object_a->collision_mask);
}

bool AABB_overlaps_AABB(const SimpleArea *object_a, const SimpleArea *object_b) {
    Vector3 origin_a = object_a->get_global_transform().origin + object_a->offset;
    Vector3 origin_b = object_b->get_global_transform().origin + object_b->offset;
    Vector3 min_a = origin_a - object_a->extents;
    Vector3 min_b = origin_b - object_b->extents;
    Vector3 max_a = origin_a + object_a->extents;
    Vector3 max_b = origin_b + object_b->extents;

	return (min_b.x <= max_a.x) && (min_a.x <= max_b.x) && \
		   (min_b.y <= max_a.y) && (min_a.y <= max_b.y) && \
		   (min_b.z <= max_a.z) && (min_a.z <= max_b.z);
}

bool SimpleWorld::has_collision(const SimpleArea *p_object) {    
     if (p_object->disabled)
        return false;

    for (const List<SimpleBody *>::Element *E = bodies.front(); E; E = E->next()) {
        const SimpleBody *element = E->get();
        if (element == p_object || !test_collision_layers(p_object, element) || !AABB_overlaps_AABB(p_object, element)) {
            continue;
        }

        return true;
    }
	
	return false;
}

Array SimpleWorld::get_overlapping_areas(const SimpleArea *p_object) const {
    Array result;

    if (p_object->disabled)
        return result;
    
    for (const List<SimpleArea *>::Element *E = areas.front(); E; E = E->next()) {
        const SimpleArea *element = E->get();
        if (element == p_object || element->disabled || !test_collision_layers(p_object, element) || !AABB_overlaps_AABB(p_object, element)) {
            continue;
        }

        result.push_back(element);
    }
	
	return result;
}

Array SimpleWorld::get_overlapping_bodies(const SimpleArea *p_object) const {
    Array result;

    if (p_object->disabled)
        return result;
    
    for (const List<SimpleBody *>::Element *E = bodies.front(); E; E = E->next()) {
        const SimpleBody *element = E->get();
        if (element == p_object || element->disabled || !test_collision_layers(p_object, element) || !AABB_overlaps_AABB(p_object, element)) {
            continue;
        }

        result.push_back(element);
    }
	
	return result;
}

SimpleWorld::SimpleWorld(){
	singleton = this;
}

SimpleWorld::~SimpleWorld() {
	singleton = nullptr;
}
