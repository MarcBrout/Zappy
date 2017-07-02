using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeamInfo {

    public string name;
    public int lvl1;
    public int lvl2;
    public int lvl3;
    public int lvl4;
    public int lvl5;
    public int lvl6;
    public int lvl7;
    public int lvl8;

    public TeamInfo(string name)
    {
        this.name = name;
        lvl1 = lvl2 = lvl3 = lvl4 = lvl5 = lvl6 = lvl7 = lvl8 = 0;
    }

    public void UpdateTeamInfo(int lvl1 = 0, int lvl2 = 0, int lvl3 = 0, int lvl4 = 0, int lvl5 = 0, int lvl6 = 0, int lvl7 = 0, int lvl8 = 0)
    {
        this.lvl1 = lvl1;
        this.lvl2 = lvl2;
        this.lvl3 = lvl3;
        this.lvl4 = lvl4;
        this.lvl5 = lvl5;
        this.lvl6 = lvl6;
        this.lvl7 = lvl7;
        this.lvl8 = lvl8;
    }

    public void UpdateTeamInfo(Player p)
    {
        if (p.level == 1)
            ++lvl1;
        else if (p.level == 2)
            ++lvl2;
        else if (p.level == 3)
            ++lvl3;
        else if (p.level == 4)
            ++lvl4;
        else if (p.level == 5)
            ++lvl5;
        else if (p.level == 6)
            ++lvl6;
        else if (p.level == 7)
            ++lvl7;
        else if (p.level == 8)
            ++lvl8;
    }
}
