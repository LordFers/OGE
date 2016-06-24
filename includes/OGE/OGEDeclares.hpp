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
#pragma once
class OGEDeclares {
	public:
		OGEDeclares::OGEDeclares() { 
			this->m_GettedSkills = false;
		}

	public:
		inline int OGEDeclares::GetNumSkills() { return this->m_NUMSKILLS; }
		inline int OGEDeclares::GetMaxInventorySlots() { return this->m_MAXINVENTORYSLOTS; }
		inline int OGEDeclares::GetNumAtributos() { return this->m_NUMATRIBUTOS; }
		inline int OGEDeclares::GetNumClasses() { return this->m_NUMCLASES; }
		inline int OGEDeclares::GetNumRazas() { return this->m_NUMRAZAS; }
		inline int OGEDeclares::GetMaxSkillsPoints() { return this->m_MAXSKILLPOINTS; }
		inline int OGEDeclares::GetNumCiudades() { return this->m_NUMCIUDADES; }

	public:
		inline short OGEDeclares::GetNumGrhs() { return this->m_NumGrhs; }
		inline short OGEDeclares::GetNumBodys() { return this->m_NumBodys; }
		inline short OGEDeclares::GetNumHeads() { return this->m_NumHeads; }
		inline short OGEDeclares::GetNumHelmets() { return this->m_NumHelmets; }
		inline short OGEDeclares::GetNumWeapons() { return this->m_NumWeapons; }
		inline short OGEDeclares::GetNumShields() { return this->m_NumShields; }
		inline short OGEDeclares::GetNumFXs() { return this->m_NumFXs; }

	public:
		inline bool OGEDeclares::GettedSkills() { return this->m_GettedSkills; }

	public:
		inline void OGEDeclares::SetNumGrhs(short m_NumGrhs) { this->m_NumGrhs = m_NumGrhs; }
		inline void OGEDeclares::SetNumBodys(short m_NumBodys) { this->m_NumBodys = m_NumBodys; }
		inline void OGEDeclares::SetNumHeads(short m_NumHeads) { this->m_NumHeads = m_NumHeads; }
		inline void OGEDeclares::SetNumHelmets(short m_NumHelmets) { this->m_NumHelmets = m_NumHelmets; }
		inline void OGEDeclares::SetNumWeapons(short m_NumWeapons) { this->m_NumWeapons = m_NumWeapons; }
		inline void OGEDeclares::SetNumShields(short m_NumShields) { this->m_NumShields = m_NumShields; }
		inline void OGEDeclares::SetNumFXs(short m_NumFXs) { this->m_NumFXs = m_NumFXs; }

	public:
		inline void OGEDeclares::SetGettedSkills(bool m_Getted) { this->m_GettedSkills = m_Getted; }

	private:
		short m_NumGrhs;
		short m_NumBodys;
		short m_NumHeads;
		short m_NumHelmets;
		short m_NumWeapons;
		short m_NumShields;
		short m_NumFXs;

	private:
		bool m_GettedSkills;

	private: //Constantes:
		const int m_NUMSKILLS = 20;
		const int m_MAXINVENTORYSLOTS = 25;
		const int m_NUMATRIBUTOS = 5;
		const int m_NUMCLASES = 12;
		const int m_NUMRAZAS = 5;
		const int m_MAXSKILLPOINTS = 100;
		const int m_NUMCIUDADES = 6;
};