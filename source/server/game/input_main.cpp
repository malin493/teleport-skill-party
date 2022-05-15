//find and change
void CInputMain::PartyUseSkill(LPCHARACTER ch, const char* c_pData)
{
    TPacketCGPartyUseSkill* p = (TPacketCGPartyUseSkill*) c_pData; 
    if (!ch->GetParty())
        return;

    if (ch->GetPlayerID() != ch->GetParty()->GetLeaderPID())
    {
        ch->ChatPacket(CHAT_TYPE_INFO, "<Group> Only the leader can use this function.");
        return;
    }

    switch (p->bySkillIndex)
    {
        case PARTY_SKILL_HEAL:
            ch->GetParty()->HealParty();
            break;
        case PARTY_SKILL_WARP:
            {
                if (ch->GetSkillLevel(SKILL_LEADERSHIP) >= 10)
                {
                    LPCHARACTER pch = CHARACTER_MANAGER::instance().Find(p->vid);
                    if (pch)
                    {
                        int last_use_time = ch->GetQuestFlag("setTimerSkillForParty.last_use_time");
                        if (get_global_time() - last_use_time < 60)
                        {
                            ch->ChatPacket(CHAT_TYPE_INFO, "timer %d sec.", 60 - (get_global_time() - last_use_time));
                            return;
                        }
                        ch->GetParty()->SummonToLeader(pch->GetPlayerID()); 
                        ch->SetQuestFlag("setTimerSkillForParty.last_use_time", get_global_time());
                    }
                    else
                    {
                        ch->ChatPacket(CHAT_TYPE_INFO, "<Teleport> The character is not online.");
                    }
                }
                else
                {
                    ch->ChatPacket(CHAT_TYPE_INFO, "<Teleport> You need upgrade your leadership skill to use this function.");
                }
            }
            break;
    }
}