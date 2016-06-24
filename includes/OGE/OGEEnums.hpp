#ifndef MYENUMS_H
#define MYENUMS_H

enum eClass {
	eClass_None = 0,
	/* 'Mago */
	eClass_Mage = 1,
	/* 'Clérigo */
	eClass_Cleric,
	/* 'Guerrero */
	eClass_Warrior,
	/* 'Asesino */
	eClass_Assasin,
	/* 'Ladrón */
	eClass_Thief,
	/* 'Bardo */
	eClass_Bard,
	/* 'Druida */
	eClass_Druid,
	/* 'Bandido */
	eClass_Bandit,
	/* 'Paladín */
	eClass_Paladin,
	/* 'Cazador */
	eClass_Hunter,
	/* 'Trabajador */
	eClass_Worker,
	/* 'Pirata */
	eClass_Pirat
};

enum eCiudad {
	eCiudad_None = 0,
	eCiudad_cUllathorpe = 1,
	eCiudad_cNix,
	eCiudad_cBanderbill,
	eCiudad_cLindos,
	eCiudad_cArghal,
	eCiudad_cArkhein,
	eCiudad_cLastCity
};

enum eRaza {
	eRaza_None = 0, eRaza_Humano = 1, eRaza_Elfo, eRaza_Drow, eRaza_Gnomo, eRaza_Enano
};

enum eGenero {
	eGenero_None =0, eGenero_Hombre = 1, eGenero_Mujer
};

enum eClanType {
	eClanType_ct_RoyalArmy,
	eClanType_ct_Evil,
	eClanType_ct_Neutral,
	eClanType_ct_GM,
	eClanType_ct_Legal,
	eClanType_ct_Criminal
};

enum FxMeditar {
	CHICO = 4,
	MEDIANO = 5,
	GRANDE = 6,
	XGRANDE = 16,
	XXGRANDE = 34
};

enum eTrigger {
	eTrigger_NADA = 0,
	eTrigger_BAJOTECHO = 1,
	eTrigger_trigger_2 = 2,
	eTrigger_POSINVALIDA = 3,
	eTrigger_ZONASEGURA = 4,
	eTrigger_ANTIPIQUETE = 5,
	eTrigger_ZONAPELEA = 6
};

enum eHeading {
	eHeading_None = 0,
	eHeading_NORTH = 1,
	eHeading_EAST = 2,
	eHeading_SOUTH = 3,
	eHeading_WEST = 4
};

enum eSkill {
	eSkill_Magia = 1,
	eSkill_Robar = 2,
	eSkill_Tacticas = 3,
	eSkill_Armas = 4,
	eSkill_Meditar = 5,
	eSkill_Apunalar = 6,
	eSkill_Ocultarse = 7,
	eSkill_Supervivencia = 8,
	eSkill_Talar = 9,
	eSkill_Comerciar = 10,
	eSkill_Defensa = 11,
	eSkill_Pesca = 12,
	eSkill_Mineria = 13,
	eSkill_Carpinteria = 14,
	eSkill_Herreria = 15,
	eSkill_Liderazgo = 16,
	eSkill_Domar = 17,
	eSkill_Proyectiles = 18,
	eSkill_Wrestling = 19,
	eSkill_Navegacion = 20,
};

enum eAtributos {
	eAtributos_Fuerza = 1,
	eAtributos_Agilidad = 2,
	eAtributos_Inteligencia = 3,
	eAtributos_Carisma = 4,
	eAtributos_Constitucion = 5
};

enum eOBJType {
	eOBJType_Null = 0,
	eOBJType_otUseOnce = 1,
	eOBJType_otWeapon = 2,
	eOBJType_otArmadura = 3,
	eOBJType_otArboles = 4,
	eOBJType_otGuita = 5,
	eOBJType_otPuertas = 6,
	eOBJType_otContenedores = 7,
	eOBJType_otCarteles = 8,
	eOBJType_otLlaves = 9,
	eOBJType_otForos = 10,
	eOBJType_otPociones = 11,
	eOBJType_otBebidas = 13,
	eOBJType_otLena = 14,
	eOBJType_otFogata = 15,
	eOBJType_otESCUDO = 16,
	eOBJType_otCASCO = 17,
	eOBJType_otAnillo = 18,
	eOBJType_otTeleport = 19,
	eOBJType_otYacimiento = 22,
	eOBJType_otMinerales = 23,
	eOBJType_otPergaminos = 24,
	eOBJType_otInstrumentos = 26,
	eOBJType_otYunque = 27,
	eOBJType_otFragua = 28,
	eOBJType_otBarcos = 31,
	eOBJType_otFlechas = 32,
	eOBJType_otBotellaVacia = 33,
	eOBJType_otBotellaLlena = 34,
	/* 'No se usa */
	eOBJType_otManchas = 35,
	eOBJType_otArbolElfico = 36,
	eOBJType_otMochilas = 37,
	eOBJType_otYacimientoPez = 38,
	eOBJType_otCualquiera = 1000
};

