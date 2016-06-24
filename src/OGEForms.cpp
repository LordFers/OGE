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
#include "OGEForms.hpp"

template <typename T> std::string NumberToString(T Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

void OGEForms::LoadForms(){
	FConnect_Load();
	FCreateCharacter_Load();
	FErrorWindow_UnLoad();
	FMain_Load();
}

void OGEForms::FConnect_Load(){
	Window* FConnect = GetWinRoot()->getChild("AllForm")->getChild("ConnectArea");

	FConnect->getChild("Connect")->setVisible(true);
	FConnect->getChild("Connect")->setPosition(UVector2(UDim(0, 480), UDim(0, 280)));
	FConnect->getChild("Connect/ButtonConnect")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FConnect_MouseButtonUp, this));
	FConnect->getChild("Connect/ButtonCreatePJ")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FConnect_MouseButtonUp_CP, this));
	FConnect->getChild("ButtonExit")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FConnect_MouseButtonUp_Exit, this));
	GetGame()->GetAudio()->PlayMIDI("6.ogg");
}

void OGEForms::FConnect_Visible(bool m_Visible) {
	Window* FConnect = GetWinRoot()->getChild("AllForm")->getChild("ConnectArea");

	if (FConnect->isVisible() == m_Visible) return;

	FConnect->setVisible(m_Visible);
	FConnect->getChild("Connect")->getChild("UserText")->setText("BetaTester");
	FConnect->getChild("Connect")->getChild("PasswordText")->setText("");

	if (m_Visible == true)
		GetGame()->GetAudio()->PlayMIDI("6.ogg");
}

void OGEForms::FConnect_Login() {
	if (m_Game->GetConnected()) return;
	Window* FConnect = GetWinRoot()->getChild("AllForm")->getChild("ConnectArea")->getChild("Connect");

	std::string m_Name = FConnect->getChild("UserText")->getText().c_str();
	std::string m_Password = FConnect->getChild("PasswordText")->getText().c_str();

	if (m_Name.size() < 1) {
		MessageBoxA(NULL, "Debes ingresar un nombre antes de intentar conectarte.", "Argentum Online", NULL);
		return;
	}

	if (m_Password.size() < 1) {
		MessageBoxA(NULL, "Debes ingresar una contraseña antes de intentar conectarte.", "Argentum Online", NULL);
		return;
	}

	GetGame()->GetProtocol()->Connect();
	GetGame()->GetProtocol()->WriteLoginExistingChar(FConnect->getChild("UserText")->getText().c_str(), FConnect->getChild("PasswordText")->getText().c_str());
	GetGame()->GetProtocol()->FlushBuffer();
}

bool OGEForms::FConnect_MouseButtonUp(const EventArgs &e){
	GetGame()->GetAudio()->PlayWAV("click.wav");
	FConnect_Login();
	return false;
}

bool OGEForms::FConnect_MouseButtonUp_CP(const EventArgs &e) {
	GetGame()->GetProtocol()->Connect();
	GetGame()->GetProtocol()->WriteThrowDices();
	return false;
}

bool OGEForms::FConnect_MouseButtonUp_Exit(const EventArgs &e) {
	GetGame()->GetEngine()->setRun(false);
	return false;
}

//Form CP:

