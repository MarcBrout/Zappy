using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TeamInfoUI : MonoBehaviour {

    public Text teamName;
    public Text lvl1;
    public Text lvl2;
    public Text lvl3;
    public Text lvl4;
    public Text lvl5;
    public Text lvl6;
    public Text lvl7;
    public Text lvl8;

    public TeamInfo teamInfo;
	
	void Update () {
		if (teamInfo != null)
        {
            teamName.text = teamInfo.name;
            lvl1.text = teamInfo.lvl1.ToString();
            lvl2.text = teamInfo.lvl2.ToString();
            lvl3.text = teamInfo.lvl3.ToString();
            lvl4.text = teamInfo.lvl4.ToString();
            lvl5.text = teamInfo.lvl5.ToString();
            lvl6.text = teamInfo.lvl6.ToString();
            lvl7.text = teamInfo.lvl7.ToString();
            lvl8.text = teamInfo.lvl8.ToString();
        }
	}
}
