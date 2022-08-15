#ifndef SIMPLE_WORLD_H
#define SIMPLE_WORLD_H

#include <core/object.h>

class SimpleArea;
class SimpleBody;

class SimpleWorld : public Object {
    GDCLASS(SimpleWorld, Object);

    static SimpleWorld *singleton;

	List<SimpleArea *> areas;
	List<SimpleBody *> bodies;

public:
	// struct ShapeOverlapInfo {
	// 	SGShape2DInternal *shape;
	// 	SGFixedVector2Internal separation;
	// 	SGFixedVector2Internal collision_normal;

	// 	ShapeOverlapInfo() {
	// 		shape = nullptr;
	// 	}
	// };

	struct BodyOverlapInfo {
		SimpleBody *collider;
		// SGFixedVector2Internal separation;
		Vector2 collision_normal;

		BodyOverlapInfo() {
			collider = nullptr;
		}
	};

	struct RayCastInfo {
		SimpleBody *body;
		Vector2 collision_point;
		Vector2 collision_normal;

		RayCastInfo() {
			body = nullptr;
		}
	};

	// typedef bool (*CompareCallback)(SGCollisionObject2DInternal*, SGCollisionObject2DInternal*);

	static SimpleWorld *get_singleton();

	_FORCE_INLINE_ const List<SimpleBody *> &get_bodies() const { return bodies; }
	_FORCE_INLINE_ const List<SimpleArea *> &get_areas() const { return areas; }
	// _FORCE_INLINE_ const SGBroadphase2DInternal *get_broadphase() const { return broadphase; }

	void add_area(SimpleArea *p_area);
	void remove_area(SimpleArea *p_area);
	void add_body(SimpleBody *p_body);
	void remove_body(SimpleBody *p_body);

	
    bool has_collision(const SimpleArea *p_object);
	Array get_overlapping_areas(const SimpleArea *p_object) const;
	Array get_overlapping_bodies(const SimpleArea *p_object) const;

	// bool segment_intersects_shape(const SGFixedVector2Internal &p_start, const SGFixedVector2Internal &p_cast_to, SGShape2DInternal *p_shape, SGFixedVector2Internal &p_intersection_point, SGFixedVector2Internal &p_collision_normal) const;
	// bool cast_ray(const SGFixedVector2Internal &p_start, const SGFixedVector2Internal &p_cast_to, uint32_t p_collision_mask, Set<SGCollisionObject2DInternal *> *p_exceptions = nullptr,
	// 	bool collide_with_areas=false, bool collide_with_bodies=true, RayCastInfo *p_info = nullptr) const;

	SimpleWorld();
	~SimpleWorld();
};

#endif