void OGEForms::FCreateCharacter_Load() {
	Window* FCreateCharacter = GetWinRoot()->getChild("AllForm")->getChild("CrearPJArea");

	Combobox* RazaCombo = static_cast<Combobox*>(FCreateCharacter->getChild("RazaCombo"));
	std::string Razas[5] = { "Humano", "Elfo", "Elfo Oscuro", "Gnomo", "Enano" };
	for (int i = 0; i < 5; ++i) {
		RazaCombo->addItem(new ListboxTextItem(Razas[i]));
	}

	Combobox* GeneroCombo = static_cast<Combobox*>(FCreateCharacter->getChild("GeneroCombo"));
	std::string Genero[2] = { "Hombre", "Mujer" };
	for (int i = 0; i < 2; ++i) {
		GeneroCombo->addItem(new ListboxTextItem(Genero[i]));
	}

	Combobox* ClaseCombo = static_cast<Combobox*>(FCreateCharacter->getChild("ClaseCombo"));
	std::string Clases[12] = { "Mago", "Clerigo", "Guerrero", "Asesino", "Ladron", "Bardo", "Druida", "Bandido", "Paladin", "Cazador", "Trabajador", "Pirata" };
	for (int i = 0; i < 12; ++i) {
		ClaseCombo->addItem(new ListboxTextItem(Clases[i]));
	}

	Combobox* HogarCombo = static_cast<Combobox*>(FCreateCharacter->getChild("HogarCombo"));
	std::string Hogar[5] = { "Ullathorpe", "Nix", "Banderbill", "Lindos", "Arghâl" };
	for (int i = 0; i < 5; ++i) {
		HogarCombo->addItem(new ListboxTextItem(Hogar[i]));
	}

	(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FConnect_MouseButtonUp_Exit, this));
	FCreateCharacter->getChild("BackButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FCreateCharacter_MouseButtonUp_Back, this));
	FCreateCharacter->getChild("ThrowDices")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FCreateCharacter_MouseButtonUp_ThrowDices, this));
	FCreateCharacter->getChild("CrearPJButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FCreateCharacter_MouseButtonUp_CreateCharacter, this));
	FCreateCharacter->setVisible(false);
}

void OGEForms::FCreateCharacter_Visible(bool m_Visible) {
	Window* FCreateCharacter = GetWinRoot()->getChild("AllForm")->getChild("CrearPJArea");

	if (FCreateCharacter->isVisible() == m_Visible) return;

	FCreateCharacter->setVisible(m_Visible);
	FCreateCharacter->getChild("NameText")->setText("BetaTester");
	//GetGame()->set_inCP(m_Visible);
}

void OGEForms::FCreateCharacter_setAttributes(unsigned char m_Strength, unsigned char m_Agility,
	unsigned char m_Intelligence, unsigned char m_Charisma,
	unsigned char m_Constitution) {

	Window* FCreateCharacter = GetWinRoot()->getChild("AllForm")->getChild("CrearPJArea");

	FCreateCharacter->getChild("FuerzaValue")->setText(NumberToString((int)m_Strength));
	FCreateCharacter->getChild("AgilidadValue")->setText(NumberToString((int)m_Agility));
	FCreateCharacter->getChild("InteligenciaValue")->setText(NumberToString((int)m_Intelligence));
	FCreateCharacter->getChild("CarismaValue")->setText(NumberToString((int)m_Charisma));
	FCreateCharacter->getChild("ConstitucionValue")->setText(NumberToString((int)m_Constitution));
}

bool OGEForms::FCreateCharacter_MouseButtonUp_Back(const EventArgs &e) {
	FCreateCharacter_Visible(false);
	FMain_Visible(false);
	FConnect_Visible(true);
	return false;
}

bool OGEForms::FCreateCharacter_MouseButtonUp_ThrowDices(const EventArgs &e) {
	if (GetGame()->GetConnected())
		return false;
	
	GetGame()->GetProtocol()->WriteThrowDices();
	return false;
}

