#include "stdafx.h"
#include "LightManager.h"


LightManager* LightManager::m_lightManager = nullptr;

void LightManager::AddLight(LightBase* light) {

	if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
		MessageBoxA(nullptr, "これ以上ディレクションライトを置けないよ！", "たいへん！", MB_OK);
		return;
	}

	const std::type_info& typeInfo = typeid(*light);

	if (typeInfo == typeid(DirectionLight)) {

		//登録済みか調べる。
		auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light->GetLigData());
		if (findIt == m_directionLights.end()) {
			//新規登録。
			m_directionLights.push_back(reinterpret_cast<DirectionLigData*>(light->GetLigData()));

			int a = 0;
			std::list<DirectionLigData*>::iterator itr;
			itr = m_directionLights.begin();

			//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
			//	m_ligData.m_directionLigData[i] = nullptr;
			//}
			for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

				m_ligData.m_directionLigData[a] = *(*itr);
				a++;
			}
		}
		else {
			//既に登録されてるよ。
			MessageBoxA(nullptr, "既に登録されてるよ！！", "たいへん！", MB_OK);
			return;
		}
	}

}

void LightManager::RemoveLight(LightBase* light)
{
	const std::type_info& typeInfo = typeid(*light);
	
	if (typeInfo == typeid(DirectionLight)) {
		m_directionLights.erase(
			std::remove(m_directionLights.begin(), m_directionLights.end(), light->GetLigData()),
			m_directionLights.end()
		);

		int a = 0;

		//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		//	m_ligData.m_directionLigData[i] = nullptr;
		//}
		for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

			m_ligData.m_directionLigData[a] = *(*itr);
			a++;
		}
	}
}

void LightManager::Update() {
	m_ligData.ambient.Set(0.3f, 0.3f, 0.3f);
	m_lightManager->m_ligData.eyePos = g_camera3D->GetPosition();


	for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

		int a = 0;
		m_ligData.m_directionLigData[a] = *(*itr);
		a++;
	}

	m_lightManager->m_ligData.m_viewProj = Camera::GetLightCamera()->GetViewProjectionMatrix();
}