enum eNickColor {
	eNickColor_ieCriminal = 0x1, eNickColor_ieCiudadano = 0x2, eNickColor_ieAtacable = 0x4
};

enum eForumMsgType {
	eForumMsgType_ieGeneral,
	eForumMsgType_ieGENERAL_STICKY,
	eForumMsgType_ieREAL,
	eForumMsgType_ieREAL_STICKY,
	eForumMsgType_ieCAOS,
	eForumMsgType_ieCAOS_STICKY
};

enum eForumVisibility {
	eForumVisibility_ieGENERAL_MEMBER = 0x1,
	eForumVisibility_ieREAL_MEMBER = 0x2,
	eForumVisibility_ieCAOS_MEMBER = 0x4
};

enum eForumType {
	eForumType_ieGeneral, eForumType_ieREAL, eForumType_ieCAOS
};

enum eMessages {
	eMessages_DontSeeAnything,
	eMessages_NPCSwing,
	eMessages_NPCKillUser,
	eMessages_BlockedWithShieldUser,
	eMessages_BlockedWithShieldother,
	eMessages_UserSwing,
	eMessages_SafeModeOn,
	eMessages_SafeModeOff,
	eMessages_ResuscitationSafeOff,
	eMessages_ResuscitationSafeOn,
	eMessages_NobilityLost,
	eMessages_CantUseWhileMeditating,
	eMessages_NPCHitUser,
	eMessages_UserHitNPC,
	eMessages_UserAttackedSwing,
	eMessages_UserHittedByUser,
	eMessages_UserHittedUser,
	eMessages_WorkRequestTarget,
	eMessages_HaveKilledUser,
	eMessages_UserKill,
	eMessages_EarnExp,
	eMessages_Home,
	eMessages_CancelHome,
    eMessages_FinishHome
};

