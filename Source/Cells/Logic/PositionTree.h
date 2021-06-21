// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <cmath>
#include <deque>
#include <vector>
#include <unordered_set>
#include <list>
#include <limits>
#include <cassert>

#include "BoundingBox.h"
#include "StorageInfo.h"

/// @brief PositionalTree allowing access to T content objects
/// T must define
// - std::array<double, 2> getPosition() const
// - std::array<double, 2> getSize() const
// - std::list<StorageInfo<T> > & getStorageInfo()
template<typename T>
class PositionalTree
{
public:
	/// @brief
	/// @param box_p box of the tree
	/// @param size_t nb of node in each dimension
	/// @param z_p z coordinate of the plan
	PositionalTree(BoundingBox const& box_p, unsigned long size_p, double z_p);

	/// @brief add a new content to the tree
	void addContent(T* content_p);
	/// @brief removed content from the tree
	void removeContent(T* content_p);

	/// @brief return the list of new position node based on the current ones and the given content
	/// @remark it is important than content_p still has its old bounding box
	void updatePositionFromNode(T& content_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p);

	/// @brief get the closest content from given position
	T* getClosestFromPosition(std::array<double, 2> const& position_p, double maxRadius_p, std::unordered_set<T*> const& ignored_p = {});

	/// @brief get all content within the given point and radius
	/// @param squared true if the radius is squared
	/// @param ignored_p this node will be excluded from the search
	std::unordered_set<T*> getAllWithinRadius(std::array<double, 2> const& position_p, double radius_p, PositionalNode<T>* ignored_p = nullptr);

	/// @brief get all content within the given point and radius
	/// @param position_p the position from where the line is thrown
	/// @param target_p the position givin the line direction
	/// @param range_p the length of the line
	std::unordered_set<T*> getAllWithinLine(std::array<double, 2> const& position_p, std::array<double, 2> const& target_p, double range_p);

	std::vector<std::vector<PositionalNode<T>* > > const& getMap() const { return _map; }
	std::list<PositionalNode<T> > const& getNodes() const { return _nodes; }
	BoundingBox const& getBox() const { return _box; }
	unsigned long const& getSize() const { return _size; }
	double getZ() const { return _z; }
protected:
	/// @brief return the deepest node intersecting the given box
	std::list<PositionalNode<T>*> getNodeIntersecting(BoundingBox const& box_p);


	/// @brief get the closest content from given position
	template<typename container_t>
	T* getClosestFromPositionDecoy(std::array<double, 2> const& position_p, container_t const& content_p, std::unordered_set<T*> const& ignored_p);

	/// @brief get the closest content from given position
	template<typename container_t>
	std::unordered_set<T*> getAllWithinRadiusDecoy(std::array<double, 2> const& position_p, double radius_p, container_t const& content_p);

	std::vector<std::vector<PositionalNode<T>* > > _map;
	std::list<PositionalNode<T> > _nodes;

	BoundingBox const _box;
	unsigned long const _size;
	/// @brief z coordinate of the plan in which the tree is positioned
	double const _z;
};

template<typename T>
class PositionalNode
{
public:
	PositionalNode(PositionalTree<T>& tree_p, BoundingBox const& box_p)
		: _tree(tree_p)
		, _box(box_p)
		, _left(nullptr)
		, _right(nullptr)
		, _up(nullptr)
		, _down(nullptr)
	{}

	/// @brief return storage index
	unsigned long addContent(T* content_p)
	{
		if (_freeIndexes.empty())
		{
			_content.push_back(content_p);
			return _content.size() - 1;
		}
		else
		{
			unsigned long index_l = _freeIndexes.front();
			_freeIndexes.pop_front();
			_content[index_l] = content_p;
			return index_l;
		}
	}

	/// @brief remove content
	void removeContent(StorageInfo<T> const& info_p)
	{
		_freeIndexes.push_back(info_p.index);
		_content[info_p.index] = nullptr;
	}

