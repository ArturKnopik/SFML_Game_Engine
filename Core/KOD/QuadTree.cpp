#include "QuadTree.h"

bool KOD::QuadTree::insert(std::shared_ptr<IGameObject> obj)
{
	if (obj->getSolid() != nullptr) return false;

	if (!isLeaf) {
		// insert object into leaf
		if (QuadTree* child = getChild(obj->getSize()))
			return child->insert(obj);
	}
	objects.push_back(obj);
	//obj->qt = this;

	// Subdivide if required
	if (isLeaf && level < maxLevel && objects.size() >= capacity) {
		subdivide();
		update(obj);
	}
	return true;
}