enum eGMCommands {
	/* '/GMSG */
	eGMCommands_GMMessage = 1,
	/* '/SHOWNAME */
	eGMCommands_showName,
	/* '/ONLINEREAL */
	eGMCommands_OnlineRoyalArmy,
	/* '/ONLINECAOS */
	eGMCommands_OnlineChaosLegion,
	/* '/IRCERCA */
	eGMCommands_GoNearby,
	/* '/REM */
	eGMCommands_comment,
	/* '/HORA */
	eGMCommands_serverTime,
	/* '/DONDE */
	eGMCommands_Where,
	/* '/NENE */
	eGMCommands_CreaturesInMap,
	/* '/TELEPLOC */
	eGMCommands_WarpMeToTarget,
	/* '/TELEP */
	eGMCommands_WarpChar,
	/* '/SILENCIAR */
	eGMCommands_Silence,
	/* '/SHOW SOS */
	eGMCommands_SOSShowList,
	/* 'SOSDONE */
	eGMCommands_SOSRemove,
	/* '/IRA */
	eGMCommands_GoToChar,
	/* '/INVISIBLE */
	eGMCommands_invisible,
	/* '/PANELGM */
	eGMCommands_GMPanel,
	/* 'LISTUSU */
	eGMCommands_RequestUserList,
	/* '/TRABAJANDO */
	eGMCommands_Working,
	/* '/OCULTANDO */
	eGMCommands_Hiding,
	/* '/CARCEL */
	eGMCommands_Jail,
	/* '/RMATA */
	eGMCommands_KillNPC,
	/* '/ADVERTENCIA */
	eGMCommands_WarnUser,
	/* '/MOD */
	eGMCommands_EditChar,
	/* '/INFO */
	eGMCommands_RequestCharInfo,
	/* '/STAT */
	eGMCommands_RequestCharStats,
	/* '/BAL */
	eGMCommands_RequestCharGold,
	/* '/INV */
	eGMCommands_RequestCharInventory,
	/* '/BOV */
	eGMCommands_RequestCharBank,
	/* '/SKILLS */
	eGMCommands_RequestCharSkills,
	/* '/REVIVIR */
	eGMCommands_ReviveChar,
	/* '/ONLINEGM */
	eGMCommands_OnlineGM,
	/* '/ONLINEMAP */
	eGMCommands_OnlineMap,
	/* '/PERDON */
	eGMCommands_Forgive,
	/* '/ECHAR */
	eGMCommands_Kick,
	/* '/EJECUTAR */
	eGMCommands_Execute,
	/* '/BAN */
	eGMCommands_BanChar,
	/* '/UNBAN */
	eGMCommands_UnbanChar,
	/* '/SEGUIR */
	eGMCommands_NPCFollow,
	/* '/SUM */
	eGMCommands_SummonChar,
	/* '/CC */
	eGMCommands_SpawnListRequest,
	/* 'SPA */
	eGMCommands_SpawnCreature,
	/* '/RESETINV */
	eGMCommands_ResetNPCInventory,
	/* '/LIMPIAR */
	eGMCommands_CleanWorld,
	/* '/RMSG */
	eGMCommands_ServerMessage,
	/* '/NICK2IP */
	eGMCommands_NickToIP,
	/* '/IP2NICK */
	eGMCommands_IPToNick,
	/* '/ONCLAN */
	eGMCommands_GuildOnlineMembers,
	/* '/CT */
	eGMCommands_TeleportCreate,
	/* '/DT */
	eGMCommands_TeleportDestroy,
	/* '/LLUVIA */
	eGMCommands_RainToggle,
	/* '/SETDESC */
	eGMCommands_SetCharDescription,
	/* '/FORCEMIDIMAP */
	eGMCommands_ForceMIDIToMap,
	/* '/FORCEWAVMAP */
	eGMCommands_ForceWAVEToMap,
	/* '/REALMSG */
	eGMCommands_RoyalArmyMessage,
	/* '/CAOSMSG */
	eGMCommands_ChaosLegionMessage,
	/* '/CIUMSG */
	eGMCommands_CitizenMessage,
	/* '/CRIMSG */
	eGMCommands_CriminalMessage,
	/* '/TALKAS */
	eGMCommands_TalkAsNPC,
	/* '/MASSDEST */
	eGMCommands_DestroyAllItemsInArea,
	/* '/ACEPTCONSE */
	eGMCommands_AcceptRoyalCouncilMember,
	/* '/ACEPTCONSECAOS */
	eGMCommands_AcceptChaosCouncilMember,
	/* '/PISO */
	eGMCommands_ItemsInTheFloor,
	/* '/ESTUPIDO */
	eGMCommands_MakeDumb,
	/* '/NOESTUPIDO */
	eGMCommands_MakeDumbNoMore,
	/* '/DUMPSECURITY */
	eGMCommands_DumpIPTables,
	/* '/KICKCONSE */
	eGMCommands_CouncilKick,
	/* '/TRIGGER */
	eGMCommands_SetTrigger,
	/* '/TRIGGER with no args */
	eGMCommands_AskTrigger,
	/* '/BANIPLIST */
	eGMCommands_BannedIPList,
	/* '/BANIPRELOAD */
	eGMCommands_BannedIPReload,
	/* '/MIEMBROSCLAN */
	eGMCommands_GuildMemberList,
	/* '/BANCLAN */
	eGMCommands_GuildBan,
	/* '/BANIP */
	eGMCommands_BanIP,
	/* '/UNBANIP */
	eGMCommands_UnbanIP,
	/* '/CI */
	eGMCommands_CreateItem,
	/* '/DEST */
	eGMCommands_DestroyItems,
	/* '/NOCAOS */
	eGMCommands_ChaosLegionKick,
	/* '/NOREAL */
	eGMCommands_RoyalArmyKick,
	/* '/FORCEMIDI */
	eGMCommands_ForceMIDIAll,
	/* '/FORCEWAV */
	eGMCommands_ForceWAVEAll,
	/* '/BORRARPENA */
	eGMCommands_RemovePunishment,
	/* '/BLOQ */
	eGMCommands_TileBlockedToggle,
	/* '/MATA */
	eGMCommands_KillNPCNoRespawn,
	/* '/MASSKILL */
	eGMCommands_KillAllNearbyNPCs,
	/* '/LASTIP */
	eGMCommands_LastIP,
	/* '/MOTDCAMBIA */
	eGMCommands_ChangeMOTD,
	/* 'ZMOTD */
	eGMCommands_SetMOTD,
	/* '/SMSG */
	eGMCommands_SystemMessage,
	/* '/ACC */
	eGMCommands_CreateNPC,
	/* '/RACC */
	eGMCommands_CreateNPCWithRespawn,
	/* '/AI1 - 4 */
	eGMCommands_ImperialArmour,
	/* '/AC1 - 4 */
	eGMCommands_ChaosArmour,
	/* '/NAVE */
	eGMCommands_NavigateToggle,
	/* '/HABILITAR */
	eGMCommands_ServerOpenToUsersToggle,
	/* '/APAGAR */
	eGMCommands_TurnOffServer,
	/* '/CONDEN */
	eGMCommands_TurnCriminal,
	/* '/RAJAR */
	eGMCommands_ResetFactions,
	/* '/RAJARCLAN */
	eGMCommands_RemoveCharFromGuild,
	/* '/LASTEMAIL */
	eGMCommands_RequestCharMail,
	/* '/APASS */
	eGMCommands_AlterPassword,
	/* '/AEMAIL */
	eGMCommands_AlterMail,
	/* '/ANAME */
	eGMCommands_AlterName,
	/* '/CENTINELAACTIVADO */
	eGMCommands_ToggleCentinelActivated,
	/* '/DOBACKUP */
	eGMCommands_DoBackUp,
	/* '/SHOWCMSG */
	eGMCommands_ShowGuildMessages,
	/* '/GUARDAMAPA */
	eGMCommands_SaveMap,
	/* '/MODMAPINFO PK */
	eGMCommands_ChangeMapInfoPK,
	/* '/MODMAPINFO BACKUP */
	eGMCommands_ChangeMapInfoBackup,
	/* '/MODMAPINFO RESTRINGIR */
	eGMCommands_ChangeMapInfoRestricted,
	/* '/MODMAPINFO MAGIASINEFECTO */
	eGMCommands_ChangeMapInfoNoMagic,
	/* '/MODMAPINFO INVISINEFECTO */
	eGMCommands_ChangeMapInfoNoInvi,
	/* '/MODMAPINFO RESUSINEFECTO */
	eGMCommands_ChangeMapInfoNoResu,
	/* '/MODMAPINFO TERRENO */
	eGMCommands_ChangeMapInfoLand,
	/* '/MODMAPINFO ZONA */
	eGMCommands_ChangeMapInfoZone,
	/* '/MODMAPINFO ROBONPC */
	eGMCommands_ChangeMapInfoStealNpc,
	/* '/MODMAPINFO OCULTARSINEFECTO */
	eGMCommands_ChangeMapInfoNoOcultar,
	/* '/MODMAPINFO INVOCARSINEFECTO */
	eGMCommands_ChangeMapInfoNoInvocar,
	/* '/GRABAR */
	eGMCommands_SaveChars,
	/* '/BORRAR SOS */
	eGMCommands_CleanSOS,
	/* '/SHOW INT */
	eGMCommands_ShowServerForm,
	/* '/NOCHE */
	eGMCommands_night,
	/* '/ECHARTODOSPJS */
	eGMCommands_KickAllChars,
	/* '/RELOADNPCS */
	eGMCommands_ReloadNPCs,
	/* '/RELOADSINI */
	eGMCommands_ReloadServerIni,
	/* '/RELOADHECHIZOS */
	eGMCommands_ReloadSpells,
	/* '/RELOADOBJ */
	eGMCommands_ReloadObjects,
	/* '/REINICIAR */
	eGMCommands_Restart,
	/* '/AUTOUPDATE */
	eGMCommands_ResetAutoUpdate,
	/* '/CHATCOLOR */
	eGMCommands_ChatColor,
	/* '/IGNORADO */
	eGMCommands_Ignored,
	/* '/SLOT */
	eGMCommands_CheckSlot,
	/* '/SETINIVAR LLAVE CLAVE VALOR */
	eGMCommands_SetIniVar,
	/* '/CREARPRETORIANOS */
	eGMCommands_CreatePretorianClan,
	/* '/ELIMINARPRETORIANOS */
	eGMCommands_RemovePretorianClan,
	/* '/DENUNCIAS */
	eGMCommands_EnableDenounces,
	/* '/SHOW DENUNCIAS */
	eGMCommands_ShowDenouncesList,
	/* '/MAPMSG */
	eGMCommands_MapMessage,
	/* '/SETDIALOG */
	eGMCommands_SetDialog,
	/* '/IMPERSONAR */
	eGMCommands_Impersonate,
	/* '/MIMETIZAR */
	eGMCommands_Imitate,
	eGMCommands_RecordAdd,
	eGMCommands_RecordRemove,
	eGMCommands_RecordAddObs,
	eGMCommands_RecordListRequest,
	eGMCommands_RecordDetailsRequest,
	eGMCommands_AlterGuildName,
	eGMCommands_HigherAdminsMessage
};
enum e_SecurityIpTabla {
	e_SecurityIpTabla_IP_INTERVALOS = 1, e_SecurityIpTabla_IP_LIMITECONEXIONES = 2
};
enum TipoAI {
	TipoAI_None = 0,
	TipoAI_ESTATICO = 1,
	TipoAI_MueveAlAzar = 2,
	TipoAI_NpcMaloAtacaUsersBuenos = 3,
	TipoAI_NPCDEFENSA = 4,
	TipoAI_GuardiasAtacanCriminales = 5,
	TipoAI_NpcObjeto = 6,
	TipoAI_SigueAmo = 8,
	TipoAI_NpcAtacaNpc = 9,
	TipoAI_NpcPathfinding = 10,
	/* 'Pretorianos */
	TipoAI_SacerdotePretorianoAi = 20,
	TipoAI_GuerreroPretorianoAi = 21,
	TipoAI_MagoPretorianoAi = 22,
	TipoAI_CazadorPretorianoAi = 23,
	TipoAI_ReyPretoriano = 24
};
enum EstaNotificaciones {
	EstaNotificaciones_CANTIDAD_ONLINE = 1,
	EstaNotificaciones_RECORD_USUARIOS = 2,
	EstaNotificaciones_UPTIME_SERVER = 3,
	EstaNotificaciones_CANTIDAD_MAPAS = 4,
	EstaNotificaciones_EVENTO_NUEVO_CLAN = 5,
	EstaNotificaciones_HANDLE_WND_SERVER = 100
};
enum ALINEACION_GUILD {
	ALINEACION_GUILD_Null = 0,
	ALINEACION_GUILD_ALINEACION_LEGION = 1,
	ALINEACION_GUILD_ALINEACION_CRIMINAL = 2,
	ALINEACION_GUILD_ALINEACION_NEUTRO = 3,
	ALINEACION_GUILD_ALINEACION_CIUDA = 4,
	ALINEACION_GUILD_ALINEACION_ARMADA = 5,
	ALINEACION_GUILD_ALINEACION_MASTER = 6
};
enum SONIDOS_GUILD {
	SONIDOS_GUILD_SND_CREACIONCLAN = 44,
	SONIDOS_GUILD_SND_ACEPTADOCLAN = 43,
	SONIDOS_GUILD_SND_DECLAREWAR = 45
};
enum RELACIONES_GUILD {
	RELACIONES_GUILD_GUERRA = -1, RELACIONES_GUILD_PAZ = 0, RELACIONES_GUILD_ALIADOS = 1
};
enum eKingSpells {
	eKingSpells_LittleHeal = 1,
	eKingSpells_RemoveParalisis = 2,
	eKingSpells_BlindAttack = 3,
	eKingSpells_StupidityAttack = 4,
	eKingSpells_HealPoison = 5
};
enum eKingAction {
	eKingAction_HealAllyParalisis = 1,
	eKingAction_HealAllyPoison,
	eKingAction_HealAlly,
	eKingAction_ChaseTarget,
	eKingAction_MassiveAttack,
	eKingAction_RetreatAndHeal
};
enum eHealerAction {
	eHealerAction_HealAllyParalisis = 1,
	eHealerAction_ParalizePet,
	eHealerAction_ParalizeUser,
	eHealerAction_AttackUser,
	eHealerAction_HealAlly,
	eHealerAction_RescueFarAlly
};
enum eHealerSpells {
	eHealerSpells_ParalizeUser = 1,
	eHealerSpells_RemoveParalisis = 2,
	eHealerSpells_ParalizeNpc = 3,
	eHealerSpells_Heal = 4,
	eHealerSpells_Tormenta = 5
};
enum eSpellCasterAction {
	eSpellCasterAction_RemoveInvi = 1, eSpellCasterAction_Attack
};
enum eSpellCasterSpells {
	eSpellCasterSpells_Apocalipsis = 1, eSpellCasterSpells_RemoInvi = 2
};
enum eThiefAction {
	eThiefAction_Attack = 1, eThiefAction_Steal, eThiefAction_None
};
enum eThiefSpells {
	eThiefSpells_Arrow = 1,
  eThiefSpells_Paralisis = 2
};
enum ServerPacketID {
	Logged,
	RemoveDialogs,
	RemoveCharDialog,
	NavigateToggle,
	Disconnect,
	CommerceEnd,
	BankEnd,
	CommerceInit,
	BankInit,
	UserCommerceInit,
	UserCommerceEnd,
	UserOfferConfirm,
	CommerceChat,
	ShowBlacksmithForm,
	ShowCarpenterForm,
	UpdateSta,
	UpdateMana,
	UpdateHP,
	UpdateGold,
	UpdateBankGold,
	UpdateExp,
	ChangeMap,
	PosUpdate,
	ChatOverHead,
	ConsoleMsg,
	GuildChat,
	ShowMessageBox,
	UserIndexInServer,
	UserCharIndexInServer,
	CharacterCreate,
	CharacterRemove,
	CharacterChangeNick,
	CharacterMove,
	ForceCharMove,
	CharacterChange,
	ObjectCreate,
	ObjectDelete,
	BlockPosition,
	PlayMidi,
	PlayWave,
	guildList,
	AreaChanged,
	PauseToggle,
	RainToggle,
	CreateFX,
	UpdateUserStats,
	WorkRequestTarget,
	ChangeInventorySlot,
	ChangeBankSlot,
	ChangeSpellSlot,
	Atributes,
	BlacksmithWeapons,
	BlacksmithArmors,
	CarpenterObjects,
	RestOK,
	ErrorMsg,
	Blind,
	Dumb,
	ShowSignal,
	ChangeNPCInventorySlot,
	UpdateHungerAndThirst,
	Fame,
	MiniStats,
	LevelUp,
	AddForumMsg,
	ShowForumForm,
	SetInvisible,
	DiceRoll,
	MeditateToggle,
	BlindNoMore,
	DumbNoMore,
	SendSkills,
	TrainerCreatureList,
	guildNews,
	OfferDetails,
	AlianceProposalsList,
	PeaceProposalsList,
	CharacterInfo,
	GuildLeaderInfo,
	GuildMemberInfo,
	GuildDetails,
	ShowGuildFundationForm,
	ParalizeOK,
	ShowUserRequest,
	TradeOK,
	BankOK,
	ChangeUserTradeSlot,
	SendNight,
	Pong,
	UpdateTagAndStatus,
	SpawnList,
	ShowSOSForm,
	ShowMOTDEditionForm,
	ShowGMPanelForm,
	UserNameList,
	ShowDenounces,
	RecordList,
	RecordDetails,
	ShowGuildAlign,
	ShowPartyForm,
	UpdateStrenghtAndDexterity,
	UpdateStrenght,
	UpdateDexterity,
	AddSlots,
	MultiMessage,
	StopWorking,
    CancelOfferItem
};

