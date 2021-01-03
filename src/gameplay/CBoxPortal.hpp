#pragma once 

#include "gameplay/Object.hpp"
#include "engine/Model.hpp"
#include "engine/StaticMesh.hpp"
#include "gameplay/Portal.hpp"

class CBoxPortal : public Object
{
public:
	CBoxPortal(const Model& model, const TransformLayout& transLayout, const std::shared_ptr<Portal>& portalPtr)
		: Object(model, transLayout, "CBox"), _portalPtr(portalPtr)
	{

	}

	void OnOverlap() override
	{
		_portalPtr->HitCBox();
	}

private:
	std::shared_ptr<Portal> _portalPtr;
};