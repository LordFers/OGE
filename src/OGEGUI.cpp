/*****************************************************************************
*   Open-source Game Engine (OGE) 0.1.0 programmed in C++
******************************************************************************
*   Copyright (C) 2016 - Fernando Alan Quinteros, 10th Dec 2015.
*   http://email:lordfers@gmail.com
******************************************************************************
*   This program is open-source and free software.
*   OGE used the standard libraries CEGUI 8.4.x and DirectX 9.
*   https://github.com/LordFers/OGE.git
*****************************************************************************/
#include "OGEGUI.hpp"

OGEGUI::OGEGUI(LPDIRECT3DDEVICE9 m_Direct3DDevice){
	try {
		Direct3D9Renderer &Renderer = Direct3D9Renderer::create(m_Direct3DDevice);
		System::create(Renderer); //Direct3D9Renderer::bootstrapSystem(m_Direct3DDevice);
		SetSingleton(&System::getSingleton());
		DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>(GetSingleton()->getResourceProvider());

		rp->setResourceGroupDirectory("schemes", "resources/gui/src/");
		rp->setResourceGroupDirectory("imagesets", "resources/gui/images/");
		rp->setResourceGroupDirectory("fonts", "resources/gui/fonts/");
		rp->setResourceGroupDirectory("layouts", "resources/gui/src/");
		rp->setResourceGroupDirectory("looknfeels", "resources/gui/scripts/");
		rp->setResourceGroupDirectory("lua_scripts", "resources/gui/scripts/");

		ImageManager::setImagesetDefaultResourceGroup("imagesets");
		Font::setDefaultResourceGroup("fonts");
		Scheme::setDefaultResourceGroup("schemes");
		WidgetLookManager::setDefaultResourceGroup("looknfeels");
		WindowManager::setDefaultResourceGroup("layouts");
		ScriptModule::setDefaultResourceGroup("lua_scripts");

		XMLParser* parser = GetSingleton()->getXMLParser();
		if (parser->isPropertyPresent("SchemaDefaultResourceGroup")) parser->setProperty("SchemaDefaultResourceGroup", "schemas");

		SchemeManager::getSingleton().createFromFile("GlossySerpent.scheme");
		FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

		GetSingleton()->getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
		//GetSingleton()->setDefaultMouseCursor( "TaharezLook", "MouseArrow" ); //Cursor of Mouse
		GetSingleton()->getDefaultGUIContext().setDefaultTooltipType("GlossySerpent/Tooltip");
		GetSingleton()->getDefaultGUIContext().getMouseCursor().setVisible(false);

		WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

		SetWinRoot(wmgr.createWindow("DefaultWindow", "root_wnd"));
		GetSingleton()->getDefaultGUIContext().setRootWindow(GetWinRoot());

		Window* tempWin = wmgr.loadLayoutFromFile("GUI.aoc");
		GetWinRoot()->addChild(tempWin);

	}
	catch (GenericException &e) {
		MessageBoxA(NULL, e.getMessage().c_str(), "Error OGEGUI:", NULL);
	}
}