enum ClientPacketID {
	/* 'OLOGIN */
	ClientPacketID_LoginExistingChar,
	/* 'TIRDAD */
	ClientPacketID_ThrowDices,
	/* 'NLOGIN */
	ClientPacketID_LoginNewChar,
	/* '; */
	ClientPacketID_Talk,
	/* '- */
	ClientPacketID_Yell,
	/* '\ */
	ClientPacketID_Whisper,
	/* 'M */
	ClientPacketID_Walk,
	/* 'RPU */
	ClientPacketID_RequestPositionUpdate,
	/* 'AT */
	ClientPacketID_Attack,
	/* 'AG */
	ClientPacketID_PickUp,
	/* '/SEG & SEG  (SEG's behaviour has to be coded in the client) */
	ClientPacketID_SafeToggle,
	ClientPacketID_ResuscitationSafeToggle,
	/* 'GLINFO */
	ClientPacketID_RequestGuildLeaderInfo,
	/* 'ATR */
	ClientPacketID_RequestAtributes,
	/* 'FAMA */
	ClientPacketID_RequestFame,
	/* 'ESKI */
	ClientPacketID_RequestSkills,
	/* 'FEST */
	ClientPacketID_RequestMiniStats,
	/* 'FINCOM */
	ClientPacketID_CommerceEnd,
	/* 'FINCOMUSU */
	ClientPacketID_UserCommerceEnd,
	ClientPacketID_UserCommerceConfirm,
	ClientPacketID_CommerceChat,
	/* 'FINBAN */
	ClientPacketID_BankEnd,
	/* 'COMUSUOK */
	ClientPacketID_UserCommerceOk,
	/* 'COMUSUNO */
	ClientPacketID_UserCommerceReject,
	/* 'TI */
	ClientPacketID_Drop,
	/* 'LH */
	ClientPacketID_CastSpell,
	/* 'LC */
	ClientPacketID_LeftClick,
	/* 'RC */
	ClientPacketID_RightClick,
	/* 'UK */
	ClientPacketID_Work,
	/* 'UMH */
	ClientPacketID_UseSpellMacro,
	/* 'USA */
	ClientPacketID_UseItem,
	/* 'CNS */
	ClientPacketID_CraftBlacksmith,
	/* 'CNC */
	ClientPacketID_CraftCarpenter,
	/* 'WLC */
	ClientPacketID_WorkLeftClick,
	/* 'CIG */
	ClientPacketID_CreateNewGuild,
	/* 'INFS */
	ClientPacketID_SpellInfo,
	/* 'EQUI */
	ClientPacketID_EquipItem,
	/* 'CHEA */
	ClientPacketID_ChangeHeading,
	/* 'SKSE */
	ClientPacketID_ModifySkills,
	/* 'ENTR */
	ClientPacketID_Train,
	/* 'COMP */
	ClientPacketID_CommerceBuy,
	/* 'RETI */
	ClientPacketID_BankExtractItem,
	/* 'VEND */
	ClientPacketID_CommerceSell,
	/* 'DEPO */
	ClientPacketID_BankDeposit,
	/* 'DEMSG */
	ClientPacketID_ForumPost,
	/* 'DESPHE */
	ClientPacketID_MoveSpell,
	ClientPacketID_MoveBank,
	/* 'DESCOD */
	ClientPacketID_ClanCodexUpdate,
	/* 'OFRECER */
	ClientPacketID_UserCommerceOffer,
	/* 'ACEPPEAT */
	ClientPacketID_GuildAcceptPeace,
	/* 'RECPALIA */
	ClientPacketID_GuildRejectAlliance,
	/* 'RECPPEAT */
	ClientPacketID_GuildRejectPeace,
	/* 'ACEPALIA */
	ClientPacketID_GuildAcceptAlliance,
	/* 'PEACEOFF */
	ClientPacketID_GuildOfferPeace,
	/* 'ALLIEOFF */
	ClientPacketID_GuildOfferAlliance,
	/* 'ALLIEDET */
	ClientPacketID_GuildAllianceDetails,
	/* 'PEACEDET */
	ClientPacketID_GuildPeaceDetails,
	/* 'ENVCOMEN */
	ClientPacketID_GuildRequestJoinerInfo,
	/* 'ENVALPRO */
	ClientPacketID_GuildAlliancePropList,
	/* 'ENVPROPP */
	ClientPacketID_GuildPeacePropList,
	/* 'DECGUERR */
	ClientPacketID_GuildDeclareWar,
	/* 'NEWWEBSI */
	ClientPacketID_GuildNewWebsite,
	/* 'ACEPTARI */
	ClientPacketID_GuildAcceptNewMember,
	/* 'RECHAZAR */
	ClientPacketID_GuildRejectNewMember,
	/* 'ECHARCLA */
	ClientPacketID_GuildKickMember,
	/* 'ACTGNEWS */
	ClientPacketID_GuildUpdateNews,
	/* '1HRINFO< */
	ClientPacketID_GuildMemberInfo,
	/* 'ABREELEC */
	ClientPacketID_GuildOpenElections,
	/* 'SOLICITUD */
	ClientPacketID_GuildRequestMembership,
	/* 'CLANDETAILS */
	ClientPacketID_GuildRequestDetails,
	/* '/ONLINE */
	ClientPacketID_Online,
	/* '/SALIR */
	ClientPacketID_Quit,
	/* '/SALIRCLAN */
	ClientPacketID_GuildLeave,
	/* '/BALANCE */
	ClientPacketID_RequestAccountState,
	/* '/QUIETO */
	ClientPacketID_PetStand,
	/* '/ACOMPANAR */
	ClientPacketID_PetFollow,
	/* '/LIBERAR */
	ClientPacketID_ReleasePet,
	/* '/ENTRENAR */
	ClientPacketID_TrainList,
	/* '/DESCANSAR */
	ClientPacketID_Rest,
	/* '/MEDITAR */
	ClientPacketID_Meditate,
	/* '/RESUCITAR */
	ClientPacketID_Resucitate,
	/* '/CURAR */
	ClientPacketID_Heal,
	/* '/AYUDA */
	ClientPacketID_Help,
	/* '/EST */
	ClientPacketID_RequestStats,
	/* '/COMERCIAR */
	ClientPacketID_CommerceStart,
	/* '/BOVEDA */
	ClientPacketID_BankStart,
	/* '/ENLISTAR */
	ClientPacketID_Enlist,
	/* '/INFORMACION */
	ClientPacketID_Information,
	/* '/RECOMPENSA */
	ClientPacketID_Reward,
	/* '/MOTD */
	ClientPacketID_RequestMOTD,
	/* '/UPTIME */
	ClientPacketID_UpTime,
	/* '/SALIRPARTY */
	ClientPacketID_PartyLeave,
	/* '/CREARPARTY */
	ClientPacketID_PartyCreate,
	/* '/PARTY */
	ClientPacketID_PartyJoin,
	/* '/ENCUESTA ( with no params ) */
	ClientPacketID_Inquiry,
	/* '/CMSG */
	ClientPacketID_GuildMessage,
	/* '/PMSG */
	ClientPacketID_PartyMessage,
	/* '/CENTINELA */
	ClientPacketID_CentinelReport,
	/* '/ONLINECLAN */
	ClientPacketID_GuildOnline,
	/* '/ONLINEPARTY */
	ClientPacketID_PartyOnline,
	/* '/BMSG */
	ClientPacketID_CouncilMessage,
	/* '/ROL */
	ClientPacketID_RoleMasterRequest,
	/* '/GM */
	ClientPacketID_GMRequest,
	/* '/_BUG */
	ClientPacketID_bugReport,
	/* '/DESC */
	ClientPacketID_ChangeDescription,
	/* '/VOTO */
	ClientPacketID_GuildVote,
	/* '/PENAS */
	ClientPacketID_Punishments,
	/* '/CONTRASENA */
	ClientPacketID_ChangePassword,
	/* '/APOSTAR */
	ClientPacketID_Gamble,
	/* '/ENCUESTA ( with parameters ) */
	ClientPacketID_InquiryVote,
	/* '/RETIRAR ( with no arguments ) */
	ClientPacketID_LeaveFaction,
	/* '/RETIRAR ( with arguments ) */
	ClientPacketID_BankExtractGold,
	/* '/DEPOSITAR */
	ClientPacketID_BankDepositGold,
	/* '/DENUNCIAR */
	ClientPacketID_Denounce,
	/* '/FUNDARCLAN */
	ClientPacketID_GuildFundate,
	ClientPacketID_GuildFundation,
	/* '/ECHARPARTY */
	ClientPacketID_PartyKick,
	/* '/PARTYLIDER */
	ClientPacketID_PartySetLeader,
	/* '/ACCEPTPARTY */
	ClientPacketID_PartyAcceptMember,
	ClientPacketID_Ping,
	ClientPacketID_RequestPartyForm,
	ClientPacketID_ItemUpgrade,
	ClientPacketID_GMCommands,
	ClientPacketID_InitCrafting,
	ClientPacketID_Home,
	ClientPacketID_ShowGuildNews,
	/* '/COMPARTIR */
	ClientPacketID_ShareNpc,
	ClientPacketID_StopSharingNpc,
	ClientPacketID_Consultation,
	ClientPacketID_moveItem,

