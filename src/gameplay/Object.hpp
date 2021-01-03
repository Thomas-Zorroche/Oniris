#pragma once
#include "engine/Model.hpp"
#include <string>
#include "glm/glm.hpp"

class StaticMesh;
class TransformLayout;
class InputHandler;

//
// Object is an Interface 
//
class Object
{
public:
	Object(const Model& model, const TransformLayout& transLayout, const std::string& panelName = "", const std::string& shaderName = "Model3D_Tex");
	virtual ~Object();

	void Draw();

	bool IsInWorld() const { return _InWorld; }

	virtual void OnOverlap() = 0;

	static void SetInputHandlerPtr(InputHandler* inputHandler);

	void Free();

protected:
	std::shared_ptr<StaticMesh> _staticMesh;
	std::string _panelName;
	bool _InWorld = true;

	static InputHandler* s_inputHandler;
};

