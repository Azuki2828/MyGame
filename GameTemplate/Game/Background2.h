#pragma once
#include "stdafx.h"
/// <summary>
/// 背景クラス。
/// </summary>
class Background2 : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
private:
	Model m_model;								//モデル
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト・
};