	std::list<unsigned long> const& getFreeIndexes() const { return _freeIndexes; }
	std::deque<T*> const& getContent() const { return _content; }
	BoundingBox const& getBox() const { return _box; }
	PositionalNode<T>* const& getLeft() const { return _left; }
	PositionalNode<T>* const& getRight() const { return _right; }
	PositionalNode<T>* const& getUp() const { return _up; }
	PositionalNode<T>* const& getDown() const { return _down; }

	/// @brief get the real non null content size
	size_t getContentSize() const { return _content.size() - _freeIndexes.size(); }

	T* getContent(unsigned long index_p);

protected:

	/// @brief list of indexes equal to nullptr in the deque _content
	std::list<unsigned long> _freeIndexes;
	/// @brief element in the node (some may be nullptr)
	std::deque<T*> _content;
	/// @brief reference to master tree
	PositionalTree<T>& _tree;
	/// @brief the bounding box of this node
	BoundingBox const _box;

	/// @brief all neighbours (used to update content link when moving)
	PositionalNode<T>* _left;
	PositionalNode<T>* _right;
	PositionalNode<T>* _up;
	PositionalNode<T>* _down;

	// position tree is the owner of this class
	friend class PositionalTree<T>;
};

inline std::array<double, 2> normalize(std::array<double, 2> const& array_p)
{
	double length_l = sqrt(array_p[0] * array_p[0] + array_p[1] * array_p[1]);
	return { array_p[0] / length_l, array_p[1] / length_l };
}

inline double square_distance(std::array<double, 2> const& pos1_p, std::array<double, 2> const& pos2_p)
{
	return (pos1_p[0] - pos2_p[0]) * (pos1_p[0] - pos2_p[0]) + (pos1_p[1] - pos2_p[1]) * (pos1_p[1] - pos2_p[1]);
}



template<typename T>
BoundingBox getBoundingBox(T const& content_p)
{
	return getBoundingBox<T>(content_p, content_p.getPosition());
}
template<typename T>
BoundingBox getBoundingBox(T const& content_p, std::array<double, 2> const& pos_p)
{
	return {
		{pos_p[0] - content_p.getSize()[0] / 2., pos_p[1] - content_p.getSize()[1] / 2.},		// position
		{content_p.getSize()}																// size
	};
}

template<typename T>
PositionalTree<T>::PositionalTree(BoundingBox const& box_p, unsigned long size_p, double z_p)
	: _map(size_p, std::vector<PositionalNode<T>* >(size_p, nullptr))
	, _box(box_p)
	, _size(size_p)
	, _z(z_p)
{
	// compute size of one node
	std::array<double, 2> subSize_l = { box_p.size[0] / size_p , box_p.size[1] / size_p };
	// pointers to init neighbours
	// create nodes
	for (unsigned long i = 0; i < size_p; ++i)
	{
		for (unsigned long j = 0; j < size_p; ++j)
		{
			// direct neighbours
			PositionalNode<T>* left_l = i == 0 ? nullptr : _map[i - 1][j];
			PositionalNode<T>* top_l = j == 0 ? nullptr : _map[i][j - 1];

			// create node
			_nodes.emplace_back(*this, BoundingBox({ {i * subSize_l[0], j * subSize_l[1]}, subSize_l }));
			// set up neighbour
			PositionalNode<T>& current_l = _nodes.back();
			if (top_l)
			{
				top_l->_down = &current_l;
				current_l._up = top_l;
			}
			if (left_l)
			{
				left_l->_right = &current_l;
				current_l._left = left_l;
			}
			// update map
			_map[i][j] = &current_l;
		}
	}
}
#include <sstream>

template<typename T>
void PositionalTree<T>::addContent(T* content_p)
{
	for (PositionalNode<T>* node_l : getNodeIntersecting(getBoundingBox<T>(*content_p)))
	{
		content_p->getPositionNodes().push_back(StorageInfo<T>({ node_l, node_l->addContent(content_p) }));
	}
}

