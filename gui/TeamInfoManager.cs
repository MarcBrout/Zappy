using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeamInfoManager : MonoBehaviour {

    public Transform teamInfoParent;
    public GameObject teamInfoUI;
    public List<TeamInfoUI> teamInfoListUI;

    public TeamInfoUI FindTeamUI(string name)
    {
        return teamInfoListUI.Find((x) => x.teamInfo.name == name);
    }

    public void Reset()
    {
        for (int i = 0; i < teamInfoListUI.Count; i++)
        {
            teamInfoListUI[i].teamInfo.UpdateTeamInfo();
        }        
    }

    public void UpdateTeamInfo(Player p)
    {
        TeamInfoUI t = FindTeamUI(p.team);
        if (t == null)
        {
            GameObject go = Instantiate(teamInfoUI, teamInfoParent);
            t = go.GetComponent<TeamInfoUI>();
            t.teamInfo = new TeamInfo(p.team);

            teamInfoListUI.Add(t);
        }
        t.teamInfo.UpdateTeamInfo(p);
    }
}