	LAST_CLIENT_PACKET_ID
};

enum FontTypeNames {
	FontTypeNames_FONTTYPE_TALK,
	FontTypeNames_FONTTYPE_FIGHT,
	FontTypeNames_FONTTYPE_WARNING,
	FontTypeNames_FONTTYPE_INFO,
	FontTypeNames_FONTTYPE_INFOBOLD,
	FontTypeNames_FONTTYPE_EJECUCION,
	FontTypeNames_FONTTYPE_PARTY,
	FontTypeNames_FONTTYPE_VENENO,
	FontTypeNames_FONTTYPE_GUILD,
	FontTypeNames_FONTTYPE_SERVER,
	FontTypeNames_FONTTYPE_GUILDMSG,
	FontTypeNames_FONTTYPE_CONSEJO,
	FontTypeNames_FONTTYPE_CONSEJOCAOS,
	FontTypeNames_FONTTYPE_CONSEJOVesA,
	FontTypeNames_FONTTYPE_CONSEJOCAOSVesA,
	FontTypeNames_FONTTYPE_CENTINELA,
	FontTypeNames_FONTTYPE_GMMSG,
	FontTypeNames_FONTTYPE_GM,
	FontTypeNames_FONTTYPE_CITIZEN,
	FontTypeNames_FONTTYPE_CONSE,
	FontTypeNames_FONTTYPE_DIOS
};

enum eEditOptions {
	eEditOptions_eo_Gold = 1,
	eEditOptions_eo_Experience,
	eEditOptions_eo_Body,
	eEditOptions_eo_Head,
	eEditOptions_eo_CiticensKilled,
	eEditOptions_eo_CriminalsKilled,
	eEditOptions_eo_Level,
	eEditOptions_eo_Class,
	eEditOptions_eo_Skills,
	eEditOptions_eo_SkillPointsLeft,
	eEditOptions_eo_Nobleza,
	eEditOptions_eo_Asesino,
	eEditOptions_eo_Sex,
	eEditOptions_eo_Raza,
	eEditOptions_eo_addGold,
	eEditOptions_eo_Vida,
	eEditOptions_eo_Poss
};

#endif