template<typename T>
void PositionalTree<T>::removeContent(T* content_p)
{
	std::list<StorageInfo<T> > const& list_l = content_p->getPositionNodes();
	for (StorageInfo<T> const& info_l : list_l)
	{
		info_l.node->removeContent(info_l);
	}
	content_p->getPositionNodes().clear();
}

template<typename T>
void PositionalTree<T>::updatePositionFromNode(T& content_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p)
{
	bool moveLeft_l = oldPos_p[0] > newPos_p[0];
	bool moveRight_l = oldPos_p[0] < newPos_p[0];
	bool moveTop_l = oldPos_p[1] > newPos_p[1];
	bool moveBottom_l = oldPos_p[1] < newPos_p[1];
	// old box of content_p
	BoundingBox old_l = getBoundingBox<T>(content_p, oldPos_p);
	// new box of content_p
	BoundingBox new_l = getBoundingBox<T>(content_p, newPos_p);
	// shrink box to this box
	BoundingBox box_l = intersection(_box, new_l);
	// for each node
	std::unordered_set<PositionalNode<T>*> setAdded_l;
	auto it_l = content_p.getPositionNodes().begin();
	for (; it_l != content_p.getPositionNodes().end(); )
	{
		PositionalNode<T>* node_l = it_l->node;
		BoundingBox const& nodeBox_l = node_l->_box;
		// if moved to right
		// and old box do not oversize right
		// and new box DO
		if (moveRight_l && !oversizeRight(nodeBox_l, old_l) && oversizeRight(nodeBox_l, new_l))
		{
			PositionalNode<T>* right_l = node_l->_right;
			if (right_l && setAdded_l.find(right_l) == setAdded_l.end())
			{
				setAdded_l.insert(right_l);
				// add neighbour node
				content_p.getPositionNodes().push_back({ right_l, right_l->addContent(&content_p) });
			}
		}
		// if moved to left
		// and old box do not oversize left
		// and new box DO
		if (moveLeft_l && !oversizeLeft(nodeBox_l, old_l) && oversizeLeft(nodeBox_l, new_l))
		{
			PositionalNode<T>* left_l = node_l->_left;
			if (left_l && setAdded_l.find(left_l) == setAdded_l.end())
			{
				setAdded_l.insert(left_l);
				// add neighbour node
				content_p.getPositionNodes().push_back({ left_l, left_l->addContent(&content_p) });
			}
		}
		// if moved to top
		// and old box do not oversize top
		// and new box DO
		if (moveTop_l && !oversizeTop(nodeBox_l, old_l) && oversizeTop(nodeBox_l, new_l))
		{
			PositionalNode<T>* top_l = node_l->_up;
			if (top_l && setAdded_l.find(top_l) == setAdded_l.end())
			{
				setAdded_l.insert(top_l);
				// add neighbour node
				content_p.getPositionNodes().push_back({ top_l, top_l->addContent(&content_p) });
			}
		}
		// if moved to bottom
		// and old box do not oversize bottom
		// and new box DO
		if (moveBottom_l && !oversizeBottom(nodeBox_l, old_l) && oversizeBottom(nodeBox_l, new_l))
		{
			PositionalNode<T>* bottom_l = node_l->_down;
			if (bottom_l && setAdded_l.find(bottom_l) == setAdded_l.end())
			{
				setAdded_l.insert(bottom_l);
				// add neighbour node
				content_p.getPositionNodes().push_back({ bottom_l, bottom_l->addContent(&content_p) });
			}
		}
		// if box and node do not intersect anymore remove it
		if (empty(intersection(nodeBox_l, new_l)))
		{
			// remove content from node
			node_l->removeContent(*it_l);
			// remove node from content
			it_l = content_p.getPositionNodes().erase(it_l);
		}
		else
		{
			++it_l;
		}
	}
}

