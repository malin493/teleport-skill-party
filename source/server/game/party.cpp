//find and change
void CParty::SummonToLeader(DWORD pid)
{
	LPCHARACTER l = GetLeaderCharacter();

	if (m_memberMap.find(pid) == m_memberMap.end())
	{
		l->ChatPacket(CHAT_TYPE_INFO, "<Teleport> The character is too far.");
		return;
	}

	LPCHARACTER ch = m_memberMap[pid].pCharacter;

	if (!ch)
	{
		l->ChatPacket(CHAT_TYPE_INFO, "<Teleport> The character was not found in your map.");
		return;
	}

	if (ch->IsDead())
	{
		l->ChatPacket(CHAT_TYPE_INFO, "<Teleport> I can't teleport the character if he is dead.");
		return;
	}

	ch->Show(l->GetMapIndex(), l->GetX(), l->GetY());
	ch->Stop();
}