bool OGEForms::FCreateCharacter_MouseButtonUp_CreateCharacter(const EventArgs &e) {
	if (GetGame()->GetConnected())
		return false;

	Window* FCreateCharacter = GetWinRoot()->getChild("AllForm")->getChild("CrearPJArea");

	Combobox* RazaCombo = static_cast<Combobox*>(FCreateCharacter->getChild("RazaCombo"));
	Combobox* GeneroCombo = static_cast<Combobox*>(FCreateCharacter->getChild("GeneroCombo"));
	Combobox* ClaseCombo = static_cast<Combobox*>(FCreateCharacter->getChild("ClaseCombo"));
	Combobox* HogarCombo = static_cast<Combobox*>(FCreateCharacter->getChild("HogarCombo"));

	String username = FCreateCharacter->getChild("NameText")->getText();
	String userpassworda = FCreateCharacter->getChild("PasswordTextA")->getText();
	String userpasswordb = FCreateCharacter->getChild("PasswordTextB")->getText();
	String useremaila = FCreateCharacter->getChild("EMailTextA")->getText();
	String useremailb = FCreateCharacter->getChild("EMailTextB")->getText();

	short countA = 0;
	const char* charname = useremaila.c_str();

	for (int i = 0; i < (int)useremaila.length(); ++i){
		if (charname[i] == '@'){
			countA++;
		}
	}

	if ((countA != 1) | (useremaila.length() < 6)){
		MessageBoxA(NULL, "Ha ingresado una dirección de E-Mail inválida, porfavor verifique que su dirección sea la correcta.", "Creando personaje: ", NULL);
		return false;
	}

	if (useremaila != useremailb){
		MessageBoxA(NULL, "Las direcciones de E-Mail no coinciden, porfavor verifique que ambas sean correctas.", "Creando personaje: ", NULL);
		return false;
	}

	if (userpassworda.length() < 8){
		MessageBoxA(NULL, "Debe ingresar una contraseña alfanumérica mayor a 8 caracteres.", "Creando personaje: ", NULL);
		return false;
	}

	if (userpassworda != userpasswordb){
		MessageBoxA(NULL, "Las contraseñas no coinciden, porfavor verifique que ambas sean correctas.", "Creando personaje: ", NULL);
		return false;
	}

	if (!RazaCombo->getSelectedItem()){
		MessageBoxA(NULL, "Debes seleccionar la Raza de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!GeneroCombo->getSelectedItem()){
		MessageBoxA(NULL, "Debes seleccionar el Genero de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!ClaseCombo->getSelectedItem()){
		MessageBoxA(NULL, "Debes seleccionar la Clase de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!HogarCombo->getSelectedItem()){
		MessageBoxA(NULL, "Debes seleccionar una Ciudad de Origen para el Hogar de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	char userraza = 1;
	char usergenero = 1;
	char userclase = 1;
	char userhogar = 1;
	short userhead = 8;

	for (int i = 0; i < (int)RazaCombo->getItemCount(); ++i) {
		if (RazaCombo->getListboxItemFromIndex(i)->isSelected()) userraza = i + 1;
	}

	for (int i = 0; i < (int)GeneroCombo->getItemCount(); ++i) {
		if (GeneroCombo->getListboxItemFromIndex(i)->isSelected()) usergenero = i + 1;
	}

	for (int i = 0; i < (int)ClaseCombo->getItemCount(); ++i) {
		if (ClaseCombo->getListboxItemFromIndex(i)->isSelected()) userclase = i + 1;
	}

	for (int i = 0; i < (int)HogarCombo->getItemCount(); ++i) {
		if (HogarCombo->getListboxItemFromIndex(i)->isSelected()) userhogar = i + 1;
	}

	GetGame()->GetProtocol()->WriteLoginNewChar(username.c_str(), userpassworda.c_str(), userraza, usergenero, userclase, userhead, useremaila.c_str(), userhogar);
	return false;
}

void OGEForms::FMain_Load(){
	Window* FMainArea = GetWinRoot()->getChild("AllForm")->getChild("MainArea");

	FMainArea->setVisible(true);
	FMainArea->getChild("Console")->setVisible(true);
	FMainArea->getChild("CantidadText")->setVisible(false);
	FMainArea->getChild("ClanesWindow")->setVisible(false);
	FMainArea->getChild("ComercioUsuarioWindow")->setVisible(false);
	FMainArea->getChild("ExpBar")->setVisible(true);
	FMainArea->getChild("InfoButton")->setVisible(false);
	FMainArea->getChild("LanzarButton")->setVisible(false);
	FMainArea->getChild("MenuWindow")->setVisible(false);
	FMainArea->getChild("MiClanWindow")->setVisible(false);
	FMainArea->getChild("MinimapaRect")->setVisible(false);
	FMainArea->getChild("MoveSpellDownButton")->setVisible(false);
	FMainArea->getChild("MoveSpellUpButton")->setVisible(false);
	FMainArea->getChild("NpcBancoWindow")->setVisible(false);
	FMainArea->getChild("NpcComercioWindow")->setVisible(false);
	FMainArea->getChild("OpcionesWindow")->setVisible(false);
	FMainArea->getChild("PosRect")->setVisible(false);
	FMainArea->getChild("SpellButton")->setVisible(false);
	FMainArea->getChild("SpellList")->setVisible(false);
	FMainArea->getChild("TeclasWindow")->setVisible(false);

	FMainArea->getChild("MenuWindow")->subscribeEvent(FrameWindow::EventCloseClicked, Event::Subscriber(&OGEForms::FMain_onCloseClicked, this));
	FMainArea->getChild("MenuWindow/DesloginButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_Deslogin_MouseButtonUp, this));
	FMainArea->getChild("MenuWindow/ExitButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_Exit_MouseButtonUp, this));
	FMainArea->getChild("MenuWindow/ClanesButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_ClanesButton, this));
	FMainArea->getChild("ClanesWindow")->subscribeEvent(FrameWindow::EventCloseClicked, Event::Subscriber(&OGEForms::FMain_onCloseClicked_ClanesWindow, this));
	FMainArea->getChild("ClanesWindow/ClanesList")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_ClanesList, this));
	FMainArea->getChild("ClanesWindow/SolicitarButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_SolicitarButton, this));
	FMainArea->getChild("ClanesWindow/SolicitudWindow/EnviarButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_SolicitudWindow_EnviarButton, this));
	FMainArea->getChild("MiClanWindow")->subscribeEvent(FrameWindow::EventCloseClicked, Event::Subscriber(&OGEForms::FMain_onCloseClicked_MiClanWindow, this));
	FMainArea->getChild("MiClanWindow/MiembrosButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_MyClanes_MembersButton, this));
	FMainArea->getChild("MiClanWindow/AspirantesButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_MyClanes_AspirantesButton, this));
	FMainArea->getChild("MiClanWindow/ClanesButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_MyClanes_ClanesButton, this));
	FMainArea->getChild("MiClanWindow/AspirantesWindow/AceptarButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_Aspirantes_AcceptButton, this));
	FMainArea->getChild("MiClanWindow/AspirantesWindow/RechazarButton")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_Aspirantes_RejectButton, this));
	FMainArea->getChild("Console/Submit")->subscribeEvent(FrameWindow::EventMouseButtonUp, Event::Subscriber(&OGEForms::FMain_SendText_MouseUp, this));
}

void OGEForms::FMain_UnLoad(){
	Window* FMain = GetWinRoot()->getChild("AllForm")->getChild("MainArea")->getChild("MenuWindow");
}

void OGEForms::FMain_Menu_Visible(bool m_Visible){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MenuWindow");

	FMain->setVisible(m_Visible);
}

void OGEForms::FMain_GuildList_Visible(bool m_Visible){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow");
	FMain->setVisible(m_Visible);
}

void OGEForms::FMain_GuildLeader_Visible(bool m_Visible, bool m_isLeader){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow");
	FMain->setVisible(m_Visible);
	FMain->getChild("ClanesWindow")->setVisible(m_Visible);
	FMain->getChild("AspirantesButton")->setEnabled(m_isLeader);
	FMain->getChild("MiembrosWindow/EcharButton")->setEnabled(m_isLeader);
	FMain->getChild("OtrosButton")->setEnabled(false);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(true);
}

void OGEForms::FMain_GuildNews_setText(std::string newstext){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/DeskText");
	FMain->setText(newstext);
	FMain->setVisible(true);
}

bool OGEForms::FMain_MyClanes_MembersButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow");
	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(true);
	FMain_Reload_GuildMember();
	return false;
}

bool OGEForms::FMain_MyClanes_AspirantesButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow");
	FMain->getChild("AspirantesWindow")->setVisible(true);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(false);
	FMain_Reload_GuildAspirantes();
	return false;
}

bool OGEForms::FMain_MyClanes_ClanesButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow");
	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("ClanesWindow")->setVisible(true);
	FMain->getChild("MiembrosWindow")->setVisible(false);
	FMain_Reload_GuildList();
	return false;
}

void OGEForms::FMain_Reload_GuildList(){
	/*if (m_Game->GetDeclares()->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList")->isVisible())
	{
		CEGUI::Listbox* GuildList = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList"));
		GuildList->resetList();

		for (int i = 0; i < GameData->GuildNames.size(); ++i)
		{
			GuildList->addItem(new CEGUI::ListboxTextItem(GameData->GuildNames[i]));
		}

		winRoot->getChild("AllForm/MainArea/ClanesWindow/MiclanButton")->setEnabled(false);
	}

	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/ClanesWindow/ClanesList")->isVisible())
	{
		CEGUI::Listbox* GuildListLeader = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/ClanesWindow/ClanesList"));
		GuildListLeader->resetList();

		for (int i = 0; i < GameData->GuildNames.size(); ++i)
		{
			GuildListLeader->addItem(new CEGUI::ListboxTextItem(GameData->GuildNames[i]));
		}
	}*/
}

void OGEForms::FMain_Reload_GuildAspirantes(){
	/*cGameData* GameData = cGameData::p_cGIn();
	if (GameData->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList")->isVisible())
	{
		CEGUI::Listbox* GuildAspirantes = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList"));
		GuildAspirantes->resetList();

		for (int i = 0; i < GameData->GuildAspirantes.size(); ++i)
		{
			GuildAspirantes->addItem(new CEGUI::ListboxTextItem(GameData->GuildAspirantes[i]));
		}
	}
	*/
}

void OGEForms::FMain_Reload_GuildMember(){
	/*cGameData* GameData = cGameData::p_cGIn();
	if (GameData->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/MiembrosWindow/MiembrosList")->isVisible())
	{
		CEGUI::Listbox* GuildMembers = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/MiembrosWindow/MiembrosList"));
		GuildMembers->resetList();

		for (int i = 0; i < GameData->GuildMembers.size(); ++i)
		{
			GuildMembers->addItem(new CEGUI::ListboxTextItem(GameData->GuildMembers[i]));
		}
	}*/

}

void OGEForms::FMain_AddItem_Console(std::string text, int color, bool bold, bool italic){
	Window* Console = GetWinRoot()->getChild("AllForm/MainArea/Console");
	Listbox *outputWindow = static_cast<Listbox*>(Console->getChild("History"));
	ListboxTextItem* newItem = new ListboxTextItem(text);

	newItem->setTextColours(color);

	if (outputWindow->getItemCount() >= 200) outputWindow->resetList();

	Scrollbar* scrollVert = static_cast<Scrollbar*>(outputWindow->getVertScrollbar());
	outputWindow->addItem(newItem);
	scrollVert->setUnitIntervalScrollPosition(1.0f);
}

void OGEForms::FMain_SendText(){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/Console/Editbox");

	if (FMain->isActive()){
		m_Game->GetProtocol()->ParseUserCommand(FMain->getText().c_str());
		FMain->setText("");
		FMain->setEnabled(false);
		FMain->deactivate();
		GetWinRoot()->getChild("AllForm/MainArea/Console/Submit")->setEnabled(false);
	}
	else{
		FMain->setText("");
		FMain->setEnabled(true);
		FMain->activate();
		GetWinRoot()->getChild("AllForm/MainArea/Console/Submit")->setEnabled(true);
	}
}

void OGEForms::FMain_Visible(bool m_Visible){
	GetWinRoot()->getChild("AllForm/MainArea")->setVisible(m_Visible);
	GetWinRoot()->getChild("AllForm/MainArea/ExpBar")->setVisible(m_Visible);
}

void OGEForms::FMain_SetExpBar(float m_Value){
	Window* childExpBar = GetWinRoot()->getChild("AllForm")->getChild("MainArea")->getChild("ExpBar");
	ProgressBar* ExpBar = static_cast<ProgressBar*>(childExpBar);
	ExpBar->setProgress(m_Value);
	GetWinRoot()->getChild("AllForm/MainArea/ExpBar")->setText(NumberToString(m_Value) + "%");
}

bool OGEForms::FMain_onCloseClicked(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	return false;
}

bool OGEForms::FMain_onCloseClicked_ClanesWindow(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow")->setVisible(false);
	return false;
}

bool OGEForms::FMain_onCloseClicked_MiClanWindow(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow")->setVisible(false);
	return false;
}

bool OGEForms::FMain_Aspirantes_AcceptButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList");
	Listbox* ClanesList = static_cast<Listbox*>(FMain);

	int countList = 0;

	for (size_t i = 0; i < ClanesList->getItemCount(); ++i){
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = (int)i;
	}

	//WriteGuildAcceptNewMember(cGameData::p_cGIn()->GuildAspirantes[countList]);
	return false;
}

bool OGEForms::FMain_Aspirantes_RejectButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList");
	Listbox* ClanesList = static_cast<Listbox*>(FMain);

	int countList = 0;
	for (size_t i = 0; i < ClanesList->getItemCount(); ++i){
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = (int)i + 1;
	}

	//std::cout << "aspi: " << cGameData::p_cGIn()->GuildAspirantes[countList - 1] << std::endl;
	//WriteGuildRejectNewMember(cGameData::p_cGIn()->GuildAspirantes[countList - 1], "Sos pt");
	return false;
}

bool OGEForms::FMain_Deslogin_MouseButtonUp(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	m_Game->GetAudio()->PlayWAV("click.wav");
	m_Game->GetProtocol()->WriteQuit();
	return false;
}

bool OGEForms::FMain_SolicitudWindow_EnviarButton(const EventArgs &e){

	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow");
	FMain->getChild("SolicitudWindow")->setVisible(false);
	//WriteGuildRequestMembership(FMain->getChild("NombreText")->getText().c_str(), FMain->getChild("SolicitudWindow/SolicitudText")->getText().c_str());
	return false;
}

bool OGEForms::FMain_SolicitarButton(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/SolicitudWindow")->setVisible(true);
	GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/SolicitudWindow/SolicitudText")->setText("Qué tal, me interesaría unirme a tu Clan.");
	return false;
}

bool OGEForms::FMain_Exit_MouseButtonUp(const EventArgs &e){
	GetWinRoot()->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	m_Game->GetEngine()->setRun(false);
	//m_Game->GetEngine()->setRun(false);
	return false;
}

bool OGEForms::FMain_ClanesButton(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/ClanesList");

	//WriteRequestGuildLeaderInfo();
	FMain_Menu_Visible(false);
	return false;
}

bool OGEForms::FMain_ClanesList(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/ClanesList");
	Window* NameText = GetWinRoot()->getChild("AllForm/MainArea/ClanesWindow/NombreText");

	Listbox* ClanesList = static_cast<Listbox*>(FMain);

	int countList = 0;
	for (size_t i = 0; i < ClanesList->getItemCount(); ++i){
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = (int)i + 1;
	}

	//if (countList > 0) NameText->setText(cGameData::p_cGIn()->GuildNames[countList - 1]);

	return false;
}

bool OGEForms::FMain_SendText_MouseUp(const EventArgs &e){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/Console/Editbox");

	//ParseUserCommand(FMain->getText().c_str());
	FMain->setText("");
	FMain->setEnabled(false);
	FMain->deactivate();
	GetWinRoot()->getChild("AllForm/MainArea/Console/Submit")->setEnabled(false);
	return false;
}

bool OGEForms::FMain_GetActive_SendText(){
	Window* FMain = GetWinRoot()->getChild("AllForm/MainArea/Console/Editbox");
	return FMain->isActive();
}

void OGEForms::FErrorWindow_Load(){
	GetWinRoot()->getChild("AllForm")->getChild("ErrorWindow")->setVisible(true);
}

void OGEForms::FErrorWindow_UnLoad(){
	GetWinRoot()->getChild("AllForm")->getChild("ErrorWindow")->setVisible(false);
}