template<typename T>
T* PositionalTree<T>::getClosestFromPosition(std::array<double, 2> const& position_p, double maxRadius_p, std::unordered_set<T*> const& ignored_p)
{
	// get node where position is
	long x = (position_p[0] - _box.position[0]) / (_box.size[0] / _size);
	long y = (position_p[1] - _box.position[1]) / (_box.size[1] / _size);
	// crop indexes
	x = std::max<long>(0, std::min<long>(x, long(_size) - 1));
	y = std::max<long>(0, std::min<long>(y, long(_size) - 1));
	PositionalNode<T>* current_l = _map[x][y];
	assert(current_l);
	T* closest_l = getClosestFromPositionDecoy(position_p, current_l->_content, ignored_p);
	double sqDist_l = std::numeric_limits<double>::max();
	if (closest_l)
	{
		// compute distance to closest
		sqDist_l = (closest_l->getPosition()[0] - position_p[0]) * (closest_l->getPosition()[0] - position_p[0])
			+ (closest_l->getPosition()[1] - position_p[1]) * (closest_l->getPosition()[1] - position_p[1]);

		std::unordered_set<T*> listClosest_l = getAllWithinRadius(position_p, sqrt(sqDist_l), current_l);
		listClosest_l.insert(closest_l);
		closest_l = getClosestFromPositionDecoy(position_p, listClosest_l, ignored_p);
	}
	else
	{
		// compute min distance from neighbours
		std::unordered_set<T*> listClosest_l = getAllWithinRadius(position_p, maxRadius_p);
		closest_l = getClosestFromPositionDecoy(position_p, listClosest_l, ignored_p);
	}

	if (closest_l)
	{
		sqDist_l = (closest_l->getPosition()[0] - position_p[0]) * (closest_l->getPosition()[0] - position_p[0])
			+ (closest_l->getPosition()[1] - position_p[1]) * (closest_l->getPosition()[1] - position_p[1]);
		if (sqDist_l > maxRadius_p * maxRadius_p)
		{
			closest_l = nullptr;
		}
	}

	return closest_l;
}

template<typename T>
std::unordered_set<T*> PositionalTree<T>::getAllWithinRadius(std::array<double, 2> const& position_p, double radius_p, PositionalNode<T>* ignored_p)
{
	BoundingBox simplifiedRadius_l = {
		{position_p[0] - radius_p, position_p[1] - radius_p},
		{2 * radius_p, 2 * radius_p}
	};
	std::unordered_set<T*> all_l;
	std::list<PositionalNode<T>*> nodes_l = getNodeIntersecting(simplifiedRadius_l);
	for (PositionalNode<T>* node_l : nodes_l)
	{
		if (node_l != ignored_p)
		{
			std::unordered_set<T*> newAll_l = getAllWithinRadiusDecoy(position_p, radius_p, node_l->_content);
			all_l.insert(newAll_l.begin(), newAll_l.end());
		}
	}

	return all_l;
}

template<typename T>
std::unordered_set<T*> PositionalTree<T>::getAllWithinLine(std::array<double, 2> const& position_p, std::array<double, 2> const& target_p, double range_p)
{
	std::array<double, 2> direction_l = {
		target_p[0] - position_p[0],
		target_p[1] - position_p[1]
	};
	direction_l = normalize(direction_l);
	// index start line
	long min_x = (position_p[0] - _box.position[0]) / (_box.size[0] / _size);
	long min_y = (position_p[1] - _box.position[1]) / (_box.size[1] / _size);
	// index end line
	long max_x = (position_p[0] - _box.position[0] + range_p * direction_l[0]) / (_box.size[0] / _size);
	long max_y = (position_p[1] - _box.position[1] + range_p * direction_l[1]) / (_box.size[1] / _size);
	// adjust max index
	max_x = std::min<long>(max_x, _size - 1);
	max_y = std::min<long>(max_y, _size - 1);

	std::unordered_set<T*> all_l;

	// for every node potentially intersecting the line
	for (long x = std::min(min_x, max_x); x <= std::max(min_x, max_x); ++x)
	{
		for (long y = std::min(min_y, max_y); y <= std::max(min_y, max_y); ++y)
		{
			// check every content of node
			PositionalNode<T>* node_l = _map[x][y];

			for (T* content_l : node_l->getContent())
			{
				// can have null elt
				if (!content_l) { continue; }
				BoundingBox box_l = getBoundingBox(*content_l);

				PositionalHitbox hitbox_l;
				hitbox_l.pos = { box_l.position[0], box_l.position[1], 0. };
				hitbox_l.hitbox.size = { box_l.size[0], box_l.size[1], 0. };
				double contact_l = collide({ position_p[0], position_p[1], 0. }, { direction_l[0], direction_l[1], 0. }, hitbox_l);
				// if range is within given range limit
				if (contact_l >= 0. && range_p >= contact_l)
				{
					all_l.insert(content_l);
				}
			}
		}
	}

	return all_l;
}


