#include "BoundingBox.h"

#include <limits>

/// @brief compute intersection of boxes
BoundingBox intersection(BoundingBox const& box1_p, BoundingBox const& box2_p)
{
	BoundingBox box_l = {
			{std::max(box1_p.position[0], box2_p.position[0]), std::max(box1_p.position[1], box2_p.position[1])},
			{std::min(box1_p.position[0] + box1_p.size[0], box2_p.position[0] + box2_p.size[0])
				, std::min(box1_p.position[1] + box1_p.size[1], box2_p.position[1] + +box2_p.size[1])}
	};
	box_l.size[0] = box_l.size[0] - box_l.position[0];
	box_l.size[1] = box_l.size[1] - box_l.position[1];
	return box_l;
}

/// @brief check if bounding box is empty (any size <= 0)
bool empty(BoundingBox const& box_p)
{
	return box_p.size[0] <= 0. || box_p.size[1] <= 0.;
}

/// @brief check if other_p was oversizing ref on the left (pos)
bool oversizeLeft(BoundingBox const& ref_p, BoundingBox const& other_p)
{
	return ref_p.position[0] > other_p.position[0];
}

/// @brief check if other_p was oversizing ref on the left (pos + size)
bool oversizeRight(BoundingBox const& ref_p, BoundingBox const& other_p)
{
	return ref_p.position[0] + ref_p.size[0] < other_p.position[0] + other_p.size[0];
}

/// @brief check if other_p was oversizing ref on the left (pos)
bool oversizeTop(BoundingBox const& ref_p, BoundingBox const& other_p)
{
	return ref_p.position[1] > other_p.position[1];
}

/// @brief check if other_p was oversizing ref on the left (pos + size)
bool oversizeBottom(BoundingBox const& ref_p, BoundingBox const& other_p)
{
	return ref_p.position[1] + ref_p.size[1] < other_p.position[1] + other_p.size[1];
}

std::ostream& operator<<(std::ostream& os_p, BoundingBox const& box_p)
{
	os_p << "Box["
		<< "position: (" << box_p.position[0] << ", " << box_p.position[1] << "), "
		<< "size: (" << box_p.size[0] << ", " << box_p.size[1] << ")]";
	return os_p;
}

/// @brief check if a ray (orig_p -dir_p-> ) collide with the positioned hitbox
/// @param orig_p the origin of the ray
/// @param dir_p the direction of the ray
/// @param hitbox_p the hitbox to be tested
/// @return return the distance (in norm of dir_p!), negative if no contact
double collide(std::array<double, 3> const& orig_p, std::array<double, 3> const& dir_p, PositionalHitbox const& hitbox_p)
{
	std::array<double, 3> boxLB_l = {
		hitbox_p.hitbox.offset[0] + hitbox_p.pos[0],
		hitbox_p.hitbox.offset[1] + hitbox_p.pos[1],
		hitbox_p.hitbox.offset[2] + hitbox_p.pos[2]
	};
	std::array<double, 3> boxUB_l = {
		hitbox_p.hitbox.offset[0] + hitbox_p.pos[0] + hitbox_p.hitbox.size[0],
		hitbox_p.hitbox.offset[1] + hitbox_p.pos[1] + hitbox_p.hitbox.size[1],
		hitbox_p.hitbox.offset[2] + hitbox_p.pos[2] + hitbox_p.hitbox.size[2]
	};

	// default value = blocking value that will make final test fail
	std::array<double, 3> lower_l = {
		std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max()
	};
	std::array<double, 3> upper_l = {
		std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min()
	};
	// for each coordinate
	for (size_t i = 0; i < 3; ++i)
	{
		// if no direction check directly if origin is in bound
		if (std::abs(dir_p[i]) < 1e-5)
		{
			// check if in bounds
			if (orig_p[i] <= boxUB_l[i] && orig_p[i] >= boxLB_l[i])
			{
				lower_l[i] = std::numeric_limits<double>::min();
				upper_l[i] = std::numeric_limits<double>::max();
			}
		}
		else
		{
			lower_l[i] = std::min((boxLB_l[i] - orig_p[i]) / dir_p[i], (boxUB_l[i] - orig_p[i]) / dir_p[i]);
			upper_l[i] = std::max((boxLB_l[i] - orig_p[i]) / dir_p[i], (boxUB_l[i] - orig_p[i]) / dir_p[i]);
		}
	}

	if (std::min(upper_l[0], std::min(upper_l[1], upper_l[2])) >= std::max(lower_l[0], std::max(lower_l[1], lower_l[2])))
	{
		return std::max(0., std::max(lower_l[0], std::min(lower_l[1], lower_l[2])));
	}
	return -1.;
}