template<typename T>
std::list<PositionalNode<T>*> PositionalTree<T>::getNodeIntersecting(BoundingBox const& box_p)
{
	BoundingBox shrinked_l = intersection(box_p, _box);
	//
	long min_x = (shrinked_l.position[0] - _box.position[0]) / (_box.size[0] / _size);
	long min_y = (shrinked_l.position[1] - _box.position[1]) / (_box.size[1] / _size);
	//
	long max_x = (shrinked_l.position[0] + shrinked_l.size[0] - _box.position[0]) / (_box.size[0] / _size);
	long max_y = (shrinked_l.position[1] + shrinked_l.size[1] - _box.position[1]) / (_box.size[1] / _size);
	// adjust max index
	max_x = std::min<long>(max_x, _size - 1);
	max_y = std::min<long>(max_y, _size - 1);
	std::list<PositionalNode<T>*> list_l;
	for (long x = min_x; x <= max_x; ++x)
		for (long y = min_y; y <= max_y; ++y)
			list_l.push_back(_map[x][y]);
	return list_l;
}


template<typename T>
template<typename container_t>
T* PositionalTree<T>::getClosestFromPositionDecoy(std::array<double, 2> const& position_p, container_t const& content_p, std::unordered_set<T*> const& ignored_p)
{
	double sqMinDist_l = 0.;
	T* closest_l = nullptr;
	for (T* elt_l : content_p)
	{
		// can have null elt
		if (!elt_l) { continue; }
		// skip if ignored
		if (ignored_p.find(elt_l) != ignored_p.end()) { continue; }

		double sqDist_l = (elt_l->getPosition()[0] - position_p[0]) * (elt_l->getPosition()[0] - position_p[0])
			+ (elt_l->getPosition()[1] - position_p[1]) * (elt_l->getPosition()[1] - position_p[1]);
		if (!closest_l || sqDist_l < sqMinDist_l)
		{
			closest_l = elt_l;
			sqMinDist_l = sqDist_l;
		}
	}
	return closest_l;
}

template<typename T>
template<typename container_t>
std::unordered_set<T*> PositionalTree<T>::getAllWithinRadiusDecoy(std::array<double, 2> const& position_p, double radius_p, container_t const& content_p)
{
	double sqRadius_l = radius_p * radius_p;
	std::unordered_set<T*> list_l;
	for (T* elt_l : content_p)
	{
		// can have null elt
		if (!elt_l) { continue; }
		double sqDist_l = (elt_l->getPosition()[0] - position_p[0]) * (elt_l->getPosition()[0] - position_p[0])
			+ (elt_l->getPosition()[1] - position_p[1]) * (elt_l->getPosition()[1] - position_p[1]);
		if (sqDist_l <= sqRadius_l)
		{
			list_l.insert(elt_l);
		}
	}
	return list_l;
}

template<typename T>
T* PositionalNode<T>::getContent(unsigned long index_p)
{
	unsigned long cur_l = 0;
	for (T* content_l : _content)
	{
		if (content_l)
		{
			if (cur_l == index_p)
			{
				return content_l;
			}
			++cur_l;
		}
	}
	return nullptr;
}
